/*
 * Util.h
 *
 *  Created on: 13/09/2012
 *      Author: oscar
 */

#ifndef UTIL_H_
#define UTIL_H_
#include <vector>
#include <cmath>
#include <iostream>
#include <typeinfo>
#include <sstream>

using namespace std;
/*
 * author oscar
 */
class Util
{
	public:

		static float standard_deviation(float mean, vector<float> values)
		{
			if (values.size() == 0)
			{
				return 0;
			}

			float sum = 0;
			for (unsigned i = 0; i < values.size(); i++)
			{
				sum += pow(values[i] - mean, 2);

			}

			return sqrt(sum / (float) values.size());
		}

		static float mean(vector<float> values)
		{
			if (values.size() == 0)
			{
				return 0;
			}
			float result = 0;
			float size = (float) values.size();
			for (int i = 0; i < size; i++)
			{
				if (values[i] > 0)
				{
					result += values[i];
				}

			}
			result /= size;

			return result;
		}

		static float variance(vector<float> histogram, float mean)
		{
			float result = 0;
			float size = histogram.size();
			for (int i = 0; i < size; i++)
			{
				if (histogram[i] > 0)
				{
					result += pow(histogram[i] - mean, 2);
				}

			}
			result /= size;

			return result;
		}

		static float entropy(vector<float> histogram)
		{
			float result = 0;
			float size = (float) histogram.size();

			for (int i = 0; i < size; i++)
			{
				if (histogram[i] > 0)
				{
					result += (histogram[i] / size) * log2(histogram[i] / size);
				}

			}

			return result;
		}
		static string to_string(int value)
		{
			stringstream string_value;
			string_value << value;
			return string_value.str();

		}

		static string to_string(double value)
		{

			stringstream string_value;
			string_value << value;
			return string_value.str();

		}

		static string to_string(float value)
		{

			stringstream string_value;
			string_value << value;
			return string_value.str();

		}

		static int max(int a, int b)
		{
			if (a > b)
			{
				return a;
			}
			return b;
		}

		static int min(int a, int b)
		{
			if (a < b)
			{
				return a;
			}
			return b;
		}

		static float min(float a, float b)
		{
			return (a < b) ? a : b;

		}

		static int find(int value, vector<int> vector) //vector find
		{
			for (unsigned i = 0; i < vector.size(); i++)
			{
				if (vector[i] == value)
				{
					return i;
				}
			}
			return -1;
		}

};

#endif /* UTIL_H_ */