#include "game.h"
#include <string>
#include <cstdint>
#include <TFT_eSPI.h>
#include <iomanip>
#include <random>
using namespace std;

char tetrominoList[7] = {'R', 'G', 'C', 'O', 'B', 'P', 'Y'};


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

                {{0, 0}, {1, 0}, {1, 1}, {2, 1}}, 
                {{0, 1}, {1, 1}, {1, 0}, {0, 2}}, 
                {{0, 0}, {1, 0}, {1, 1}, {2, 1}}, 
                {{0, 1}, {1, 1}, {1, 0}, {0, 2}}

            };
            return Tetromino(shape, 3, 0, RED, 0);
        }
        case 'G': {

            Cell shape[ROTATION][COORDINATE] = {

                {{0, 1}, {1, 1}, {1, 0}, {2, 0}}, 
                {{0, 0}, {0, 1}, {1, 1}, {1, 2}},
                {{0, 1}, {1, 1}, {1, 0}, {2, 0}}, 
                {{0, 0}, {0, 1}, {1, 1}, {1, 2}}

            };


            return Tetromino(shape, 3, 0, GREEN, 0);
        }
        case 'C': {

            Cell shape[ROTATION][COORDINATE] = {

                {{0, 0}, {1, 0}, {2, 0}, {3, 0}},
                {{0, 0}, {0, 1}, {0, 2}, {0, 3}},
                {{0, 0}, {1, 0}, {2, 0}, {3, 0}},
                {{0, 0}, {0, 1}, {0, 2}, {0, 3}}

            };
            return Tetromino(shape, 3, 0, CYAN, 0);

        }
        case 'O': {

            Cell shape[ROTATION][COORDINATE] = {

                {{2, 0}, {0, 1}, {1, 1}, {2, 1}},
                {{0, 0}, {0, 1}, {0, 2}, {1, 2}},
                {{0, 0}, {1, 0}, {2, 0}, {0, 1}},
                {{0, 0}, {1, 0}, {1, 1}, {1, 2}}
                
            };
            return Tetromino(shape, 3, 0, ORANGE, 0);
        
        }

        case 'B': {

            Cell shape[ROTATION][COORDINATE] = {

                {{0, 0}, {0, 1}, {1, 1}, {2, 1}},
                {{0, 0}, {1, 0}, {0, 1}, {0, 2}},
                {{0, 0}, {1, 0}, {2, 0}, {2, 1}},
                {{1, 0}, {1, 1}, {0, 2}, {1, 2}}
                
            };

            return Tetromino(shape, 3, 0, BLUE, 0);
        }

        case 'P': {

            Cell shape[ROTATION][COORDINATE] = {

                {{1, 0}, {0, 1}, {1, 1}, {2, 1}}, 
                {{0, 0}, {0, 1}, {1, 1}, {0 ,2}},
                {{0, 0}, {1, 0}, {2, 0}, {1, 1}},
                {{1, 0}, {0, 1}, {1, 1}, {1, 2}}

            };

        

            return Tetromino(shape, 3, 0, VIOLET, 0);
        }
        case 'Y': {

            Cell shape[ROTATION][COORDINATE] = {

                {{0, 0}, {0, 1}, {1, 0}, {1, 1}},
                {{0, 0}, {0, 1}, {1, 0}, {1, 1}},
                {{0, 0}, {0, 1}, {1, 0}, {1, 1}},
                {{0, 0}, {0, 1}, {1, 0}, {1, 1}}

            };

            return Tetromino(shape, 4, 0, YELLOW, 0);
        
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

        case 0x915C:
            return "PURPLE";

        default:
            return "UNKNOWN";
    }
}

//prints out each block on the game board for debugging, shows if occupied and what colour 
/*
void printBoard(Block (&board)[BOARD_WIDTH][BOARD_HEIGHT]) {
    const int CELL_PRINT_WIDTH = 30;

    cout << left;

    // Column headings
    cout << setw(6) << "Row";

    for (unsigned int x = 0; x < BOARD_WIDTH; x++) {
        string heading = "Column " + to_string(x);
        cout << setw(CELL_PRINT_WIDTH) << heading;
    }

    cout << endl;

    // Separator line
    cout << string(6 + BOARD_WIDTH * CELL_PRINT_WIDTH, '-') << endl;

    for (unsigned int y = 0; y < BOARD_HEIGHT; y++) {
        cout << setw(6) << y;

        for (unsigned int x = 0; x < BOARD_WIDTH; x++) {
            string cellInfo =
                colourName(board[x][y].colour) +
                ", occupied=" +
                (board[x][y].occupied ? "true" : "false");

            cout << setw(CELL_PRINT_WIDTH) << cellInfo << "| ";
        }

        cout << endl;
    }
}*/

void printBoard(Block (&board)[BOARD_WIDTH][BOARD_HEIGHT]) {
    unsigned int count = 1;
    cout << "bruh" << endl;
    for (unsigned int i = 0; i < BOARD_HEIGHT; i++) {
        for (unsigned int j = 0; j < BOARD_WIDTH; j++){
            //cout << "i = " << i << " j = " << j;
            Serial.print(count);
            Serial.print(" : ");
            Serial.print(colourName(board[j][i].colour).c_str());
            /*
            if (board[j][i].occupied == true) {
                Serial.print("TRUE");
            } else {
                Serial.print("FALSE");
            }*/
            Serial.print(" ");
            count++;
        }   
        Serial.print("\n");
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
//drawing a ghost block 
void drawGhostBlock(TFT_eSPI &tft, unsigned int x, unsigned int y, uint16_t colour) {
    int xBlock = (x * 15) + 5;
    int yBlock = (y * 15) + 5;
    tft.drawRect(xBlock, yBlock, 15, 15, colour);
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
    int xValue = 0;
    int yValue = 0;
    //for int i = 0, i < max_size(array Cell), i++
    for (int i = 0; i < CELL_SIZE; i++) {
        int xCor = piece.shape[piece.orientation][i].x + x;
        //Serial.println(xCor);

        int yCor = piece.shape[piece.orientation][i].y + y;
        //Serial.println(yCor);
        drawBlock(tft, xCor, yCor, piece.colour);
        board[xCor][yCor].colour = piece.colour;
        xValue = xCor;
        yValue = yCor; 
    //draw cube with colour from cell[i] = (x, y) to board[i][j]\

    }

    //making ghost Tetromino 
    int counter = 0; 
    while (!(wallCollision(piece, x, y + counter + 1)) 
                    && !(blockCollision(piece, board, x, y + counter + 1))) {
        counter++; 
    } 

    for (int i = 0; i < CELL_SIZE; i++) {
        int xCor = piece.shape[piece.orientation][i].x + x;
        //Serial.println(xCor);

        int yCor = piece.shape[piece.orientation][i].y + y;
        //Serial.println(yCor);
        drawGhostBlock(tft, xCor, yCor + counter, piece.colour);
    }

    return;
    
}

void deleteTetromino(TFT_eSPI& tft, Block (&board)[BOARD_WIDTH][BOARD_HEIGHT],
                    Tetromino& piece, int x, int y) {

    for (int i = 0; i < CELL_SIZE; i++) {
        int xCor = piece.shape[piece.orientation][i].x + x;
        //Serial.println(xCor);

        int yCor = piece.shape[piece.orientation][i].y + y;
        //Serial.println(yCor);
        drawBlock(tft, xCor, yCor, BLACK);
        board[xCor][yCor].occupied = false;
        board[xCor][yCor].colour = BLACK;


    }
    int counter = 0; 
    while (!(wallCollision(piece, x, y + counter + 1))
                    && !(blockCollision(piece, board, x, y + counter + 1))) {
        counter++; 
    } 

    for (int i = 0; i < CELL_SIZE; i++) {
        int xCor = piece.shape[piece.orientation][i].x + x;
        //Serial.println(xCor);

        int yCor = piece.shape[piece.orientation][i].y + y;
        //Serial.println(yCor);
        drawGhostBlock(tft, xCor, yCor + counter, BLACK);
    }



    return;

}

//used for redrawing the Tetromino 
void drawTetromino(TFT_eSPI& tft, Block (&board)[BOARD_WIDTH][BOARD_HEIGHT],
                    Tetromino& piece, int x, int y, int xPrev, int yPrev) {
    int ori = piece.orientation; 
    //loop that removes tetromino from old location 
    /*for (int i = 0; i < CELL_SIZE; i++) {
        int xCorPrev = piece.shape[ori][i].x + xPrev;
        int yCorPrev = piece.shape[ori][i].y + yPrev;

        //Serial.println(yCor);
        
        drawBlock(tft, xCorPrev, yCorPrev, BLACK);

        //colours the previous block location to black 
        board[xCorPrev][yCorPrev].colour = BLACK;



    //draw cube with colour from cell[i] = (x, y) to board[i][j]

    }*/
   deleteTetromino(tft, board, piece, xPrev, yPrev);
    // loop that draws tetromino in new location 
    for (int i = 0; i < CELL_SIZE; i++) {
        int xCor = piece.shape[ori][i].x + x;
        //Serial.println(xCor);
        int yCor = piece.shape[ori][i].y + y;
        drawBlock(tft, xCor, yCor, piece.colour);
        board[xCor][yCor].colour = piece.colour;

        
    }
    int counter = 0; 
    while (!(wallCollision(piece, x, y + counter + 1)) 
                    && !(blockCollision(piece, board, x, y + counter + 1))) {
        counter++; 
  
    } 
    /*
    for (int i = 0; i < CELL_SIZE; i++) {
        int xCor = piece.shape[piece.orientation][i].x + xPrev;
        //Serial.println(xCor);

        int yCor = piece.shape[piece.orientation][i].y + yPrev;
        //Serial.println(yCor);
        drawGhostBlock(tft, xCor, yCor + counter, BLACK);
    }*/
    for (int i = 0; i < CELL_SIZE; i++) {
        int xCor = piece.shape[piece.orientation][i].x + x;
        //Serial.println(xCor);

        int yCor = piece.shape[piece.orientation][i].y + y;
        //Serial.println(yCor);
        drawGhostBlock(tft, xCor, yCor + counter, piece.colour);
    }
    return;
    
}

//x and y are the values that the cursor wants to move to 
bool wallCollision(Tetromino& piece, int  x, int y) {
    for (int i = 0; i < CELL_SIZE; i++) {
        //get tetromino orientation and shape coordinates
        int ori = piece.orientation;
        Cell newBlock = piece.shape[ori][i];
        int newX = newBlock.x + x;
        int newY = newBlock.y + y;
        if ((newX < 0) || (newX > BOARD_WIDTH -1 ) || (newY < 0) || (newY > BOARD_HEIGHT - 1)) {
            return true;
        }
        //use x and y and tetromino coordinates to calculate position on board 


    }
    return false; 
}

//will modify tetromino and cursor values if rotation is possible

void rotateTetromino(TFT_eSPI& tft, Tetromino& piece, 
            Block (&board)[BOARD_WIDTH][BOARD_HEIGHT], int& xCursor, int& yCursor) {
    bool leftCollision = false; 
    bool rightCollision = false;
    //check the next four left and four right blocks
    int move = 0; 
    //create sample tetromino to test if rotation possivle 
    Tetromino sample = piece; 

    //changes orientation of tetromino (rotates clockwise)
    if (sample.orientation == 3) {
        sample.orientation = 0; 
    } else {
        sample.orientation++; 
    }

    //checks how many times the cursor needs to move left or right
    for (int i = 0; i < CELL_SIZE; i++) {
        if (sample.shape[sample.orientation][i].x + xCursor < 0) {
            leftCollision = true; 
            move++; 
        }
        if (sample.shape[sample.orientation][i].x + xCursor > 9) {
            rightCollision = true; 
            move++;
        }
    }

    //removes tetromino from board and display 
    deleteTetromino(tft, board, piece, xCursor, yCursor);

    //modifies cursor value to new spot 
    if (leftCollision == true) {
        xCursor = xCursor + move;
    } else if (rightCollision == true) {
        xCursor = xCursor - move; 
    }

    //changes tetromino piece's orientation
    if (piece.orientation == 3) {
        piece.orientation = 0; 
    } else {
        piece.orientation++; 
    }
    Serial.println(piece.orientation);
    //draws new tetromino
    drawTetromino(tft, board, piece, xCursor, yCursor);
    Serial.println("tetromino rotaion successful");

}

//precondition: Tetromino is actually able to lock itself into place (collision checks don't return true )
//without collisions 
void lockTetromino (TFT_eSPI& tft, Tetromino& piece, Block (&board)[BOARD_WIDTH][BOARD_HEIGHT], int xCursor, int yCursor) {
    int counter = 0; 
    while (!(wallCollision(piece, xCursor, yCursor + counter + 1)) && 
                        !(blockCollision(piece, board, xCursor, yCursor + counter + 1))) {
        counter++; 
    } 

    for (int i = 0; i < CELL_SIZE; i++) {
        //get coordinates of the block 
        int xLock = piece.shape[piece.orientation][i].x + xCursor;
        int yLock = piece.shape[piece.orientation][i].y + yCursor + counter;

        //make block occupied and change it's colour 
        board[xLock][yLock].occupied = true; 
        board[xLock][yLock].colour = piece.colour; 
        //draw block on display 
        drawBlock(tft, xLock, yLock, board[xLock][yLock].colour); 
    }
    deleteTetromino(tft, board, piece, xCursor, yCursor);
}

//checks if the blocks for the future location of a tetromino is occupied. 
//tetromino should remain in place if blockCollision() returns false. 
bool blockCollision(Tetromino& piece, Block (&board)[BOARD_WIDTH][BOARD_HEIGHT], int xCursor, int yCursor) {
    
    for (int i = 0; i < CELL_SIZE; i++) {
        //get coordinates for where the tetromino block wants to move 
        int xMove = piece.shape[piece.orientation][i].x + xCursor;
        int yMove = piece.shape[piece.orientation][i].y + yCursor; 
        //Serial.print("block wants to move to: (");
        //Serial.print(xCursor); 
        //Serial.print(", ");
       // Serial.print(yCursor); 
       // Serial.print(")\n");



        if (board[xMove][yMove].occupied == true) {
            //Serial.print("block collision detected");
            return true; 

        }

    }
    return false;
}

Tetromino spawnTetromino() {
    random_device rd; 

    mt19937 gen(rd()); 

    uniform_int_distribution<int> dist(0, 6); 

    int randomNum = dist(gen); 

    return (createTetromino(tetrominoList[randomNum]));
}