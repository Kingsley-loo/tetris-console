#include "game.h"
#include <string>
#include <array>
#include <cstdint>
#include <TFT_eSPI.h>
using namespace std;


//constructor called in createTetromino 
Tetromino::Tetromino(array<Cell, 4> newShape, unsigned int newX,
            unsigned int newY, uint16_t newColour)
    : shape(newShape),
      x(newX),
      y(newY),
      colour(newColour) {
}
//empty tetromino 
Tetromino::Tetromino() {
    shape = {{
          {0, 0}, {0, 0}, {0, 0}, {0, 0}
      }};
      x = 0;
      y = 0;
      colour = BLACK;
}

//creates tetrominos based on the type. 
Tetromino createTetromino(char type) {

    switch(type) {
        case 'R': 

            return Tetromino(
                array<Cell, 4>{{{0, 0}, {0, 1}, {1, 1}, {1, 2}}}, 
                0, 0, RED
            );

        case 'G':

            return Tetromino(
                array<Cell, 4>{{{1, 0}, {1, 1}, {0, 1}, {0, 2}}}, 
                0, 0, GREEN
            );

        case 'C': 

            return Tetromino(
                array<Cell, 4>{{{0, 0}, {0, 1}, {0, 2}, {0, 3}}}, 
                0, 0, CYAN
            );

        case 'O':

            return Tetromino(
                array<Cell, 4>{{{0, 0}, {0, 1}, {0, 2}, {1, 2}}}, 
                0, 0, ORANGE
            );

        case 'B':

            return Tetromino(
                array<Cell, 4>{{{1, 0}, {1, 1}, {1, 2}, {0, 2}}}, 
                0, 0, BLUE
            );

        case 'P':

            return Tetromino(
                array<Cell, 4>{{{1, 0}, {0, 1}, {1, 1}, {2, 1}}}, 
                0, 0, VIOLET
            );

        case 'Y': 
            return Tetromino(
                array<Cell, 4>{{{0, 0}, {0, 1}, {1, 0}, {1, 1}}}, 
                0, 0, YELLOW
            );

        default: 
            return Tetromino(); 
            
    }

}

//prints out each block on the game board for debugging, shows if occupied and what colour 
void printBoard(Block (&board)[BOARD_WIDTH][BOARD_HEIGHT]) {
    unsigned int count = 1;
    cout << "bruh" << endl;
        for (unsigned int i = 0; i < BOARD_WIDTH; i++) {
            for (unsigned int j = 0; j < BOARD_HEIGHT; j++){
                //cout << "i = " << i << " j = " << j;
                cout <<  count <<  ": " << board[i][j].colour << " ";
                count++;
            }

            cout << endl;
        }

    return;
}

//draws blocks. 
void drawBlock(TFT_eSPI &tft, unsigned int x, unsigned int y, uint16_t colour) {
    int xBlock = (x * 15) + 5;
    int yBlock = (y * 15) + 5;
    
    if (colour == BLACK) {
        tft.drawRect(xBlock, yBlock, 15, 15, BLACK);
    } else {
        tft.drawRect(xBlock, yBlock, 15, 15, WHITE);
    }
  
    tft.fillRect(xBlock +1, yBlock + 1, 13, 13, colour);
    return;

}

//sets up the main home screen of the game, board layout, score, next tetrominos 
void LoadHomescreen(TFT_eSPI& tft) {

    tft.setTextSize(2);
    tft.setTextColor(TFT_WHITE);
    tft.fillScreen(TFT_BLACK);
    tft.drawRect(3, 3, GAME_WINDOW_WIDTH, GAME_WINDOW_HEIGHT, WHITE);
    tft.drawString("NEXT:", 165, 5);
    tft.drawRect(165, 30, NEXT_WINDOW_WIDTH, NEXT_WINDOW_HEIGHT, WHITE);
    tft.drawString("SCORE:", 165, 105);
    tft.drawString("123456", 165, 125);

    return; 

}

//assuming the piece is within the boundaries of the board 
void drawTetromino(TFT_eSPI& tft, Block (&board)[BOARD_WIDTH][BOARD_HEIGHT],
                    Tetromino& piece, int x, int y) {

    //for int i = 0, i < max_size(array Cell), i++
    for (int i = 0; i < CELL_SIZE; i++) {
        int xCor = piece.shape[i].x + x;
        Serial.println(xCor);

        int yCor = piece.shape[i].y + y;
        Serial.println(yCor);
        drawBlock(tft, xCor, yCor, piece.colour);
        board[xCor][yCor].occupied = true;
        board[xCor][yCor].colour = piece.colour;
    //draw cube with colour from cell[i] = (x, y) to board[i][j]\

    }
    
}

//used for redrawing the Tetromino 
void drawTetromino(TFT_eSPI& tft, Block (&board)[BOARD_WIDTH][BOARD_HEIGHT],
                    Tetromino& piece, int x, int y, int xPrev, int yPrev) {

    //for int i = 0, i < max_size(array Cell), i++
    for (int i = 0; i < CELL_SIZE; i++) {

        int xCor = piece.shape[i].x + x;
        Serial.println(xCor);

        int yCor = piece.shape[i].y + y;

        int xCorPrev = piece.shape[i].x + xPrev;
        int yCorPrev = piece.shape[i].y + yPrev;

        Serial.println(yCor);

        drawBlock(tft, xCorPrev, yCorPrev, BLACK);
        drawBlock(tft, xCor, yCor, piece.colour);

        board[xCorPrev][yCorPrev].occupied = false;
        board[xCorPrev][yCorPrev].colour = BLACK;

        board[xCor][yCor].occupied = true;
        board[xCor][yCor].colour = piece.colour;



    //draw cube with colour from cell[i] = (x, y) to board[i][j]\

    }
    
}