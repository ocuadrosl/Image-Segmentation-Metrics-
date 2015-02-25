//============================================================================
// Name        : Segmentation_metrics.cpp
// Author      : Oscar
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>
#include "SEG.h"

#include "OCE.h"
#include "MSSI.h"
#include "Metric.h"
using namespace std;

void foo(Metric* __metric, SEG* __seg_1, SEG* __seg_2)
{

	cout << __metric->compare(__seg_1, __seg_2) << endl;
}

int main()
{
	SEG seg_1, seg_2;
	seg_1.read("seg/61086.seg_1102");
	seg_2.read("seg/61086.seg_1130");

	Metric *oce = new OCE();
	MSSI * mssi = new MSSI();

	mssi->penality(0.1);

	foo(mssi, &seg_1, &seg_2);
	foo(oce, &seg_1, &seg_2);

	return 0;
}
