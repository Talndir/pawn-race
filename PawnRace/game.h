#pragma once

#include "vec.h"

class Game
{
public:
	Game();
	virtual ~Game();

	virtual Vec getValidMoves();
	virtual void makeMove(int move);
	virtual Vec getInput();
	virtual int state();
	virtual void flip();
	virtual void print();

protected:
	std::vector<std::vector<int>> board;
	int currentPlayer;
};