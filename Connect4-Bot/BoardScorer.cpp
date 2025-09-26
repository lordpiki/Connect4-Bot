#include "BoardScorer.h"


uint8_t BoardScorer::rate_board(const Board& board, bool checking_red, uint8_t move_count, uint8_t best)
{
    uint8_t state = check_state(board, checking_red, move_count, checking_red);
    if (state)
    {
        return state;
    }

    for (uint8_t cell = 0; cell < BOARD_WIDTH; ++cell)
    {
		// Check for the available moves
        if (board.is_cell_full(cell))   
        {
            continue; // Skip full columns
        }

        auto new_board = board; // Create a copy of the board to explore this move

        // Play move and get the number of moves required to win
        new_board.play(cell);
        auto score = rate_board(new_board, move_count + (new_board.is_red_turn() == checking_red), best);

        if (score == move_count + 1 && (new_board.is_red_turn() == checking_red)) // Best possible case
        {
            return score;
        }

		best = std::min(best, score);

    }

    return best;
}

bool BoardScorer::state_move_match(GameState state, bool red_move)
{
    return (state == GameState::RedWon && red_move)
        || (state == GameState::YellowWon && !red_move);
}

uint8_t BoardScorer::check_state(const Board& board, bool checking_red, uint8_t move_count, uint8_t best)
{
    if (move_count >= best)
    {
        return best; // No need to continue if we've already found a better solution
    }

	GameState game_state = board.get_game_state();
    if (GameState::InProgress != game_state)
    {
        if (state_move_match(game_state, checking_red))
        {
            return move_count;
        }

        return UINT8_MAX; // Game is over, no further moves can be made
    }

    return 0;
}
