#pragma once
#include <unordered_map>
#include <stdint.h>
#include "Board.h"



class BoardScorer
{
public:

	// Function calculates the min number of moves required to win
	static uint8_t rate_board(const Board& board, bool checking_red, uint8_t move_count = 1,  uint8_t best = UINT8_MAX);

	// Function checks if the current state of the board matches the game state
	static bool state_move_match(GameState state, bool red_move);


private:
	// (red_board, yellow_board) : min_moves

	// Checks if the function should return the current state of the board
	// Returns UINT8_MAX if the game is over or if the current state does not match the expected state
	// Otherwise, returns min_moves
	static uint8_t check_state(const Board& board, bool checking_red, uint8_t move_count, uint8_t best);
	
};