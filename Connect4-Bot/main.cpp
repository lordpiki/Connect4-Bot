#include <iostream>
#include "Board.h"
#include <stdint.h>


int main()
{
	Board board;
	for (int i = 0; i < 4; ++i) {
		board.play(i);
		board.play(i);
	}


	board.print();
	board.unplay(0);
	board.print();
	board.unplay(0);
	board.print();
	std::cout << "Game State: " << static_cast<int>(board.get_game_state()) << std::endl;

}
