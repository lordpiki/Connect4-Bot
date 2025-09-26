#include <iostream>
#include "Board.h"
#include <stdint.h>
#include  "BoardSolver.h"
#include "BoardScorer.h"
#include <chrono>

void setup_board(Board& board)
{
	// Initialize the board with some moves
	board.set_red_board(8391062); // Example red pieces
	board.set_yellow_board(98857); // Example yellow pieces
	//board.play(4); // Play a move in column 4
	
}

int main()
{
	Board board;

	setup_board(board); // Set up the board with some initial move

	board.print();
	uint8_t state = BoardScorer::rate_board(board, true); // Rate the board state
	std::cout << "Board state rating: " << static_cast<int>(state) << std::endl; // Print the board state rating

	BoardSolver solver;

	std::cout << "Calculating best move" << std::endl;
	auto start = std::chrono::high_resolution_clock::now();
	auto best_move = solver.calculate_best_move(board, 10); // Calculate the best move for the current board state
	auto end = std::chrono::high_resolution_clock::now();
	auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);
	std::cout << "Best move calculated in " << duration.count() << " ms" << std::endl;

	std::cout << "best cell is " << std::to_string(best_move) << std::endl; // Calculate the best move for the current board state
	return 0;
}
