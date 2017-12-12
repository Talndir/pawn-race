//#include <vld.h>

#include <time.h>
#include "montecarlo.h"
#include "net.h"

int main()
{
	std::srand(time(NULL));
	
	Net p(9, 9, std::vector<int> {9}, 0.01, 0.9);
	TicTacToe game;
	MonteCarlo mcts;
	
	
	for (unsigned int i = 0; i < 1000000; ++i)
	{
		game = TicTacToe();
		mcts = MonteCarlo(0.95, 0.95, 50, true, game, &p, -1, nullptr);
		mcts.run();
		p.gradDesc(mcts);
		//std::cout << i << std::endl;
	}
	
	std::cin.ignore();
	return 0;
}