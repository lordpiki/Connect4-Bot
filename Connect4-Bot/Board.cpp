#include "Board.h"
#include <stdexcept>
#include <iostream>
#include <string>

void Board::play(uint8_t cell)
{
	if (cell >= BOARD_WIDTH) {
		throw std::out_of_range("Cell index out of range");
	}

	if (m_column_heights[cell] > BOARD_HEIGHT) {
		throw std::invalid_argument("Column is full, cannot play here");
	}

	auto& current_board = m_red_move ? m_red_board : m_yellow_board;

	current_board |= (1ULL << (cell + m_column_heights[cell] * BOARD_WIDTH));
	switch_turn();

	m_column_heights[cell]++; 
	m_num_moves++;

}

bool Board::is_cell_full(uint8_t cell) const
{
	if (cell >= BOARD_WIDTH) {
		throw std::out_of_range("Cell index out of range");
	}

	return m_column_heights[cell] >= BOARD_HEIGHT;
}

GameState Board::get_game_state() const
{
	if (m_num_moves == BOARD_WIDTH * BOARD_HEIGHT)
	{
		return GameState::Draw; // Board is full, it's a draw
	}

	if (check_win(m_red_board))
	{
		return GameState::RedWon; // Red player has won
	}
	if (check_win(m_yellow_board))
	{
		return GameState::YellowWon; // Yellow player has won
	}

	return GameState::InProgress;
}

uint8_t Board::get_available_moves_mask() const
{
	uint8_t mask = 0;
	for (uint8_t col = 0; col < BOARD_WIDTH; ++col)
	{
		if (m_column_heights[col] <= BOARD_HEIGHT)
		{
			mask |= (1 << col); // Set the bit for available columns
		}
	}
	return mask;
}

void Board::print()
{
	// Print the entire board, with red and yellow pieces represented by 'X' and 'O'
	std::cout << "Current Board State:\n";
	for (int8_t row = BOARD_HEIGHT - 1; row >= 0; --row) {
		for (uint8_t col = 0; col < BOARD_WIDTH; ++col) {
			uint8_t cell_index = row * BOARD_WIDTH + col;
			if (m_red_board & (1ULL << cell_index)) {
				std::cout << 'X'; // Red piece
			} else if (m_yellow_board & (1ULL << cell_index)) {
				std::cout << 'O'; // Yellow piece
			} else {
				std::cout << '.'; // Empty cell
			}
		}
		std::cout << '\n';
	}
}

bool Board::check_win(uint64_t board)
{
	// Check horizontal, vertical, and diagonal connections for a win
	return check_vertical_win(board)
		|| check_horizontal_win(board)
		|| check_diagonal(board);
}

bool Board::check_vertical_win(uint64_t board)
{
	auto vertical_mask = 0b1000000100000010000001ULL;

	for (uint8_t offset = 0; offset < BOARD_HEIGHT - 3; offset++)
	{
		for (uint8_t col = 0; col < BOARD_WIDTH; col++)
		{
			uint64_t col_mask = vertical_mask << col + offset * BOARD_WIDTH;
			if ((board & col_mask) == col_mask)
			{
				return true;
			}
		}
	}

	return false;
}

bool Board::check_horizontal_win(uint64_t board)
{
	auto horizontal_mask = 0b1111ULL;

	for (uint8_t offset = 0; offset < BOARD_WIDTH - 3; offset++)
	{
		for (uint8_t row = 0; row < BOARD_HEIGHT; row++)
		{
			uint64_t row_mask = horizontal_mask << (row * BOARD_WIDTH + offset);
			if ((board & row_mask) == row_mask)
			{
				return true;
			}
		}
	}


	return false;
}

bool Board::check_diagonal(uint64_t board)
{
	auto diagonal_mask1 = 0b1000000010000000100000001ULL;
	auto diagonal_mask2 = 0b1000001000001000001000ULL;

	for (uint8_t offset = 0; offset < BOARD_HEIGHT - 4; offset++)
	{
		for (int8_t row = 0; row < 4; row++)
		{
			uint64_t diagonal1 = diagonal_mask1 << row + offset * BOARD_WIDTH;
			uint64_t diagonal2 = diagonal_mask2 << row + offset * BOARD_WIDTH;
			// Check if the diagonal matches the board
			if ((board & diagonal1) == diagonal1 || (board & diagonal2) == diagonal2)
			{
				return true;
			}
		}
	}

	return false;
}

