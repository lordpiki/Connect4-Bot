#include "BoardSolver.h"
#include "BoardScorer.h"

uint8_t BoardSolver::calculate_best_move(const Board& board, uint8_t max_moves)
{
	// If the game ended
	uint8_t best_move = 0;
	int32_t best_score = 0;
	for (uint8_t cell = 0; cell < BOARD_WIDTH; cell++)
	{
		if (board.is_cell_full(cell))
		{
			continue; // Skip full columns
		}
		auto new_board = board; // Create a copy of the board to explore this move
		// Play move and get the score for the next depth
		new_board.play(cell);
		
		int32_t score = minimax(new_board, max_moves - 1, INT32_MIN, INT32_MAX, true);
		if (score > best_score)
		{
			best_score = score;
			best_move = cell; // Update the best move
		}
	}
	return best_move;
}

int32_t BoardSolver::minimax(const Board& board, uint8_t max_depth, int32_t alpha, int32_t beta, bool maximizing_player)
{
	auto game_state = board.get_game_state();
	auto score_muiltiplier = maximizing_player ? 1 : -1;


	if (GameState::InProgress != game_state)
	{
		if (GameState::Draw == game_state)
		{
			return 0; // Draw, no score
		}
		
		// Encourage to win in as few moves as possible
		// Score = number of empty cells left
		return (BOARD_HEIGHT * BOARD_WIDTH - board.get_num_moves()) * score_muiltiplier;
	}

	if (max_depth == 0)
	{
		BoardScorer scorer(board.is_red_turn());
		// Staticly evaluate the board
		// Guess how many moves are left to win
		return (BOARD_HEIGHT * BOARD_WIDTH - scorer.rate_board(board, 0)) * score_muiltiplier;
	}

	int32_t best_score = maximizing_player ? INT32_MIN : INT32_MAX;

	for (uint8_t cell = 0; cell < BOARD_WIDTH; cell++)
	{
		if (board.is_cell_full(cell))
		{
			continue; // Skip full columns
		}
		auto new_board = board; // Create a copy of the board to explore this move
		// Play move and get the score for the next depth
		new_board.play(cell);

		int32_t score = minimax(new_board, max_depth - 1, alpha, beta, !maximizing_player);
		if (maximizing_player)
		{
			best_score = std::max(best_score, score); // Maximizing player wants the highest score
			alpha = std::max(alpha, best_score);
			if (beta <= alpha)
			{
				break; // Beta cut-off
			}
		}
		else
		{
			best_score = std::min(best_score, score); // Minimizing player wants the lowest score
			beta = std::min(beta, best_score);
			if (beta <= alpha)
			{
				break; // Alpha cut-off
			}
		}
	}

	return best_score;

}
