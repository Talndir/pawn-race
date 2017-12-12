#pragma once

#include <iostream>
#include <string>
#include "game.h"

class TicTacToe : public Game
{
public:
	TicTacToe();
	~TicTacToe() override;

	Vec getValidMoves() override;
	void makeMove(int move) override;
	Vec getInput() override;
	int state() override;
	void flip() override;
	void print() override;
};