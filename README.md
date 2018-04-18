Object Oriented Error Measures project
01/2016

Released under the GPL license 3 http://www.gnu.org/licenses/
written by: Oscar Alonso Cuadros Linares
ocuadros@icmc.usp.br

This project aims to implement object-oriented measures to quantitatively compare segmentation files (.seg). Currently, there are three implemented measures: 

1) Alberlaez Error Measure (AEM), Arbelaez et. al. (2009)

2) Object-level Consistency Error (OCE), Polak et. al. (2009) 

3) An Adjustable Object-oriented Error Measure for Image Segmentation Evaluation (AOM), Oscar Cuadros Linares et. al. (2015): This error measure outperforms both AEM and OCE measures, not only in terms of accuracy but also in time processing. Besides, AOM satisfies the three axioms of metric spaces.        

Usage:

Those metrics are implemented in C++, you just should include the header file "metric.h" in your own project. Moreover, we implemented a class to read and write SEG files and a class to measure the processing time. See the example below:


#include "metric.h"


int main()
{

	SEG seg_1, seg_2;
	seg_1.read("input/square_1.seg");
	seg_2.read("input/square_2.seg");

	AOM aom;
	aom.penality(0.5);
	std::cout << aom.error(seg_1, seg_2) << std::endl;

	/*****************/

	Metric *oce = new OCE();
	Metric* arbelaez = new Arbelaez();

	Test test;

	test.chrono(oce, seg_1, seg_2);
	test.chrono(arbelaez, seg_1, seg_2);

	delete oce;
	delete arbelaez;

	return 0;
}
 
TODO:



