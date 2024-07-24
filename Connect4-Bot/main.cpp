#include <iostream>
#include "Board.h"

#define RED true
#define YELLOW false    

int main()
{
    Board board;
    board.playMove(0, RED);
    board.playMove(1, RED);
    board.playMove(1, RED);
    board.playMove(2, RED);
    board.playMove(2, RED);
    board.playMove(2, RED);
    board.playMove(3, YELLOW);
    board.playMove(3, RED);
    board.playMove(3, RED);
    board.playMove(3, RED);




    board.printBoard();
    std::cout << "Win? " << board.checkWinForColor(RED) << "\n";
}
