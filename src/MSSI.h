/*
 * MSSI.h
 *
 *  Created on: 19/2/2015
 *      Author: oscar
 */

#ifndef MSSI_H_
#define MSSI_H_

#include "SEG.h"
#include "Metric.h"
#include <vector>
#include <algorithm>

using namespace std;
/*
 * Métrica de similaridade para segmentação de imagens
 * Oscar
 *
 *
 */

typedef vector<vector<float> > matrix_t;

class MSSI: public Metric
{
	public:

		MSSI()
		{
		}
		;

		float operator()(SEG* __seg_1, SEG* __seg_2);

		void print_matrix();

	private:
		matrix_t _intersections;
		void fill_matrix(SEG* __seg_1, SEG* __seg_2);
		void fill_largest(int __i, int __j);

		float summatory();

};

void MSSI::print_matrix()
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

void MSSI::fill_largest(int __i, int __j)
{
	float &col = _intersections[_intersections.size() - 2][__j];
	float &col_index = _intersections[_intersections.size() - 1][__j];

	float &row = _intersections[__i][_intersections[0].size() - 2];
	float &row_index = _intersections[__i][_intersections[0].size() - 1];

	float value = 0;

	value = _intersections[__i][__j];

	if (value > row && value > col)
	{
		col = value;
		col_index = __i;
		row = value;
		row_index = __j;
	}

}

float MSSI::summatory()
{
	int col_size = _intersections[0].size();
	int col_index = 0;

	float sum = 0.f;

	for (unsigned i = 0; i < _intersections.size() - 2; i++)
	{
		col_index = _intersections[i][col_size - 1];

		if (_intersections[i][col_size - 2] != _intersections[_intersections.size() - 2][col_index]) // to resolve false positives
		{
			//cout << "false positive " << _intersections[i][col_size - 2] << " " << i << " " << col_index << endl;
			_intersections[i][col_size - 1] = -1;
			_intersections[i][col_size - 2] = -1;

			for (int j = 0; j < col_size - 2; j++)
			{
				fill_largest(i, j);
			}

		}

		sum += _intersections[i][col_size - 2];

	}

	return sum;

}

void MSSI::fill_matrix(SEG* __seg_1, SEG* __seg_2)
{

	_intersections.resize(__seg_1->size() + 2); // position[size] to store the largest element

	for (int i = 0; i < __seg_1->size() + 2; i++)
	{
		_intersections[i].resize(__seg_2->size() + 2, -1.f);
	}

	for (int i = 0; i < __seg_1->size(); i++)
	{
		for (int j = 0; j < __seg_2->size(); j++)
		{
			_intersections[i][j] = I((*__seg_1)[i], (*__seg_2)[j]);

			fill_largest(i, j);
		}

	}

}

float MSSI::operator()(SEG* __seg_1, SEG* __seg_2)
{

	if (__seg_1->size() > __seg_2->size())
		fill_matrix(__seg_2, __seg_1);
	else
		fill_matrix(__seg_1, __seg_2);


	return 1 - (summatory() / float(__seg_1->width() * __seg_1->height()));

	//print_matrix();

}

#endif /* MSSI_H_ */
