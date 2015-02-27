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
#include "Arbelaez.h"
#include "Metric.h"
#include <sys/time.h>
#include <ctime>
#include <typeinfo>

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
	seg_1.read("seg/frutas_1.seg");
	seg_2.read("seg/frutas_2.seg");

	Metric *oce = new OCE();
	MSSI * mssi = new MSSI();
	Metric* arbelaez = new Arbelaez();

	mssi->penality(0);

	chrono(mssi, &seg_1, &seg_2);
	chrono(oce, &seg_1, &seg_2);
	chrono(arbelaez, &seg_1, &seg_2);
	chrono(arbelaez, &seg_2, &seg_1);

	return 0;
}
