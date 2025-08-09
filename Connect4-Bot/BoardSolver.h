#pragma once
#include "Board.h"

class BoardSolver
{
public:

	// Function to calculate the best move to play for the current player
	uint8_t calculate_best_move(const Board& board, uint8_t max_moves);

private:
	
	// Minimax algorithm to evaluate the board state
	// Returns the score of the board for the maximizing player
	int32_t minimax(const Board& board, uint8_t depth, int32_t alpha, int32_t beta, bool maximizing_player);
};

