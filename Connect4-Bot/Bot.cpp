#include "Bot.h"
#include <algorithm>
#include <iostream>

using std::cout;
using std::end;


int Bot::miniMax(Board board, bool isRed)
{
    // Check if the game is over
    if (board.isFull()) return 0;

    // Score = num of spaces after winning (WIDTH * HEIGHT / 2 - numMoves)
    for (uint8_t i = 0; i < Board::WIDTH; i++)
	{
		if (!board.isColumnFull(i) && board.isWinningMove(i, isRed))
		{
			return Board::WIDTH * Board::HEIGHT + 1 - board.getMoves() / 2;
		}
	}

	// If the game is not over, we will recursively call miniMax on all possible moves
	int bestScore = -Board::WIDTH * Board::HEIGHT;

	for (uint8_t i = 0; i < Board::WIDTH; i++)
	{
		if (!board.isColumnFull(i))
		{
			// Create new board and play the move
			Board newBoard(board);
			newBoard.playMove(i, -isRed);
			// Recursively call miniMax to get score
			int score = -miniMax(newBoard, -isRed);
			// Update best score
			bestScore = std::max(bestScore, score);
		}
	}
	cout << "here";
	return bestScore;
}
