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

#ifndef JACCARD_H_
#define JACCARD_H_

#include "SEG.h"
#include "Metric.h"

/*
 * Jaccard index
 *
 *
 * */

class Jaccard: public Metric
{
public:
	Jaccard()
	{
	}
	;
	~Jaccard()
	{
	}
	;

public:
	inline double compute(const SEG & seg1, const SEG & seg2) final;
};

/*
 * Jaccard index for all regions, it is assumed that seg2 is placed over seg1,
 * Region labels are not considered
 * Using equation sum( intersection(seg1,seg2))/sum(union(seg1,seg2))
 * If intersection between two regions, then union is zero.
 * 0 <= Jaccard <= 1
 *
 * */

double Jaccard::compute(const SEG & seg1, const SEG & seg2)
{
	double similarity = 0;
	double intersections = 0;
	double unions = 0;
	int intersection = 0;

	for (int i = 0; i < seg2.size(); ++i)
	{

		intersection = 0;
		for (int j = 0; j < seg1.size(); ++j)
		{
			intersection = I(seg2[i], seg1[j]);

			intersections += intersection;

			unions += (intersection > 0) ? U(seg2[i], seg1[j]) : 0;

		}

	}

	return (unions == 0) ? 0 : intersections / unions;

}

#endif /* JACCARD_H_ */
