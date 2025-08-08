#pragma once
#include "Board.h"

class BoardSolver
{
public:
	BoardSolver(const Board& board)
		: m_board(board) {
	}

	// Function to calculate the best move to play for the current player
	uint8_t calculate_best_move(uint8_t max_moves);

private:
	Board m_board; 
};

