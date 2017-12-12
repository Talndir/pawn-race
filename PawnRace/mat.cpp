#include "mat.h"

Mat::Mat()
{
}

Mat::Mat(int rows, int columns)
{
	matrix = std::vector<Vec>(rows, Vec(columns));
}

Mat::Mat(std::vector<Vec>& values)
{
	matrix = std::vector<Vec>(values);
}

Mat::~Mat()
{
}

void Mat::randomize()
{
	for (unsigned int i = 0; i < matrix.size(); ++i)
		matrix.at(i).randomize();
}

Mat Mat::transpose()
{
	std::vector<float> v;
	std::vector<Vec> vs;
	for (unsigned int i = 0; i < matrix.at(0).size(); ++i)
	{
		for (unsigned int j = 0; j < matrix.size(); ++j)
			v.push_back(matrix[j][i]);

		vs.push_back(v);
		v.clear();
	}

	return Mat(vs);
}

Vec & Mat::operator[](int index)
{
	return matrix[index];
}

Vec Mat::operator[](int index) const
{
	return matrix[index];
}

Vec Mat::operator*(const Vec & v)
{
	Vec r(matrix[0].size());
	if (v.size() != matrix[0].size())
		return r;

	for (unsigned int i = 0; i < matrix.size(); ++i)
		r[i] = matrix[i] * v;

	return r;
}

Mat Mat::operator-(const Mat & v)
{
	std::vector<Vec> vs;
	for (unsigned int i = 0; i < matrix.size(); ++i)
		vs.push_back(matrix[i] - v[i]);
	return Mat(vs);
}

Mat Mat::operator*(const float & v)
{
	std::vector<Vec> vs;
	for (unsigned int i = 0; i < matrix.size(); ++i)
		vs.push_back(matrix[i] * v);
	return Mat(vs);
}

Mat Mat::operator*(const Mat & v)
{
	std::vector<float> val;
	std::vector<Vec> vs;
	Mat trans = Mat(v).transpose();
	trans.transpose();

	for (unsigned int i = 0; i < matrix.size(); ++i)
	{
		for (unsigned int j = 0; j < matrix.size(); ++j)
			val.push_back(matrix[i] * trans[j]);
		vs.push_back(val);
		val.clear();
	}

	return Mat(vs);
}
