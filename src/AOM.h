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

	typedef std::vector<std::vector<double> > matrixType;

	AOM();
	~AOM();

	inline double compute(const SEG & seg1, const SEG & seg2) final;

	void printMatrix() const;

	void setPenality(const double & penality);

private:
	matrixType intersections;

	std::vector<double> overSegmentations; //to consider over segmentation
	double penalty; // to penalize over segmentation

	void intersectionMatrix(const SEG & seg1, const SEG & seg2);

	void summatory(double& sum);

};

AOM::~AOM()
{
	matrixType().swap(intersections);
	std::vector<double>().swap(overSegmentations);
}

void AOM::summatory(double& sum)
{

	if (intersections.size() <= 0)
	{
		return;
	}

	double largest = 0;

	unsigned iFlag = 0;
	unsigned jFlag = 0;

	for (unsigned i = 0; i < intersections.size(); ++i)
	{
		for (unsigned j = 0; j < intersections[0].size(); ++j)
		{
			if (intersections[i][j] > largest)
			{

				largest = intersections[i][j];
				iFlag = i;
				jFlag = j;
			}

		}
	}

	if (largest <= 0)
	{

		return;
	}

	sum += (largest * overSegmentations[iFlag]);

	for (unsigned i = 0; i < intersections.size(); ++i) //erase column
	{
		intersections[i].erase(intersections[i].begin() + jFlag);

	}

	intersections.erase(intersections.begin() + iFlag);
	overSegmentations.erase(overSegmentations.begin() + iFlag);

	summatory(sum);

}

void AOM::intersectionMatrix(const SEG & seg1, const SEG & seg2)
{

	intersections.resize(seg1.size());

	//_over_segmentations.clear();
	overSegmentations.resize(seg1.size(), 0);

	for (int i = 0; i < seg1.size(); ++i)
	{
		intersections[i].resize(seg2.size());
		overSegmentations[i] = 0;
	}

	for (int i = 0; i < seg1.size(); ++i)
	{
		for (int j = 0; j < seg2.size(); ++j)
		{
			intersections[i][j] = I(seg1[i], seg2[j]);

			if (intersections[i][j] > 0)
			{
				overSegmentations[i] += penalty;
			}

		}

		if (overSegmentations[i] < 1)
		{
			overSegmentations[i] = 1.0;
		}

		overSegmentations[i] = 1.0 / overSegmentations[i];

		//cout << _over_segmentations[i] << endl;

	}
	//print_matrix();

}

AOM::AOM()
{
	penalty = 0.0;

}

void AOM::setPenality(const double & penality)
{
	penalty = penality;
}

void AOM::printMatrix() const
{
	for (unsigned i = 0; i < intersections.size(); i++)
	{

		for (unsigned j = 0; j < intersections[i].size(); j++)
		{
			std::cout << intersections[i][j] << " ";
		}
		std::cout << std::endl;

	}

}

double AOM::compute(const SEG & seg1, const SEG & seg2)
{

	if (seg1.size() > seg2.size())
	{
		intersectionMatrix(seg2, seg1);
	}
	else
	{
		intersectionMatrix(seg1, seg2);
	}

	double sum = 0;

	summatory(sum);

	return 1.0 - (sum / static_cast<double>(seg1.width() * seg1.height()));

}

#endif /* AOM_H_ */
