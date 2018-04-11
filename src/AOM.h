/*
 * Copyright (C) 2016  Oscar Alonso Cuadros Linares
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#ifndef AOM_H_
#define AOM_H_

#include "SEG.h"
#include "Metric.h"
#include <vector>
#include <algorithm>

using namespace std;

/*
 * Oscar
 * An Adaptable Error Measure for Image Segmentation Evaluation
 * AOM
 * *
 */

class AOM: public Metric
{
public:

	typedef vector<vector<double> > matrixType;

	AOM();
	~AOM();

	double error(const SEG & __seg_1, const SEG & __seg_2);

	void print_matrix() const;

	void penality(const double & __penality);

private:
	matrixType _intersections;

	vector<double> _over_segmentations; //to consider over segmentation
	double _penalty; // to penalize over segmentation

	void intersection_matrix(const SEG & __seg_1, const SEG & __seg_2);
	void summatory(matrixType& __intersections, vector<double>& _over_segmentations, double& __sum);

	int _image_size;

};

AOM::~AOM()
{
	matrixType().swap(_intersections);
	vector<double>().swap(_over_segmentations);
}

void AOM::summatory(matrixType& __intersections, vector<double>& __over_segmentations, double& __sum)
{

	if (__intersections.size() <= 0)
	{
		return;
	}

	double __largest = 0;

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

void AOM::intersection_matrix(const SEG & __seg_1, const SEG & __seg_2)
{

	_intersections.resize(__seg_1.size());

	//_over_segmentations.clear();
	_over_segmentations.resize(__seg_1.size(), 0);

	for (int i = 0; i < __seg_1.size(); i++)
	{
		_intersections[i].resize(__seg_2.size());
		_over_segmentations[i] = 0;
	}

	for (int i = 0; i < __seg_1.size(); i++)
	{
		for (int j = 0; j < __seg_2.size(); j++)
		{
			_intersections[i][j] = I(__seg_1[i], __seg_2[j]);

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

void AOM::penality(const double & __penality)
{
	_penalty = __penality;
}

void AOM::print_matrix() const
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

double AOM::error(const SEG & __seg_1, const SEG & __seg_2)
{

	_image_size = __seg_1.width() * __seg_1.height();

	if (__seg_1.size() > __seg_2.size())
	{
		intersection_matrix(__seg_2, __seg_1);
	}
	else
	{
		intersection_matrix(__seg_1, __seg_2);
	}

	double sum = 0;

	summatory(_intersections, _over_segmentations, sum);

	return 1 - (sum / (double) _image_size);

}

#endif /* AOM_H_ */
