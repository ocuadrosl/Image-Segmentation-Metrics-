/*
 * SEGmetric.h
 *
 *  Created on: 13/2/2015
 *      Author: oscar
 */

#ifndef METRIC_H_
#define METRIC_H_

typedef vector<vector<int> > reg_t; //seg row
/*
 * to seg files
 * oscar
 * */

class Metric
{
	public:
		//virtual float operator()(SEG* __seg_1, SEG* __seg_2)=0;
		virtual float compare(SEG* __seg_1, SEG* __seg_2)=0;
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
		int size(reg_t __reg); //the number of pixes in __reg
		float jaccard(reg_t __reg_1, reg_t __reg_2);

};

float Metric::jaccard(reg_t __reg_1, reg_t __reg_2)
{

	float den = U(__reg_1, __reg_2);

	return (den == 0) ? 1.f : (float) I(__reg_1, __reg_2) / den;

}

int Metric::size(reg_t __reg)
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
				min_end = Util::min(__reg_1[i][2], __reg_2[j][2]); //
				max_begin = Util::max(__reg_1[i][1], __reg_2[j][1]);

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
	return (size(__reg_1) + size(__reg_2)) - I(__reg_1, __reg_2);
}

#endif /* METRIC_H_ */
