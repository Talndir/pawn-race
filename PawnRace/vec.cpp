#include "vec.h"
#include "mat.h"

Vec::Vec()
{
}

Vec::Vec(int rows)
{
	vector = std::vector<float>(rows, 0);
}

Vec::Vec(std::vector<float>& values)
{
	vector = std::vector<float>(values);
}

Vec::~Vec()
{
}

int Vec::size() const
{
	return vector.size();
}

void Vec::sigmoid()
{
	for (unsigned int i = 0; i < vector.size(); ++i)
		vector[i] = 1 / (1 + std::exp(-vector[i]));
}

void Vec::sigmoidPrime()
{
	for (unsigned int i = 0; i < vector.size(); ++i)
	{
		float z = exp(vector[i]) + 1;
		vector[i] = (z - 1) / (z * z);
	}
}

void Vec::randomize()
{
	for (unsigned int i = 0; i < vector.size(); ++i)
		vector.at(i) = (((float)std::rand() / (float)RAND_MAX) * 2.f) - 1.f;
}

float Vec::lengthSq()
{
	float r = 0.0;
	for (unsigned int i = 0; i < vector.size(); ++i)
		r += vector[i] * vector[i];
	return r;
}

float Vec::length()
{
	return std::sqrt(lengthSq());
}

int Vec::getMaxIndex()
{
	return std::distance(vector.begin(), std::max_element(vector.begin(), vector.end()));
}

Mat Vec::transpose()
{
	std::vector<float> vs;
	for (int i = 0; i < vector.size(); ++i)
		vs.push_back(vector[i]);
	return Mat(std::vector<Vec> {Vec(vs)});
}

Mat Vec::toMatrix()
{
	std::vector<Vec> vs;
	for (int i = 0; i < vector.size(); ++i)
		vs.push_back(Vec(std::vector<float> {vector.at(i)}));
	return Mat(vs);
}

float & Vec::operator[](int index)
{
	return vector.at(index);
}

float Vec::operator[](int index) const
{
	return vector.at(index);
}

float Vec::operator*(const Vec & v)
{
	float r = 0.0;
	if (vector.size() != v.size())
		return r;

	for (int i = 0; i < vector.size(); ++i)
		r += vector[i] * v[i];

	return r;
}

Vec Vec::operator*(const float & v)
{
	std::vector<float> vs;
	for (int i = 0; i < vector.size(); ++i)
		vs.push_back(vector[i] * v);
	return Vec(vs);
}

Vec Vec::operator-(const Vec & v)
{
	Vec r(v.size());
	if (vector.size() != v.size())
		return r;

	for (int i = 0; i < v.size(); ++i)
		r[i] = vector[i] - v[i];

	return r;
}

Vec Vec::operator&(const Vec & v)
{
	Vec r(v.size());
	if (vector.size() != v.size())
		return r;

	for (int i = 0; i < v.size(); ++i)
		r[i] = vector[i] * v[i];

	return r;
}
