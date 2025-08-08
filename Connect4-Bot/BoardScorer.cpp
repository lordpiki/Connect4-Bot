#include "BoardScorer.h"


uint8_t BoardScorer::rate_board(const Board& board, uint8_t move_count)
{
    uint8_t state = check_state(board, move_count);
    if (state)
    {
        return state;
    }

    for (uint8_t cell = 0; cell < BOARD_WIDTH; ++cell)
    {
        if (board.is_cell_full(cell))
        {
            continue; // Skip full columns
        }

        auto new_board = board; // Create a copy of the board to explore this move

        // Play move and get the number of moves required to win
        new_board.play(cell);
        auto score = rate_board(new_board, move_count + (new_board.is_red_turn() == m_checkingRed));

        // Store the result in cache before returning
        m_cache.cache[{new_board.get_red_board(), new_board.get_yellow_board()}] = score;

        if (score == move_count + 1 && (new_board.is_red_turn() == m_checkingRed)) // Best possible case
        {
            return score;
        }

        update_min_moves(score);
    }

    return m_minMoves;
}

bool BoardScorer::state_move_match(GameState state, bool red_move)
{
    return (state == GameState::RedWon && red_move)
        || (state == GameState::YellowWon && !red_move);
}

uint8_t BoardScorer::check_state(const Board& board, uint8_t move_count) const
{
    if (move_count >= m_minMoves)
    {
        return m_minMoves; // No need to continue if we've already found a better solution
    }

    auto it = m_cache.cache.find({ board.get_red_board(), board.get_yellow_board() });
    if (it != m_cache.cache.end())
    {
        return it->second;
    }

	GameState game_state = board.get_game_state();
    if (GameState::InProgress != game_state)
    {
        if (state_move_match(game_state, m_checkingRed))
        {
            return move_count;
        }

        return UINT8_MAX; // Game is over, no further moves can be made
    }

    return 0;
}

void BoardScorer::update_min_moves(uint8_t moves)
{
    if (moves < m_minMoves) 
    {
        m_minMoves = moves; // Update the minimum moves if a better solution is found
    }
}
