#include <iostream>
#include "game.h"
using namespace std;


int main() {
    cout << "fuck" << endl;
    Tetromino red = createTetromino('R');
    cout << red.colour << endl;

    Block board[BOARD_WIDTH][BOARD_HEIGHT];

    printBoard(board);

    return 0;
        
    
}