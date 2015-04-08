//============================================================================
// Name        : Segmentation_metrics.cpp
// Author      : Oscar
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>

#include "metric.h"

#include "Test.h"

using namespace std;


int main()
{
	SEG seg_1, seg_2;
	seg_1.read("../seg/snake/snake_2.seg");
	seg_2.read("../seg/snake/all_45.seg");

	//seg_1.to_image("image.png");
	//seg_1.print();

	//Metric *oce = new OCE();
	AOM * aom = new AOM();
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

	for (float i = 0; i <= 1.05; i = i + 0.05)
	{
		//cout << "**************** " << i << endl;
		aom->penality(i);
		//test.classes(mssi, "seg/square", "seg/square");
		//test.chrono(mssi, &seg_1, &seg_2);
		cout << aom->error(&seg_1, &seg_2) << "\t";

	}

	return 0;
}
