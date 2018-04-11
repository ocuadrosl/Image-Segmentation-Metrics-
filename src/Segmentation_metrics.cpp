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

#include <iostream>

#include "metric.h"

#include "Test.h"

using namespace std;

int main()
{
	SEG seg_1, seg_2;
	seg_1.read("input/square_1.seg");
	seg_2.read("input/square_2.seg");

	//Metric *oce = new OCE();
	AOM aom;
	//Metric* arbelaez = new Arbelaez();

	//mssi->penality(0);

	Test test;

	//test.chrono(mssi, &seg_1, &seg_2);
	//test.chrono(mssi, &seg_1, &seg_3);
	//test.chrono(arbelaez, &seg_1, &seg_2);
	//test.chrono(arbelaez, &seg_2, &seg_1);
	//test.chrono(oce, &seg_1, &seg_2);

	//test.chrono(oce, &seg_1, &seg_2);
	//test.chrono(arbelaez, &seg_1, &seg_2);
	//test.chrono(arbelaez, &seg_2, &seg_1);

	//test.classes(mssi, "human_segmentations/35010", "human_segmentations/65019");
	//test.classes(arbelaez, "human_segmentations/35010", "human_segmentations/65019");
	//test.classes(oce, "human_segmentations/35010", "human_segmentations/65019");

	//for (float i = 0; i <= 1.05; i = i + 0.05)
	//{
	//cout << "**************** " << i << endl;
	aom.penality(0.5);
	//test.classes(mssi, "seg/square", "seg/square");
	//test.chrono(mssi, &seg_1, &seg_2);
	cout << aom.error(seg_1, seg_2) << std::endl;

	vector<vector<int> > reg_t;

	//}

	return 0;
}
