/*
 * Arbelaez.h
 *
 *  Created on: 26/2/2015
 *      Author: oscar
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

		float error(SEG* __seg_1, SEG* __seg_2);

};

float Arbelaez::error(SEG* __seg_1, SEG* __seg_2)
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
		covering += n_pixels((*__seg_2)[i]) * overlap;

	}

	return 1 - (covering / (float) (__seg_1->height() * __seg_1->width()));

}

#endif /* ARBELAEZ_H_ */
