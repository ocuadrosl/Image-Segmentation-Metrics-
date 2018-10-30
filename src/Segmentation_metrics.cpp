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
	SEG seg1, seg2;
	seg1.read("input/square_1.seg");
	seg2.read("input/square_2.seg");

	AOM aom;
	aom.setPenality(0.5);
	Jaccard jaccard;
	Dice dice;

	std::cout << aom.compute(seg1, seg1) << std::endl;
	std::cout << jaccard.compute(seg1, seg1) << std::endl;
	std::cout << dice.compute(seg1, seg2) << std::endl;
	std::cout << dice.compute(seg1, seg2) / (2 - dice.compute(seg1, seg2)) << std::endl;
	std::cout << 2 * jaccard.compute(seg1, seg2) / (jaccard.compute(seg1, seg2) + 1) << std::endl;

	return 0;
}
