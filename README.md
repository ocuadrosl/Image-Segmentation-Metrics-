Object Oriented Error Measures project

Released under the GPL licence 3 http://www.gnu.org/licenses/
written by: Oscar Alonso Cuadros Linares
ocuadros@icmc.usp.br

This project aims to implement object-oriented measures to quantify the quality of  image segmentation algorithms. Currently there are three implemented measures: 

1) Alberlaez Error Measure (AEM), Arbelaez et. al. (2009)

2) Object-level Consistency Error (OCE), Polak et. al. (2009) 

3) An Adjustable Error Measure for Image Segmentation Evaluation (AOM), Oscar Cuadros Linares et. al. (2015): This error measure outperforms both AEM and OCE measures, not only terms of accuracy but also in time processing. Also, AOM satisfies the three axioms of metric spaces.        

Usage:

This project is implemented in C++, you only have to include the header file "metric.h" into your own project. Besides, we implemented a class to reading and writting SEG files and  a class to measure the processing time. See the example below:


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



