#pragma once
#include <bitset>
#include <string>

using std::bitset;
using std::string;

constexpr uint8_t BOARD_WIDTH = 7;
constexpr uint8_t BOARD_HEIGHT = 6;

enum class GameState : uint8_t {
    InProgress = 0,
    RedWon = 1,
    YellowWon = 2,
    Draw = 3
};


class Board {
public:

    Board() : m_redBoard(), m_yellowBoard(), m_numMoves(0), m_redMove(0) {}
    Board(uint64_t redBoard, uint64_t yellowBoard) : m_redBoard(redBoard), m_yellowBoard(yellowBoard), m_numMoves(0), m_redMove(0) {}


    // Modifiers
    void play(uint8_t cell);

    // Checkers
    bool is_cell_full(uint8_t cell) const;

    // Getters
    GameState get_game_state() const;

	// Print the board state
    void print();

    // Operators
    bool operator==(const Board& other) const { return m_redBoard == other.m_redBoard && m_yellowBoard == other.m_yellowBoard; }

private:
    // Using bitset to represent the board
    uint64_t m_redBoard;
    uint64_t m_yellowBoard;

    // Number of moves played
    uint32_t m_numMoves;

	// Current player's turn
    bool m_redMove;
        
	// Modifiers

	// Switch turn between red and yellow
    void switch_turn() { m_redMove = !m_redMove; }

    // Checkers
    static bool check_win(uint64_t board);
	static bool check_vertical_win(uint64_t board);
	static bool check_horizontal_win(uint64_t board);
    static bool check_diagonal(uint64_t board);
};
