#pragma once
#include <map>
#include <stdint.h>
#include "Board.h"

class ScoreCache
{
public:
	inline static std::map<std::pair<uint64_t, uint64_t>, uint8_t> cache;
};

class BoardScorer
{
public:
	BoardScorer(bool checking_red) : m_minMoves(UINT8_MAX), m_checkingRed(checking_red) {}

	// Function calculates the min number of moves required to win
	uint8_t rate_board(const Board& board, uint8_t move_count = 1);

	// Function checks if the current state of the board matches the game state
	static bool state_move_match(GameState state, bool red_move);


private:
	uint8_t m_minMoves;
	bool m_checkingRed;
	// (red_board, yellow_board) : min_moves
	 ScoreCache m_cache; // Cache to store previously computed results

	// Checks if the function should return the current state of the board
	// Returns UINT8_MAX if the game is over or if the current state does not match the expected state
	// Otherwise, returns min_moves
	uint8_t check_state(const Board& board, uint8_t move_count) const;
	void update_min_moves(uint8_t moves);
};