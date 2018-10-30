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

#include <vector>
#include <cmath>
#include "SEG.h"
#include "Metric.h"

using namespace std;

#ifndef OCE_H_
#define OCE_H_

typedef vector<vector<int> > reg_t; //seg row

/*
 *  An evaluation metric for image segmentation of multiple objects
 *	Mark Polak - 2009
 *	Implemented by: Oscar
 *
 * */

class OCE: public Metric
{
	public:
		double error(SEG* __seg_1, SEG* __seg_2);
		//string metric_name();

	private:

		int bar_delta(int __input); //bar delta: see the paper (equation 6)
		float E(SEG* __seg_1, SEG* __seg_2); //error function: equation 6

};

double OCE::error(SEG* __seg_1, SEG* __seg_2)
{
	return std::min(E(__seg_1, __seg_2), E(__seg_2, __seg_1));

}
int OCE::bar_delta(int __input)
{
	return (__input == 0) ? 0 : 1;

}

float OCE::E(SEG* __seg_1, SEG* __seg_2)
{

	double error = 0;

	for (int j = 0; j < __seg_1->size(); j++)
	{

		double jacc = 0;
		for (int i = 0; i < __seg_2->size(); i++)
		{

			double den = 0;
			double num = 0;

			for (int k = 0; k < __seg_2->size(); k++)
			{
				den += bar_delta(I((*__seg_1)[j], (*__seg_2)[k])) * getNumberOfPixels((*__seg_2)[k]);
			}

			num = bar_delta(I((*__seg_1)[j], (*__seg_2)[i])) * getNumberOfPixels((*__seg_2)[i]);

			double w_ij = num / den;

			jacc += (jaccard((*__seg_1)[j], (*__seg_2)[i]) * w_ij);

		}

		jacc = 1 - jacc;

		double den = 0;
		for (int k = 0; k < __seg_1->size(); k++)
		{
			den += getNumberOfPixels((*__seg_1)[k]);
		}

		double w_j = getNumberOfPixels((*__seg_1)[j]) / den;

		error = error + (jacc * w_j);

	}

	return error;
}

#endif /* OCE_H_ */
