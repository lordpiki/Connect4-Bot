#include <iostream>
#include "Board.h"
#include "Bot.h"
#include "Helper.h"
#include <stdint.h>
#define RED true
#define YELLOW false    

int main()
{

    uint64_t num = 1;
    Board board;
    board.isWinningMove(0, RED);
    board.printBoard();
    board.playMove(1, RED);
    board.playMove(1, YELLOW);
    board.playMove(2, RED);
    board.playMove(2, YELLOW);
    board.printBoard();
    std::cout << Bot::miniMax(board, RED) << "\n";



    board.printBoard();
    std::cout << "Win? " << board.checkWinForColor(RED) << "\n";
}
