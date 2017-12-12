#include "net.h"

Net::Net()
{
}

Net::Net(int inSize, int outSize, std::vector<int>& hiddenSizes, float _learnRate, float _lrDecay)
	: learnRate(_learnRate), lrDecay(_lrDecay)
{
	hidden.push_back(Mat(hiddenSizes.at(0), inSize));
	hidden.at(0).randomize();
	for (unsigned int i = 1; i < hiddenSizes.size(); ++i)
	{
		hidden.push_back(Mat(hiddenSizes.at(i), hiddenSizes.at(i - 1)));
		hidden.at(i).randomize();
	}
	output = Mat(outSize, hiddenSizes.at(hiddenSizes.size() - 1));
	output.randomize();

	count = score = 0;
}

Net::~Net()
{
}

Vec Net::calculate(Vec& input)
{
	result = Vec(input);

	for (unsigned int i = 0; i < hidden.size(); ++i)
	{
		result = Vec(hidden.at(i) * result);
		result.sigmoid();
	}

	result = Vec(output * result);
	result.sigmoid();

	return result;
}

Vec Net::calculateWithInter(Vec & input)
{
	inter.clear();

	result = Vec(input);
	inter.push_back(result);

	for (unsigned int i = 0; i < hidden.size(); ++i)
	{
		result = Vec(hidden.at(i) * result);
		inter.push_back(result);
		result.sigmoid();
	}

	result = Vec(output * result);
	inter.push_back(result);
	result.sigmoid();

	return result;
}

int Net::playGame(TicTacToe game)
{
	while (game.state() == -100)
	{
		calculate(game.getInput());
		result = result & game.getValidMoves();
		int move = result.getMaxIndex();
		game.makeMove(move);
		game.flip();
	}

	return game.state();
}

void Net::gradDesc(MonteCarlo & mc)
{
	MonteCarlo* cm = mc.getDeepest();
	float currentLr = learnRate;
	score += cm->getState();

	do
	{
		cm = cm->getParent();
		Vec x = cm->getInput();
		if (!x.size())
			continue;
		calculateWithInter(cm->getInput());

		Vec spOut = inter.at(inter.size() - 1);
		spOut.sigmoidPrime();
		Vec deltaOut = cm->getCostDerivative() & spOut;
		Vec spHidden = inter.at(inter.size() - 2);
		spHidden.sigmoidPrime();
		Vec deltaHidden = (hidden.at(hidden.size() - 1).transpose() * deltaOut) & spHidden;

		Vec aHidden = inter.at(inter.size() - 2);
		aHidden.sigmoid();
		output = output - ((deltaOut.toMatrix() * aHidden.transpose()) * currentLr);;
		Vec aInput = inter.at(inter.size() - 3);
		aInput.sigmoid();
		hidden.at(0) = hidden.at(0) - ((deltaHidden.toMatrix() * aInput.transpose()) * currentLr);

		currentLr *= lrDecay;
	} while (cm->getParent() != nullptr);

	++count;
	if (!(count % 100))
	{
		std::cout << std::setprecision(3) << (float)score / (float)count << "\t";
		//cm->getDeepest()->printGame();
	}
}
