#pragma once

#include <iomanip>

#include "mat.h"
#include "tictactoe.h"
#include "montecarlo.h"

class Net
{
public:
	Net();
	Net(int inSize, int outSize, std::vector<int>& hiddenSizes, float _learnRate, float _lrDecay);
	~Net();

	Vec calculate(Vec& input);
	Vec calculateWithInter(Vec& input);
	int playGame(TicTacToe game);

	void gradDesc(MonteCarlo& mc);

private:
	std::vector<Mat> hidden;
	Mat output;
	Vec result;
	std::vector<Vec> inter;
	float learnRate, lrDecay;
	int count, score;
};