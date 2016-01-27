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

#ifndef TEST_H_
#define TEST_H_

#include "Metric.h"
#include <sys/time.h>
#include <ctime>
#include <typeinfo>
#include <string>
#include <sys/stat.h>

#include <iostream>

#include <dirent.h>

using namespace std;

/*
 *
 * Test functions
 *
 * */

class Test
{

	public:

		typedef vector<vector<double> > matrix_d; //matrix of doubles	Test()
		Test()
		{
		}
		;

		~Test()
		{
		}
		;

		double chrono(Metric* __metric, SEG __seg_1, SEG __seg_2);

		/*compare all human segmentations between two images
		 * todo exceptions
		 *
		 * */

		void classes(Metric* __metric, string __directory_1, string __directory_2);

	private:

		vector<string> directory_files(string __directory); //return a list of filenames from a given directory

};

vector<string> Test::directory_files(string __directory)
{
	vector<string> files;

	DIR *dp;
	struct dirent *dirp;
	if ((dp = opendir((__directory).c_str())) == NULL)
	{
		cout << "Error" << endl;
	}

	while ((dirp = readdir(dp)) != NULL)
	{
		if (string(dirp->d_name).compare(".") != 0 && string(dirp->d_name).compare("..") != 0)
		{
			//cout << __directory + "/" + dirp->d_name << endl;
			files.push_back(__directory + "/" + dirp->d_name);

		}
		else
		{
			//cout << "image error" << endl; //??

		}

	}
	closedir(dp);

	sort(files.begin(), files.end());
	return files;

}

void Test::classes(Metric* __metric, string __directory_1, string __directory_2)
{

	vector<string> files_1, files_2;
	files_1 = directory_files(__directory_1);
	files_2 = directory_files(__directory_2);

	vector<double> row(files_2.size(), -1);

	matrix_d distances(files_1.size(), row);

	SEG seg_1, seg_2;

	cout << "d=[";

	for (unsigned i = 0; i < distances.size(); i++)
	{
		seg_1.read(files_1[i]);

		//cout << files_1[i] << endl;

		for (unsigned j = 0; j < distances[0].size(); j++)
		{

			seg_2.read(files_2[j]);

			distances[i][j] = __metric->error(seg_1, seg_2);

			cout << distances[i][j] << " ";

		}
		cout << endl;

	}

	cout << "];";

}

double Test::chrono(Metric* __metric, SEG __seg_1, SEG __seg_2)
{
	double result;

	double process_time;
	timeval time;
	gettimeofday(&time, NULL);
	double t_0 = time.tv_sec + (time.tv_usec / 1000000.0);

	result = __metric->error(__seg_1, __seg_2);

	gettimeofday(&time, NULL);
	double t_1 = time.tv_sec + (time.tv_usec / 1000000.0);

	process_time = t_1 - t_0;

	cout << typeid(*__metric).name() << ": " << result << " time: " << process_time << endl;

	return process_time;

}

#endif /* TEST_H_ */
