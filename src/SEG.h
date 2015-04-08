/*
 * SEG.h
 *
 *  Created on: 12/2/2015
 *      Author: oscar
 */

#ifndef SEG_H_
#define SEG_H_

#include <iostream>
#include <vector>
#include <string>
#include <fstream>

#include <cv.h>
#include <opencv2/opencv.hpp>
#include <highgui.h>


using namespace std;
using namespace cv;

typedef vector<vector<int> > reg_t; //region row

/*
 * SEG files
 * 1: label
 * 2: row:
 * 3: col begin
 * 4: col end
 *
 *
 */
class SEG
{
	public:

		SEG()
		{
		}
		;

		void read(string __file_name);

		void print();

		reg_t &operator[](int __index);
		int size();

		int width();
		int height();
		void to_image(string __file_name);

	private:
		string _format; // {*ascii|binary} {*cr|map}
		string _date; // <date string>
		string _image_name; // <int>	# image ID name
		string _user_id; // <int>	# user ID number
		int _width; // <int>	# width of image
		int _height; // <int>	# height of image
		int _segments_number; // <int>	# number of segments
		bool _gray; // {*0|1}	# image presented in grayscale?
		bool _invert; // {*0|1}	# image presented with pixel values inverted?
		bool _flipflop; // {*0|1}	# image presented upside-down and backwards?

		vector<reg_t> _segments;

};

void SEG::to_image(string __file_name)
{

	Mat image(_height, _width, CV_8UC3, Scalar(255, 255, 255));

	for (unsigned i = 0; i < _segments.size(); i++)
	{

		for (unsigned j = 0; j < _segments[i].size(); j++)
		{
			image.at<Vec3b>(_segments[i][j][0], _segments[i][j][1])[0] = 0;
			image.at<Vec3b>(_segments[i][j][0], _segments[i][j][2])[0] = 0;

			image.at<Vec3b>(_segments[i][j][0], _segments[i][j][1])[1] = 0;
			image.at<Vec3b>(_segments[i][j][0], _segments[i][j][2])[1] = 0;

			image.at<Vec3b>(_segments[i][j][0], _segments[i][j][1])[2] = 0;
			image.at<Vec3b>(_segments[i][j][0], _segments[i][j][2])[2] = 0;

		}

	}

	imwrite(__file_name, image);

}

int SEG::width()
{
	return _width;
}

int SEG::height()
{
	return _height;
}

int SEG::size()
{
	return _segments.size();

}
void SEG::print()
{
	for (unsigned i = 0; i < _segments.size(); i++)
	{
		for (unsigned j = 0; j < _segments[i].size(); j++)
		{
			cout << i << " " << _segments[i][j][0] << " " << _segments[i][j][1] << " " << _segments[i][j][2] << endl;
		}
	}

}

reg_t &SEG::operator [](int __index)
{

	return _segments[__index];

}

void SEG::read(string __file_name)
{

	_segments.clear();

	ifstream file(__file_name.c_str());

	char trash[256]; //to trash lines

	file.getline(trash, 256);
	file.getline(trash, 256);

	file >> trash;
	file >> _image_name;

	file >> trash;
	file >> _user_id;

	file >> trash;
	file >> _width;

	file >> trash;
	file >> _height;

	file >> trash;
	file >> _segments_number;

	//trash data
	file >> trash;
	file >> trash;
	file >> trash;
	file >> trash;
	file >> trash;
	file >> trash;
	file >> trash;

	_segments.resize(_segments_number);
	/*auxiliary declarations*/

	int seg_pos;
	int row;
	int col_0;
	int col_1;
	while (file.good())
	{
		file >> seg_pos;
		file >> row;
		file >> col_0;
		file >> col_1;
		if (file.good())
		{
			_segments[seg_pos].resize(_segments[seg_pos].size() + 1);
			_segments[seg_pos][_segments[seg_pos].size() - 1].push_back(row);
			_segments[seg_pos][_segments[seg_pos].size() - 1].push_back(col_0);
			_segments[seg_pos][_segments[seg_pos].size() - 1].push_back(col_1);
		}

	}

	//cout << _segments.size() << " size" << endl;

	file.close();
}

#endif /* SEG_H_ */
