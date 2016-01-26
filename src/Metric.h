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

/*
 * to seg files
 * oscar
 * */

class Metric
{

	public:

		typedef typename SEG::region_t region_t; //seg row

		/* This functions have to return 1 to equal
		 * segmentations and 0 to totally different
		 */
		virtual double error(const SEG & __seg_1, const SEG & __seg_2)=0;

		virtual ~Metric()
		{
		}
		;

		Metric()
		{
		}
		;

	protected:

		int I(const region_t & __reg_1, const region_t & __reg_2) const; //intersection between two regions
		int U(const region_t & __reg_1, const region_t & __reg_2) const; //union between two regions
		int n_pixels(const region_t & __reg) const; //number of pixes in __reg
		double jaccard(const region_t & __reg_1, const region_t & __reg_2) const;

};

double Metric::jaccard(const region_t & __reg_1, const region_t & __reg_2) const
{

	double den = U(__reg_1, __reg_2);

	return (den == 0) ? 1.0 : (double) I(__reg_1, __reg_2) / den;

}

int Metric::n_pixels(const region_t & __reg) const
{
	int size = 0;
	for (unsigned i = 0; i < __reg.size(); i++)
	{
		size += ((__reg[i][2] - __reg[i][1]) + 1);
	}
	return size;
}

int Metric::I(const region_t& __reg_1, const region_t& __reg_2) const
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
				min_end = std::min(__reg_1[i][2], __reg_2[j][2]);
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

int Metric::U(const region_t & __reg_1, const region_t & __reg_2) const
{
	return (n_pixels(__reg_1) + n_pixels(__reg_2)) - I(__reg_1, __reg_2);
}

#endif /* METRIC_H_ */
