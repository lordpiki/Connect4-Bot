#include "Board.h"
#include <stdexcept>
#include <iostream>
#include <string>

bool Board::checkWinForColor(bool isRed) const
{
    uint64_t board = isRed ? red_board : yellow_board;

    // Horizontal check
    uint64_t h = board & (board >> 1);
    if (h & (h >> 2)) return true;

    // Vertical check
    uint64_t v = board & (board >> BOARD_HEIGHT);
    if (v & (v >> (2 * BOARD_HEIGHT))) return true;

    // Diagonal \ check
    uint64_t diagonal1 = board & (board >> (BOARD_WIDTH + 1));
    if (diagonal1 & (diagonal1 >> (2 * (BOARD_WIDTH + 1)))) return true;

    // Diagonal / check
    uint64_t diagonal2 = board & (board >> (BOARD_WIDTH - 1));
    if (diagonal2 & (diagonal2 >> (2 * (BOARD_WIDTH - 1)))) return true;

    return false;
}

bool Board::isColumnFull(uint8_t column) const
{
    // Check for out of bounds
    if (column >= BOARD_WIDTH)
	{
		throw std::out_of_range("Column " + std::to_string(column) + " out of bounds [0-6]");
	}

    // Column mask
    uint64_t single_mask = 1;
    single_mask <<= column;

    // Full board is the union of red and yellow boards
    uint64_t full_board = red_board | yellow_board;

    // Check if the column is full
    for (uint8_t i = 0; i < BOARD_HEIGHT; i++)
	{
        single_mask << (i * BOARD_WIDTH);
		if (!(full_board & single_mask ))
		{
			return false;
		}
	}
    return true;
}

void Board::playMove(uint8_t column, bool isRed)
{
    // Check for out of bounds
    if (column >= BOARD_WIDTH)
    {
        throw std::out_of_range("Column " + std::to_string(column) + " out of bounds [0-6]");
    }

    // Column mask
    // Example: column = 4, single_mask = 00010000. (Example for uint8)
    uint64_t single_mask = 1;
    single_mask <<= column;

    // Combined board for red and yellow
    // We don't care about the color, only where the pieces are
    uint64_t full_board = red_board | yellow_board;

    // Go through the column and find the first empty spot
    for (uint8_t i = 0; i < BOARD_HEIGHT; i++)
    {
        // Create a mask of the row
        // Move the single mask to the correct row
        uint64_t row_mask = single_mask << (i * BOARD_WIDTH);

        // Check if the row is empty
        if (!(full_board & row_mask))
        {
            if (isRed)
            {
                red_board |= single_mask << (i * BOARD_WIDTH);
            }
            else
            {
                yellow_board |= single_mask << (i * BOARD_WIDTH);
            }
            return;
        }
    }

    throw std::invalid_argument("Column " + std::to_string(column) + " is full");
}

void Board::printBoard() const
{
    // Print the board
	for (int i = BOARD_HEIGHT - 1; i >= 0; i--)
	{
		for (int j = 0; j < BOARD_WIDTH; j++)
		{
            uint64_t mask = 1;
            mask <<= (i * BOARD_WIDTH + j);
			if (red_board & mask)
			{
                printWithColor("R ", "red");
			}
			else if (yellow_board & mask)
			{
                printWithColor("Y ", "yellow");
			}
			else
			{
				printWithColor(". ", "white");
			}
		}
		std::cout << std::endl;
	}
	std::cout << std::endl;
}

void Board::printWithColor(const string& letter, const string& color)
{
    if (color == "red")
    {
		std::cout << "\033[1;31m" << letter << "\033[0m";
	}
	else if (color == "yellow")
	{
		std::cout << "\033[1;33m" << letter << "\033[0m";
	}
	else if (color == "green")
	{
		std::cout << "\033[1;32m" << letter << "\033[0m";
	}
	else if (color == "blue")
	{
		std::cout << "\033[1;34m" << letter << "\033[0m";
	}
	else if (color == "magenta")
	{
		std::cout << "\033[1;35m" << letter << "\033[0m";
	}
	else if (color == "cyan")
	{
		std::cout << "\033[1;36m" << letter << "\033[0m";
	}
	else if (color == "white")
	{
		std::cout << "\033[1;37m" << letter << "\033[0m";
	}
	else if (color == "black")
	{
		std::cout << "\033[1;30m" << letter << "\033[0m";
	}
	else
	{
		std::cout << letter;
	}
}
