#pragma once

#include <vector>
#include <iterator>
#include <algorithm>

class Mat;

class Vec
{
public:
	Vec();
	Vec(int rows);
	Vec(std::vector<float>& values);
	~Vec();

	int size() const;
	void sigmoid();
	void sigmoidPrime();
	void randomize();
	float lengthSq();
	float length();
	int getMaxIndex();
	Mat transpose();
	Mat toMatrix();

	float& operator[] (int index);
	float operator[] (int index) const;
	float operator* (const Vec& v);
	Vec operator* (const float& v);
	Vec operator- (const Vec& v);
	Vec operator& (const Vec& v);

private:
	std::vector<float> vector;
};