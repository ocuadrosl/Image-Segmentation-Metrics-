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

#ifndef METRIC_H_
#define METRIC_H_

#include <vector>
#include "SEG.h"

using namespace std;

/*
 * to seg files
 *
 * */

class Metric
{

public:

	typedef typename SEG::region_t regionType; //seg row

	/*
	 * main function
	 * */
	virtual double compute(const SEG & seg1, const SEG & seg2)=0;

	virtual ~Metric()
	{
	}
	;

	Metric()
	{
	}
	;

protected:

	inline int I(const regionType & reg1, const regionType & reg2) const; //intersection between two regions
	inline int U(const regionType & reg1, const regionType & reg2) const; //union between two regions
	inline int getNumberOfPixels(const regionType & region) const; //number of pixes in __reg

	// region oriented jaccard
	inline double jaccard(const regionType & reg1, const regionType & reg2) const;

};
/*
 * Jaccard for only two regions
 *
 * */
double Metric::jaccard(const regionType & reg1, const regionType & reg2) const
{

	double den = U(reg1, reg2);

	return (den == 0) ? 1.0 : static_cast<double>(I(reg1, reg2)) / den;

}

int Metric::getNumberOfPixels(const regionType & region) const
{
	int numPixels = 0;
	for (unsigned i = 0; i < region.size(); ++i)
	{
		numPixels += ((region[i][2] - region[i][1]) + 1);
	}
	return numPixels;
}

int Metric::I(const regionType& reg1, const regionType& reg2) const
{

	int intersection = 0;

	/*Auxiliary declarations*/
	int min_end = 0;
	int max_begin = 0;

	for (unsigned i = 0; i < reg1.size(); ++i)
	{
		for (unsigned j = 0; j < reg2.size(); ++j)
		{
			if (reg1[i][0] == reg2[j][0]) //row verification
			{
				min_end = std::min(reg1[i][2], reg2[j][2]);
				max_begin = std::max(reg1[i][1], reg2[j][1]);

				if (min_end >= max_begin)
				{
					intersection += ((min_end - max_begin) + 1);
				}

			}

		}
	}

	return intersection;
}

/*
 * NOTICE: this function does not verify if the intersection between seg1 and seg2 is greater than 0
 *
 *
 * */

int Metric::U(const regionType & reg1, const regionType & reg2) const
{
	return (getNumberOfPixels(reg1) + getNumberOfPixels(reg2)) - I(reg1, reg2);
}

#endif /* METRIC_H_ */
