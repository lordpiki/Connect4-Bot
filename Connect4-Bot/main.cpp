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
    // fill the board
   
    for (int i = 0; i < 7; i++)
	{
        for (int j = 0; j < 7; j++)
        {
            board.playMove(i, RED);
        }
	}
    board.printBoard();
    return 0;
    Bot bot(RED);
    std::cout << bot.miniMax(board, RED) << "\n";



    board.printBoard();
    std::cout << "Win? " << board.checkWinForColor(RED) << "\n";
}
