#pragma once

#include "TicTacToe.h"

#ifdef _DEBUG
#define new new( _NORMAL_BLOCK , __FILE__ , __LINE__ )
#else
#define new new
#endif

class Net;

class MonteCarlo
{
public:
	MonteCarlo();
	MonteCarlo(float _epsilon, float _degrade, int _maxPlays, bool _isPlayerTurn, TicTacToe _game, Net* _policy, int _preMove, MonteCarlo* _parent);
	~MonteCarlo();

	void run();
	void explore();
	void exploit();
	void play();

	float getNormalScore();
	int getPreMove();
	void updateParent(int newScore);
	void updateFail();
	Vec getCostDerivative();
	Vec getInput();
	MonteCarlo* getParent();
	void printGame();
	MonteCarlo* getDeepest();
	int getState();

private:
	MonteCarlo* parent;
	std::vector<MonteCarlo*> children;
	TicTacToe game;
	Vec input, output, best;
	Net* policy;
	float epsilon, originalEpsilon, degrade;
	int maxPlays, originalMaxPlays;
	int bestAction;
	int plays;
	int score;
	int preMove;
	bool isPlayerTurn;
};