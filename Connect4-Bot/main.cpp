#include <iostream>
#include "Board.h"
#include <stdint.h>
#include "BoardScorer.h"
#include <chrono>

int main()
{
	Board board;

	board.play(0); // Red plays in column 0
	//board.play(0); // Yellow plays in column 0
	board.print();
	std::cout << "Game State: " << static_cast<int>(board.get_game_state()) << std::endl;

	BoardScorer scorer(board.is_red_turn()); // Scoring for Red player

    auto start = std::chrono::high_resolution_clock::now();
    uint8_t score = scorer.rate_board(board);
    auto end = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count();
    std::cout << "rate_board took " << duration << " ms" << std::endl;

	std::cout << "Minimum moves for Red to win: " << static_cast<int>(score) << std::endl;
	return 0;
}
