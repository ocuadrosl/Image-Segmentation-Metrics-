/*
 * SEGmetric.h
 *
 *  Created on: 13/2/2015
 *      Author: oscar
 */

#ifndef METRIC_H_
#define METRIC_H_

#include <vector>
#include "SEG.h"

using namespace std;

typedef vector<vector<int> > reg_t; //seg row
/*
 * to seg files
 * oscar
 * */

class Metric
{
	public:
		virtual float error(SEG* __seg_1, SEG* __seg_2)=0; // return 1 to equal segs and 0 to very different

		virtual ~Metric()
		{
		}
		;

		Metric()
		{
		}
		;

	protected:

		int I(reg_t __reg_1, reg_t __reg_2); //intersection between two regions
		int U(reg_t __reg_1, reg_t __reg_2); //union between two regions
		int n_pixels(reg_t __reg); //number of pixes in __reg
		float jaccard(reg_t __reg_1, reg_t __reg_2);

};

float Metric::jaccard(reg_t __reg_1, reg_t __reg_2)
{

	float den = U(__reg_1, __reg_2);

	return (den == 0) ? 1.f : (float) I(__reg_1, __reg_2) / den;

}

int Metric::n_pixels(reg_t __reg)
{
	int size = 0;
	for (unsigned i = 0; i < __reg.size(); i++)
	{
		size += ((__reg[i][2] - __reg[i][1]) + 1);
	}
	return size;
}

int Metric::I(vector<vector<int> > __reg_1, vector<vector<int> > __reg_2)
{

	int intersection = 0;

	/*auriliary declarations*/
	int min_end = 0;
	int max_begin = 0;

	for (unsigned i = 0; i < __reg_1.size(); i++)
	{
		for (unsigned j = 0; j < __reg_2.size(); j++)
		{
			if (__reg_1[i][0] == __reg_2[j][0]) //row verification
			{
				min_end = std::min(__reg_1[i][2], __reg_2[j][2]); //
				max_begin = std::max(__reg_1[i][1], __reg_2[j][1]);

				if (min_end >= max_begin)
				{
					intersection += ((min_end - max_begin) + 1);
				}

			}

		}
	}

	return intersection;
}

int Metric::U(vector<vector<int> > __reg_1, vector<vector<int> > __reg_2)
{
	return (n_pixels(__reg_1) + n_pixels(__reg_2)) - I(__reg_1, __reg_2);
}

#endif /* METRIC_H_ */
