#include "tictactoe.h"

TicTacToe::TicTacToe()
{
	currentPlayer = 1;
	board = std::vector<std::vector<int>>(3, std::vector<int>(3, 0));
}

TicTacToe::~TicTacToe()
{
}

Vec TicTacToe::getValidMoves()
{
	std::vector<float> v;
	for (unsigned int i = 0; i < board.size(); ++i)
	{
		for (unsigned int j = 0; j < board.at(0).size(); ++j)
			v.push_back(!board.at(i).at(j) ? 1.0 : 0.0);
	}

	return Vec(v);
}

void TicTacToe::makeMove(int move)
{
	int i = move / 3;
	int j = move % 3;
	board.at(i).at(j) = 1;
}

Vec TicTacToe::getInput()
{
	std::vector<float> v1, v2;
	for (unsigned int i = 0; i < board.size(); ++i)
	{
		for (unsigned int j = 0; j < board.at(0).size(); ++j)
		{
			if (!board.at(i).at(j))
			{
				v1.push_back(0.0);
				v2.push_back(0.0);
			}
			else if (board.at(i).at(j) == 1)
			{
				v1.push_back(1.0);
				v2.push_back(0.0);
			}
			else
			{
				v1.push_back(0.0);
				v2.push_back(1.0);
			}
		}
	}

	v1.insert(v1.end(), v2.begin(), v2.end());
	return Vec(v1);
}

int TicTacToe::state()
{
	for (unsigned int i = 0; i < board.size(); ++i)
	{
		if (board.at(i).at(0) == board.at(i).at(1) &&
			board.at(i).at(0) == board.at(i).at(2) &&
			board.at(i).at(0) != 0)
			return board.at(i).at(0);
		if (board.at(0).at(i) == board.at(1).at(i) &&
			board.at(0).at(i) == board.at(2).at(i) &&
			board.at(0).at(i) != 0)
			return board.at(0).at(i);
	}
	if (board.at(0).at(0) == board.at(1).at(1) &&
		board.at(0).at(0) == board.at(2).at(2) &&
		board.at(0).at(0) != 0)
		return board.at(0).at(0);
	if (board.at(0).at(2) == board.at(1).at(1) &&
		board.at(0).at(2) == board.at(2).at(0) &&
		board.at(0).at(2) != 0)
		return board.at(0).at(2);
	
	for (unsigned int i = 0; i < board.size(); ++i)
	{
		for (unsigned int j = 0; j < board.at(0).size(); ++j)
		{
			if (board.at(i).at(j) == 0)
				return -100;
		}
	}

	return 0;
}

void TicTacToe::flip()
{
	for (unsigned int i = 0; i < board.size(); ++i)
	{
		for (unsigned int j = 0; j < board.at(0).size(); ++j)
			board.at(i).at(j) *= -1;
	}

	currentPlayer *= -1;
}

void TicTacToe::print()
{
	for (unsigned int i = 0; i < board.size(); ++i)
	{
		std::string s = "";
		for (unsigned int j = 0; j < board.at(0).size(); ++j)
		{
			switch (board.at(i).at(j) * currentPlayer)
			{
			case  0:
				s += " ";
				break;
			case 1:
				s += "O";
				break;
			case -1:
				s += "X";
				break;
			}
		}

		std::cout << s << std::endl;
	}

	std::cout << std::endl;
}
