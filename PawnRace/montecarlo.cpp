#include "montecarlo.h"
#include "net.h"

MonteCarlo::MonteCarlo()
{
}

MonteCarlo::MonteCarlo(float _epsilon, float _degrade, int _maxPlays, bool _isPlayerTurn, TicTacToe _game, Net* _policy, int _preMove, MonteCarlo* _parent)
	: epsilon(_epsilon), degrade(_degrade), maxPlays(_maxPlays), isPlayerTurn(_isPlayerTurn), game(_game), policy(_policy), preMove(_preMove), parent(_parent)
{
	bestAction = -1;
	plays = 0;
	score = 0;
	originalEpsilon = epsilon;
	originalMaxPlays = maxPlays;

	//if (!isPlayerTurn)
		//maxPlays *= 1.5;
}

MonteCarlo::~MonteCarlo()
{
	for (unsigned int i = 0; i < children.size(); ++i)
		delete children.at(i);
}

void MonteCarlo::run()
{
	//game.print();

	if (game.state() == -100)
	{
		while (plays < maxPlays)
		{
			float r = (float)std::rand() / (float)RAND_MAX;

			if (r < epsilon)
				explore();
			else
				exploit();
		}

		input = game.getInput();
		output = policy->calculate(input);
		best = output;

		if (children.size())
		{
			int move = -1;
			float normScore = -2.f;
			int index = -1;
			int mul;
			isPlayerTurn ? mul = 1 : mul = -1;
			for (unsigned int i = 0; i < children.size(); ++i)
			{
				if (children.at(i)->getNormalScore() * mul > normScore)
				{
					normScore = children.at(i)->getNormalScore();
					move = children.at(i)->getPreMove();
					index = i;
				}
			}

			best[move] = 1.0;
			auto c2 = std::vector<MonteCarlo*>(1, children.at(index));
			for (unsigned int i = 0; i < children.size(); ++i)
			{
				if (i != index)
					delete children.at(i);
			}
			children = c2;
			children.at(0)->run();
		}
	}
}

void MonteCarlo::explore()
{
	int r = 0;

	if (!children.size())
		true; //plays = score = r = 0;
	else
		r = std::rand() % (children.size() + 1);

	if (r == children.size())
	{
		Vec v = game.getValidMoves();
		std::vector<int> moves;

		for (int i = 0; i < v.size(); ++i)
		{
			if (v[i] > 0.0f)
				moves.push_back(i);
		}

		if (moves.size())
		{
			int move = moves.at(std::rand() % moves.size());
			TicTacToe nextTicTacToe = this->game;
			nextTicTacToe.makeMove(move);
			nextTicTacToe.flip();
			MonteCarlo* next = new MonteCarlo(originalEpsilon, degrade, originalMaxPlays, !isPlayerTurn, nextTicTacToe, policy, move, this);
			next->play();
			children.push_back(next);

			epsilon *= degrade;
		}
		else
			updateFail();
	}
	else
		children.at(r)->explore();
}

void MonteCarlo::exploit()
{
	if (!children.size())
		explore();
	else
	{
		int index = -1;
		float score = -2.f;
		for (unsigned int i = 0; i < children.size(); ++i)
		{
			if (children.at(i)->getNormalScore() > score)
			{
				score = children.at(i)->getNormalScore();
				index = i;
			}
		}

		children.at(index)->exploit();
	}
}

void MonteCarlo::play()
{
	score = policy->playGame(game);
	if (!isPlayerTurn)
		score *= -1;
	plays = 1;

	if (parent != nullptr)
		parent->updateParent(score * -1);
}

float MonteCarlo::getNormalScore()
{
	return float(score / plays);
}

int MonteCarlo::getPreMove()
{
	return preMove;
}

void MonteCarlo::updateParent(int newScore)
{
	score += newScore;
	++plays;

	if (parent != nullptr)
		parent->updateParent(newScore * -1);
}

void MonteCarlo::updateFail()
{
	--maxPlays;

	if (parent != nullptr)
		parent->updateFail();
}

Vec MonteCarlo::getCostDerivative()
{
	return output - best;
}

Vec MonteCarlo::getInput()
{
	return input;
}

MonteCarlo * MonteCarlo::getParent()
{
	return parent;
}

void MonteCarlo::printGame()
{
	game.print();
}

MonteCarlo * MonteCarlo::getDeepest()
{
	if (children.size())
		return children.at(0)->getDeepest();
	else
		return this;
}

int MonteCarlo::getState()
{
	return game.state();
}
