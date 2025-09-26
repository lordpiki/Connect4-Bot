#pragma once
#include <bitset>
#include <string>
#include <array>

#include "BitmapHelper.h"

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

    Board() : m_red_board(), m_yellow_board(), m_num_moves(0), m_red_move(true), m_column_heights{}, m_available_moves_maks(0) {}

    // Modifiers
    void play(uint8_t cell);

    // Checkers
	bool is_cell_full(uint8_t cell) const { return BitmapHelper::is_bit_set(m_available_moves_maks, cell); }
	bool is_red_turn() const { return m_red_move; }
	
    // Getters
    uint64_t get_red_board() const { return m_red_board; }
	uint64_t get_yellow_board() const { return m_yellow_board; }
    GameState get_game_state() const;
    uint32_t get_num_moves() const { return m_num_moves; }
    uint32_t get_empty_cells_count() const { return BOARD_WIDTH * BOARD_HEIGHT - m_num_moves; }

    // Setters
    void set_red_board(uint64_t red_board) { m_red_board = red_board; update_heights(); }
    void set_yellow_board(uint64_t yellow_board) { m_yellow_board = yellow_board; update_heights();}
	void set_red_move(bool red_move) { m_red_move = red_move; }

	// Print the board state
    void print();

    // Operators
    bool operator==(const Board& other) const { return m_red_board == other.m_red_board && m_yellow_board == other.m_yellow_board; }

private:
    // Using bitset to represent the board
    uint64_t m_red_board;
    uint64_t m_yellow_board;

    // Number of moves played
    uint32_t m_num_moves;

    // Collumn heights
	std::array<uint8_t, BOARD_WIDTH> m_column_heights;
    uint8_t m_available_moves_maks;


	// Current player's turn
    bool m_red_move;
        
	// Modifiers

	// Switch turn between red and yellow
    void switch_turn() { m_red_move = !m_red_move; }
    void update_heights();

    // Checkers
    static bool check_win(uint64_t board);
	static bool check_vertical_win(uint64_t board);
	static bool check_horizontal_win(uint64_t board);
    static bool check_diagonal(uint64_t board);
};
