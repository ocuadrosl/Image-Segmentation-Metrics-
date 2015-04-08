/*
 * AOM.h
 *
 *  Created on: 19/2/2015
 *      Author: oscar
 */

#ifndef AOM_H_
#define AOM_H_

#include "SEG.h"
#include "Metric.h"
#include <vector>
#include <algorithm>

using namespace std;
/*
 * An Adaptable Error Measure for Image Segmentation Evaluation
 * AOM
 * Oscar
 *
 */

typedef vector<vector<float> > matrix_t;

class AOM: public Metric
{
	public:

		AOM();

		float error(SEG* __seg_1, SEG* __seg_2);

		void print_matrix();

		void penality(float __penality);

	private:
		matrix_t _intersections;

		vector<float> _over_segmentations; //to consider over segmentation
		float _penalty; // to penalize over segmentation

		void intersection_matrix(SEG* __seg_1, SEG* __seg_2);
		void summatory(matrix_t __intersections, vector<float> _over_segmentations, float& __sum);

		int _image_size;

};

void AOM::summatory(matrix_t __intersections, vector<float> __over_segmentations, float& __sum)
{

	if (__intersections.size() <= 0)
	{
		return;
	}

	float __largest = 0;

	unsigned i_flag = 0;
	unsigned j_flag = 0;

	for (unsigned i = 0; i < __intersections.size(); i++)
	{
		for (unsigned j = 0; j < __intersections[0].size(); j++)
		{
			if (__intersections[i][j] > __largest)
			{

				__largest = __intersections[i][j];
				i_flag = i;
				j_flag = j;
			}

		}
	}

	//cout << __largest << " " << _over_segmentations[i_flag] << endl;

	if (__largest <= 0)
	{

		return;
	}

	__sum += (__largest * __over_segmentations[i_flag]);

	for (unsigned i = 0; i < __intersections.size(); i++) //erase column
	{
		__intersections[i].erase(__intersections[i].begin() + j_flag);

	}

	__intersections.erase(__intersections.begin() + i_flag);
	__over_segmentations.erase(__over_segmentations.begin() + i_flag);

	summatory(__intersections, __over_segmentations, __sum);

}

void AOM::intersection_matrix(SEG* __seg_1, SEG* __seg_2)
{

	_intersections.resize(__seg_1->size());

	//_over_segmentations.clear();
	_over_segmentations.resize(__seg_1->size(), 0);

	for (int i = 0; i < __seg_1->size(); i++)
	{
		_intersections[i].resize(__seg_2->size());
		_over_segmentations[i] = 0;
	}

	for (int i = 0; i < __seg_1->size(); i++)
	{
		for (int j = 0; j < __seg_2->size(); j++)
		{
			_intersections[i][j] = I((*__seg_1)[i], (*__seg_2)[j]);

			if (_intersections[i][j] > 0)
			{
				_over_segmentations[i] += _penalty;

			}

		}

		if (_over_segmentations[i] < 1)
		{
			_over_segmentations[i] = 1.f;
		}

		_over_segmentations[i] = 1.f / _over_segmentations[i];

		//cout << _over_segmentations[i] << endl;

	}
	//print_matrix();

}

AOM::AOM()
{
	_penalty = 0;
	_image_size = 0;

}

void AOM::penality(float __penality)
{
	_penalty = __penality;
}

void AOM::print_matrix()
{
	for (unsigned i = 0; i < _intersections.size(); i++)
	{

		for (unsigned j = 0; j < _intersections[i].size(); j++)
		{
			cout << _intersections[i][j] << " ";
		}
		cout << endl;

	}

}

float AOM::error(SEG* __seg_1, SEG* __seg_2)
{

	_image_size = __seg_1->width() * __seg_1->height();

	if (__seg_1->size() > __seg_2->size())
	{
		intersection_matrix(__seg_2, __seg_1);
	}
	else
	{
		intersection_matrix(__seg_1, __seg_2);
	}

	float sum = 0;

	summatory(_intersections, _over_segmentations, sum);

	return 1 - (sum / (float) _image_size);

}

#endif /* AOM_H_ */
