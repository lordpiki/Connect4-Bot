#include "Board.h"
#include <stdexcept>
#include <iostream>
#include <string>

bool Board::checkWinForColor(bool isRed) const {
    bitset<BITS_LEN> board = isRed ? redBoard : yellowBoard;

    // Horizontal check
    bitset<BITS_LEN> h = board & (board >> 1);
    if ((h & (h >> 2)).any()) return true;

    // Vertical check
    bitset<BITS_LEN> v = board & (board >> BOARD_HEIGHT);
    if ((v & (v >> (2 * BOARD_HEIGHT))).any()) return true;

    // Diagonal \ check
    bitset<BITS_LEN> diagonal1 = board & (board >> (BOARD_WIDTH + 1));
    if ((diagonal1 & (diagonal1 >> (2 * (BOARD_WIDTH + 1)))).any()) return true;

    // Diagonal / check
    bitset<BITS_LEN> diagonal2 = board & (board >> (BOARD_WIDTH - 1));
    if ((diagonal2 & (diagonal2 >> (2 * (BOARD_WIDTH - 1)))).any()) return true;

    return false;
}

bool Board::isColumnFull(uint8_t column) const {
    // Check for out of bounds
    if (column >= BOARD_WIDTH) {
        throw std::out_of_range("Column " + std::to_string(column) + " out of bounds [0-6]");
    }

    // Combined board for red and yellow
    bitset<BITS_LEN> full_board = redBoard | yellowBoard;

    // Check if the top bit of the column is set
    return full_board.test(column + (BOARD_HEIGHT - 1) * BOARD_WIDTH);

}

bool Board::isWinningMove(uint8_t column, bool isRed) {
    playMove(column, isRed);
    bool win = checkWinForColor(isRed);
    undoMove(column, isRed);
    return win;
}

void Board::playMove(uint8_t column, bool isRed) {
    // Check for out of bounds
    if (isColumnFull(column)) {
        throw std::invalid_argument("Column " + std::to_string(column) + " is full");
    }

    // Combined board for red and yellow
    bitset<BITS_LEN> full_board = redBoard | yellowBoard;

    // Go through the column and find the first empty spot
    for (int i = 0; i < BOARD_HEIGHT; ++i) {
        int position = column + i * BOARD_WIDTH;
        if (!full_board.test(position)) {
            if (isRed) {
                redBoard.set(position);
            }
            else {
                yellowBoard.set(position);
            }
            ++numMoves;
            return;
        }
    }
}

// SHOULD ONLY BE CALLED RIGHT AFTER playMove TO AVOID UNDEFINED BEHAVIOR
void Board::undoMove(uint8_t column, bool isRed) {
    // Check for out of bounds
    if (column >= BOARD_WIDTH) {
        throw std::out_of_range("Column " + std::to_string(column) + " out of bounds [0-6]");
    }

    // Go through the column and find the first filled spot
    for (int i = BOARD_HEIGHT - 1; i >= 0; --i) {
        int position = column + i * BOARD_WIDTH;
        if (isRed && redBoard.test(position)) {
            redBoard.reset(position);
            --numMoves;
            return;
        }
        else if (!isRed && yellowBoard.test(position)) {
            yellowBoard.reset(position);
            --numMoves;
            return;
        }
    }
}

void Board::printBoard() const {
    for (int i = BOARD_HEIGHT - 1; i >= 0; --i) {
        for (int j = 0; j < BOARD_WIDTH; ++j) {
            int position = i * BOARD_WIDTH + j;
            if (redBoard.test(position)) {
                Helper::printWithColor("R ", "red");
            }
            else if (yellowBoard.test(position)) {
                Helper::printWithColor("Y ", "yellow");
            }
            else {
                Helper::printWithColor(". ", "white");
            }
        }
        std::cout << std::endl;
    }
    std::cout << std::endl;
}
