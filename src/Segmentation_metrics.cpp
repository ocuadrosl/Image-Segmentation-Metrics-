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
#include <sys/time.h>
#include <ctime>

using namespace std;

void chrono(Metric* __metric, SEG* __seg_1, SEG* __seg_2)
{
	float result;

	double process_time;
	timeval time;
	gettimeofday(&time, NULL);
	double t_0 = time.tv_sec + (time.tv_usec / 1000000.0);

	result = __metric->compare(__seg_1, __seg_2);

	gettimeofday(&time, NULL);
	double t_1 = time.tv_sec + (time.tv_usec / 1000000.0);

	process_time = t_1 - t_0;

	cout << typeid(*__metric).name() << ": " << result << " time: " << process_time << endl;

}

int main()
{
	SEG seg_1, seg_2;
	seg_1.read("seg/61086.seg_1102");
	seg_2.read("seg/61086.seg_1102");

	Metric *oce = new OCE();
	MSSI * mssi = new MSSI();

	mssi->penality(0);

	chrono(mssi, &seg_1, &seg_2);
	chrono(oce, &seg_1, &seg_2);

	return 0;
}
