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

#ifndef SEG_H_
#define SEG_H_

#include <iostream>
#include <vector>
#include <string>
#include <fstream>

using namespace std;

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

	typedef vector<vector<int> > region_t; //region row

	SEG();

	void read(string __file_name);

	void print();

	region_t &operator[](int __index);
	region_t operator[](int __index) const;
	int size() const;

	int width() const;
	int height() const;
	void to_image(string __file_name);

private:
	string _format; // {*ascii|binary} {*cr|map}
	string _date; // <date string>
	string _image_name; // <int>	# image ID name
	string _user_id; // <int>	# user ID number
	int _width; // <int>	# width of image
	int _height; // <int>	# height of image
	int numberOfSegments; // <int>	# number of segments
	bool _gray; // {*0|1}	# image presented in grayscale?
	bool _invert; // {*0|1}	# image presented with pixel values inverted?
	bool _flipflop; // {*0|1}	# image presented upside-down and backwards?

	vector<region_t> _segments;

};

SEG::SEG()
{
	_width = 0; // <int>	# width of image
	_height = 0; // <int>	# height of image
	numberOfSegments = 0; // <int>	# number of segments
	_gray = 0; // {*0|1}	# image presented in grayscale?
	_invert = 0; // {*0|1}	# image presented with pixel values inverted?
	_flipflop = 0;

}

int SEG::width() const
{
	return _width;
}

int SEG::height() const
{
	return _height;
}

int SEG::size() const
{
	return _segments.size();

}
void SEG::print()
{
	for (unsigned i = 0; i < _segments.size(); i++) //segments
	{
		for (unsigned j = 0; j < _segments[i].size(); j++) //regions
		{
			cout << i << " " << _segments[i][j][0] << " " << _segments[i][j][1] << " " << _segments[i][j][2] << endl;
		}
	}

}

SEG::region_t &SEG::operator [](int __index)
{

	return _segments[__index];

}

SEG::region_t SEG::operator [](int __index) const
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
	file >> numberOfSegments;

	//trash data
	file >> trash;
	file >> trash;
	file >> trash;
	file >> trash;
	file >> trash;
	file >> trash;
	file >> trash;

	_segments.resize(numberOfSegments);
	/*auxiliary declarations*/

	int segIndex;
	int row;
	int col_0;
	int col_1;
	while (file.good())
	{
		file >> segIndex;
		file >> row;
		file >> col_0;
		file >> col_1;
		if (file.good())
		{
			_segments[segIndex].resize(_segments[segIndex].size() + 1); //3

			_segments[segIndex][_segments[segIndex].size() - 1].push_back(row);
			_segments[segIndex][_segments[segIndex].size() - 1].push_back(col_0);
			_segments[segIndex][_segments[segIndex].size() - 1].push_back(col_1);
		}

	}

	//cout << _segments.size() << " size" << endl;

	file.close();
}

#endif /* SEG_H_ */
