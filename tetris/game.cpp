#include "game.h"
#include <string>
#include <array>
#include <cstdint>
#include <TFT_eSPI.h>
using namespace std;


//constructor called in createTetromino 
Tetromino::Tetromino(Cell newShape[ROTATION][COORDINATE], unsigned int newX,
            unsigned int newY, uint16_t newColour, int newOrientation) {

    for (int i = 0; i < ROTATION; i++ ) {
        for (int j = 0; j < COORDINATE; j++) {
            shape[i][j] =  newShape[i][j];
        }
    }

    x = newX; 
    y = newY; 
    colour = newColour;
    orientation = newOrientation;

}

//creates tetrominos based on the type. 
Tetromino createTetromino(char type) {

    switch(type) {
        case 'R': {
            Cell shape[ROTATION][COORDINATE] = {

                {{0, 1}, {1, 1}, {1, 0}, {2, 0}}, 
                {{0, 0}, {0, 1}, {1, 1}, {1, 2}},
                {{0, 1}, {1, 1}, {1, 0}, {2, 0}}, 
                {{0, 0}, {0, 1}, {1, 1}, {1, 2}}

            };
            return Tetromino(shape, 0, 0, RED, 0);
        }
        case 'G': {

            Cell shape[ROTATION][COORDINATE] = {

                {{0, 0}, {1, 0}, {1, 1}, {2, 1}}, 
                {{0, 1}, {1, 1}, {1, 0}, {0, 2}}, 
                {{0, 0}, {1, 0}, {1, 1}, {2, 1}}, 
                {{0, 1}, {1, 1}, {1, 0}, {0, 2}}

            };

            return Tetromino(shape, 0, 0, GREEN, 0);
        }
        case 'C': {

            Cell shape[ROTATION][COORDINATE] = {

                {{0, 0}, {1, 0}, {2, 0}, {3, 0}},
                {{0, 0}, {0, 1}, {0, 2}, {0, 3}},
                {{0, 0}, {1, 0}, {2, 0}, {3, 0}},
                {{0, 0}, {0, 1}, {0, 2}, {0, 3}},

            };
            return Tetromino(shape, 0, 0, CYAN, 0);

        }
        case 'O': {

            Cell shape[ROTATION][COORDINATE] = {

                {{0, 0}, {0, 1}, {0, 2}, {1, 2}},
                {{0, 0}, {1, 0}, {2, 0}, {0, 1}},
                {{0, 0}, {1, 0}, {1, 1}, {1, 2}}, 
                {{0, 0}, {0, 1}, {1, 1}, {2, 1}}

            };
            return Tetromino(shape, 0, 0, ORANGE, 0);
        
        }

        case 'B': {

            Cell shape[ROTATION][COORDINATE] = {

                {{1, 0}, {1, 1}, {0, 2}, {1, 2}},
                {{0, 0} , {0, 1}, {1, 1}, {2, 1}},
                {{0, 0}, {1, 0}, {0, 1}, {0, 2}},
                {{0, 0}, {1, 0}, {2, 0}, {2, 1}}
            };

            return Tetromino(shape, 0, 0, BLUE, 0);
        }

        case 'P': {

            Cell shape[ROTATION][COORDINATE] = {

                {{1, 0}, {0, 1}, {1, 1}, {2, 1}}, 
                {{0, 0}, {0, 1}, {1, 1}, {0 ,2}},
                {{0, 0}, {1, 0}, {2, 0}, {1, 1}},
                {{1, 0}, {0, 1}, {1, 1}, {1, 2}}

            };

        

            return Tetromino(shape, 0, 0, VIOLET, 0);
        }
        case 'Y': {

        Cell shape[ROTATION][COORDINATE] = {

            {{0, 0}, {0, 1}, {1, 0}, {1, 1}},
            {{0, 0}, {0, 1}, {1, 0}, {1, 1}},
            {{0, 0}, {0, 1}, {1, 0}, {1, 1}},
            {{0, 0}, {0, 1}, {1, 0}, {1, 1}}

        };

            return Tetromino(shape, 0, 0, YELLOW, 0);
        
        }
    }

}

//helper function to output the string name of a uin16_t colour 
string colourName(uint16_t colour) {
    switch (colour) {
        case 0x0000:
            return "BLACK";

        case 0xFFFF:
            return "WHITE";

        case 0xF800:
            return "RED";

        case 0x07E0:
            return "GREEN";

        case 0x001F:
            return "BLUE";

        case 0xFFE0:
            return "YELLOW";

        case 0x07FF:
            return "CYAN";

        case 0xFDA0:
            return "ORANGE";

        case 0x780F:
            return "PURPLE";

        default:
            return "UNKNOWN";
    }
}

//prints out each block on the game board for debugging, shows if occupied and what colour 
void printBoard(Block (&board)[BOARD_WIDTH][BOARD_HEIGHT]) {
    unsigned int count = 1;
    cout << "bruh" << endl;
        for (unsigned int i = 0; i < BOARD_HEIGHT; i++) {
            for (unsigned int j = 0; j < BOARD_WIDTH; j++){
                //cout << "i = " << i << " j = " << j;
                cout <<  count <<  ": " << colourName(board[j][i].colour) << " ";
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

//sets up the main home screen of the game, board layout, score, next tetrominos, held tetromino 
void LoadHomescreen(TFT_eSPI& tft) {

    tft.setTextSize(2);
    tft.setTextColor(TFT_WHITE);
    tft.fillScreen(TFT_BLACK);
    tft.drawRect(3, 3, GAME_WINDOW_WIDTH, GAME_WINDOW_HEIGHT, WHITE);
    tft.drawString("NEXT:", 165, 5);
    tft.drawRect(165, 25, NEXT_WINDOW_WIDTH, NEXT_WINDOW_HEIGHT, WHITE);

    tft.drawString("HOLD:", 165, 105);
    tft.drawRect(165, 125, NEXT_WINDOW_WIDTH, NEXT_WINDOW_HEIGHT, WHITE);
    tft.drawString("SCORE:", 165, 274);
    tft.drawString("123456", 165, 294);

    return; 

}

//assuming the piece is within the boundaries of the board 
void drawTetromino(TFT_eSPI& tft, Block (&board)[BOARD_WIDTH][BOARD_HEIGHT],
                    Tetromino& piece, int x, int y) {

    //for int i = 0, i < max_size(array Cell), i++
    for (int i = 0; i < CELL_SIZE; i++) {
        int xCor = piece.shape[0][i].x + x;
        //Serial.println(xCor);

        int yCor = piece.shape[0][i].y + y;
        //Serial.println(yCor);
        drawBlock(tft, xCor, yCor, piece.colour);
        board[xCor][yCor].occupied = true;
        board[xCor][yCor].colour = piece.colour;
    //draw cube with colour from cell[i] = (x, y) to board[i][j]\

    }
    
}

//used for redrawing the Tetromino 
void drawTetromino(TFT_eSPI& tft, Block (&board)[BOARD_WIDTH][BOARD_HEIGHT],
                    Tetromino& piece, int x, int y, int xPrev, int yPrev) {

    //loop that removes tetromino from old location 
    for (int i = 0; i < CELL_SIZE; i++) {
        int xCorPrev = piece.shape[0][i].x + xPrev;
        int yCorPrev = piece.shape[0][i].y + yPrev;

        //Serial.println(yCor);
        
        drawBlock(tft, xCorPrev, yCorPrev, BLACK);

        //colours the previous block location to black 
        board[xCorPrev][yCorPrev].occupied = false;
        board[xCorPrev][yCorPrev].colour = BLACK;



    //draw cube with colour from cell[i] = (x, y) to board[i][j]

    }
    // loop that draws tetromino in new location 
    for (int i = 0; i < CELL_SIZE; i++) {
        int xCor = piece.shape[0][i].x + x;
        //Serial.println(xCor);
        int yCor = piece.shape[0][i].y + y;
        drawBlock(tft, xCor, yCor, piece.colour);
        board[xCor][yCor].occupied = true;
        board[xCor][yCor].colour = piece.colour;

    }
    
}

//x and y are the values that the cursor wants to move to 
bool collisionCheck(Tetromino& piece, int  x, int y) {
    for (int i = 0; i < CELL_SIZE; i++) {
        //get tetromino orientation and shape coordinates
        int ori = piece.orientation;
        Cell newBlock = piece.shape[ori][i];
        int newX = newBlock.x + x;
        int newY = newBlock.y + y;
        if ((newX <= 0) || (newX >= 9)) {
            return true;
        }
        //use x and y and tetromino coordinates to calculate position on board 


    }
    return false; 
}