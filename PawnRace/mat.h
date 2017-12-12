#pragma once

#include <vector>
#include "vec.h"

class Mat
{
public:
	Mat();
	Mat(int rows, int columns);
	Mat(std::vector<Vec>& values);
	~Mat();

	void randomize();
	Mat transpose();

	Vec& operator[] (int index);
	Vec operator[] (int index) const;
	Vec operator* (const Vec& v);
	Mat operator- (const Mat& v);
	Mat operator* (const float& v);
	Mat operator* (const Mat& v);

private:
	std::vector<Vec> matrix;
};