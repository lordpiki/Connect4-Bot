#pragma once
#include <bitset>
#include <string>
#include "Helper.h"

using std::bitset;
using std::string;

#define BOARD_WIDTH 7
#define BOARD_HEIGHT 6
#define BITS_LEN 42

class Board {
public:
    static const int WIDTH = BOARD_WIDTH;
    static const int HEIGHT = BOARD_HEIGHT;

    Board() : redBoard(), yellowBoard(), numMoves(0) {}
    Board(const bitset<BITS_LEN>& redBoard, const bitset<BITS_LEN>& yellowBoard) : redBoard(redBoard), yellowBoard(yellowBoard), numMoves(0) {}

    // Checkers
    bool checkWinForColor(bool isRed) const;
    bool isColumnFull(uint8_t column) const;
    bool isFull() const { return numMoves == BOARD_WIDTH * BOARD_HEIGHT; }
    bool isWinningMove(uint8_t column, bool isRed);

    // Getters
    uint8_t getMoves() const { return numMoves; }
    const bitset<BITS_LEN>& getRedBoard() const { return redBoard; }
    const bitset<BITS_LEN>& getYellowBoard() const { return yellowBoard; }

    // Normal functions
    void playMove(uint8_t column, bool isRed);
    void undoMove(uint8_t column, bool isRed);
    void printBoard() const;

    // Operators
    bool operator==(const Board& other) const { return redBoard == other.redBoard && yellowBoard == other.yellowBoard; }

private:
    // Using bitset to represent the board
    bitset<BITS_LEN> redBoard;
    bitset<BITS_LEN> yellowBoard;

    // Number of moves played
    uint8_t numMoves;
};
