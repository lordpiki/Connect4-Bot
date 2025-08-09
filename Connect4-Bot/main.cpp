#include <iostream>
#include "Board.h"
#include <stdint.h>
#include  "BoardSolver.h"
#include <chrono>

void setup_board(Board& board)
{
	// Initialize the board with some moves
	board.set_red_board(0b111ULL); // Example red pieces
	board.set_yellow_board(0b1110000000ULL); // Example yellow pieces
}

int main()
{
	Board board;

	setup_board(board); // Set up the board with some initial moves

	board.print();
	BoardSolver solver;

	std::cout << "Calculating best move" << std::endl;
	auto start = std::chrono::high_resolution_clock::now();
	auto best_move = solver.calculate_best_move(board, 6); // Calculate the best move for the current board state
	auto end = std::chrono::high_resolution_clock::now();
	auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);
	std::cout << "Best move calculated in " << duration.count() << " ms" << std::endl;

	std::cout << "best cell is " << std::to_string(best_move) << std::endl; // Calculate the best move for the current board state
	return 0;
}
