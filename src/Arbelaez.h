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

#ifndef ARBELAEZ_H_
#define ARBELAEZ_H_

/*
 * Contour Detection and Hierarchical Image Segmentation by Pablo Arbeláez
 *
 * implemented by Oscar
 *
 *
 * */

class Arbelaez: public Metric
{
	public:
		Arbelaez()
		{
		}
		;

		double error(SEG* __seg_1, SEG* __seg_2);

};

double Arbelaez::error(SEG* __seg_1, SEG* __seg_2)
{

	float covering = 0;
	for (int i = 0; i < __seg_2->size(); i++)
	{
		float overlap = 0;
		float jacc = 0;
		for (int j = 0; j < __seg_1->size(); j++)
		{
			jacc = jaccard((*__seg_2)[i], (*__seg_1)[j]);

			overlap = (jacc > overlap) ? jacc : overlap;

		}
		covering += getNumberOfPixels((*__seg_2)[i]) * overlap;

	}

	return 1 - (covering / (float) (__seg_1->height() * __seg_1->width()));

}

#endif /* ARBELAEZ_H_ */
