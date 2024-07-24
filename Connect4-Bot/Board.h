#pragma once
#include <stdint.h>
#include <string>

using std::string;

#define BOARD_WIDTH 7
#define BOARD_HEIGHT 6
#define BITS_LEN 42

class Board
{
public:
	Board() : red_board(0), yellow_board(0) {}
	Board(uint64_t red_board, uint64_t yellow_board) : red_board(red_board), yellow_board(yellow_board) {}
	bool checkWinForColor(bool isRed) const;
	bool isColumnFull(uint8_t column) const;
	void playMove(uint8_t column, bool isRed);
	void printBoard() const;
	static void printWithColor(const string& str, const string& color);

private:
	// Using 64-bit integer to represent the board
	// We will be using only 42 bits, may be a bit less space efficient but is faster to work with using bitwise operations
	uint64_t red_board;
	uint64_t yellow_board;
};

