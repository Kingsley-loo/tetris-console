#include "game.h"
#include <string>
#include <cstdint>
#include <TFT_eSPI.h>
#include <iomanip>
using namespace std;

char tetrominoList[7] = {'R', 'G', 'C', 'O', 'B', 'P', 'Y'};
int bagIndex = 7;

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

//default constructor
Tetromino::Tetromino() {
    for (int i = 0; i < ROTATION; i++) {
        for (int j = 0; j < COORDINATE; j++) {
            shape[i][j] = {0, 0};
        }
    }

    x = 0;
    y = 0;
    colour = BLACK;
    orientation = 0;
}

//creates tetrominoes based on the type. 
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
}
/*
void printBoard(Block (&board)[BOARD_WIDTH][BOARD_HEIGHT]) {
    unsigned int count = 1;
    cout << "bruh" << endl;
    for (unsigned int i = 0; i < BOARD_HEIGHT; i++) {
        for (unsigned int j = 0; j < BOARD_WIDTH; j++){
            //cout << "i = " << i << " j = " << j;
            Serial.print(count);
            Serial.print(" : ");
            Serial.print(colourName(board[j][i].colour).c_str());
            
            if (board[j][i].occupied == true) {
                Serial.print("TRUE");
            } else {
                Serial.print("FALSE");
            }
            Serial.print(" ");
            count++;
        }   
        Serial.print("\n");
    }

    return;

}*/

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

//sets up the main home screen of the game, board layout, score, next tetrominoes, held tetromino 
void LoadHomescreen(TFT_eSPI& tft) {

    tft.setTextSize(2);
    tft.setTextColor(TFT_WHITE);
    tft.fillScreen(TFT_BLACK);
    tft.drawRect(3, 3, GAME_WINDOW_WIDTH, GAME_WINDOW_HEIGHT, WHITE);
    tft.drawString("NEXT:", 165, 5);
    tft.drawRect(165, 25, NEXT_WINDOW_WIDTH, NEXT_WINDOW_HEIGHT, WHITE);

    tft.drawString("HOLD:", 165, 105);
    tft.drawRect(165, 125, NEXT_WINDOW_WIDTH, NEXT_WINDOW_HEIGHT, WHITE);
    tft.drawString("LEVEL:", 165, 219); 
    tft.drawString("1", 165, 239);
    tft.drawString("SCORE:", 165, 274);
    tft.drawString("123456", 165, 294);


    return; 

}

//assuming the piece is within the boundaries of the board 
void drawTetromino(TFT_eSPI& tft, Block (&board)[BOARD_WIDTH][BOARD_HEIGHT],
                    Tetromino& piece, int x, int y) {

    //for int i = 0, i < max_size(array Cell), i++
    for (int i = 0; i < CELL_SIZE; i++) {
        int xCor = piece.shape[piece.orientation][i].x + x;
        //Serial.println(xCor);

        int yCor = piece.shape[piece.orientation][i].y + y;
        //Serial.println(yCor);
        drawBlock(tft, xCor, yCor, piece.colour);
        board[xCor][yCor].colour = piece.colour;
    //draw cube with colour from cell[i] = (x, y) to board[i][j]

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

//used for redrawing the Tetromino (when it moves left or right)
//need to add for when it moves down 
void drawTetromino(TFT_eSPI& tft, Block (&board)[BOARD_WIDTH][BOARD_HEIGHT],
                    Tetromino& piece, int x, int y, int xPrev, int yPrev) {
    int ori = piece.orientation; 

    //remove tetromino from old location 
    deleteTetromino(tft, board, piece, xPrev, yPrev);
    // loop that draws tetromino in new location 

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
    for (int i = 0; i < CELL_SIZE; i++) {

        int xCor = piece.shape[ori][i].x + x;
        //Serial.println(xCor);
        int yCor = piece.shape[ori][i].y + y;
        drawBlock(tft, xCor, yCor, piece.colour);
        board[xCor][yCor].colour = piece.colour;

    }
    return;
    
}

//for drawing tetrominoes in the "next" and "hold" boxes 
void drawTetromino(TFT_eSPI& tft, Tetromino& piece, int x, int y) {
    

    for (int i = 0; i < CELL_SIZE; i++) {
        int xBlock = (piece.shape[piece.orientation][i].x * 15) + x;
        int yBlock = (piece.shape[piece.orientation][i].y * 15) + y;
        tft.drawRect(xBlock, yBlock, 15, 15, WHITE);
        tft.fillRect(xBlock +1, yBlock + 1, 13, 13, piece.colour);

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
    deleteTetromino(tft, board, piece, xCursor, yCursor);
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
    return;
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

//shuffles the tetrominoList after each tetromino has spawned at least once. 
void shuffleBag() {
    for (int i = 6; i > 0; i--) {

        int j = random(0, i + 1);

        char temp = tetrominoList[i];
        tetrominoList[i] = tetrominoList[j];
        tetrominoList[j] = temp;
    }

    bagIndex = 0;
    return; 
}


Tetromino spawnTetromino(TFT_eSPI& tft) {
    //shuffles tetrominoList if needed
    if (bagIndex >= 7) {
        shuffleBag();
    }

    Tetromino piece = createTetromino(tetrominoList[bagIndex]);
    bagIndex++;; 

    


    return piece;

}

//call function after each loop of the game. 
void redrawBoard(TFT_eSPI tft, Block (&board)[BOARD_WIDTH][BOARD_HEIGHT]) {
    
    // loop that checks each row if every cell is occupied 
    for (int j = 0; j < BOARD_HEIGHT; j++) {
        int counter = 0; 
        for (int i = 0; i < BOARD_WIDTH; i++) {
            if (board[i][j].occupied == true) {
                counter++;

            }
        }

        //if a row if occupied, copy the previous row onto it 
        if (counter == 10) { 
            for (int k = j; k > 0; k--) {
                for (int i = 0; i < BOARD_WIDTH; i++) {
                    //copying over data from block in previous row
                    board[i][k].colour = board[i][k-1].colour;
                    board[i][k].occupied = board[i][k-1].occupied; 
                    drawBlock(tft, i, k, board[i][k].colour);
                }
            }
        }
    }

    return;

}

void clearNextWindow(TFT_eSPI& tft) {
    //clears out the nextPiece window 
    tft.fillRect(166, 26, 68, 68, BLACK);
    return;
}

void clearHoldWindow(TFT_eSPI& tft) {
    //clears out the holdPiece window 
    tft.fillRect(166, 126, 68, 68, BLACK);
    return;
}

//just stuff to make the start menu look nice 
void loadStartMenu(TFT_eSPI& tft) {


        tft.setTextSize(4); 
        tft.fillScreen(BLACK); 
        tft.drawCentreString("TETRIS", 120, 144, 1);
        tft.setTextSize(2);

        Tetromino cyan = createTetromino('C');
        Tetromino red = createTetromino('R');
        Tetromino green = createTetromino('G');
        Tetromino blue = createTetromino('B');
        Tetromino yellow = createTetromino('Y');
        Tetromino orange = createTetromino('O');
        Tetromino purple = createTetromino('P');

        tft.drawCentreString("Press any button", 120, 182, 1);

        // bottom-left decoration
        cyan.orientation = 2;
        drawTetromino(tft, cyan, 0, 305);

        yellow.orientation = 2;
        drawTetromino(tft, yellow, 0, 275);

        blue.orientation = 3;
        drawTetromino(tft, blue, 30, 260);

        orange.orientation = 1;
        drawTetromino(tft, orange, 60, 275);

        green.orientation = 3;
        drawTetromino(tft, green, 75, 275);

        purple.orientation = 3;
        drawTetromino(tft, purple, 15, 245);

        red.orientation = 3;
        drawTetromino(tft, red, 0, 230);

        blue.orientation = 0;
        drawTetromino(tft, blue, 105, 290);

        purple.orientation = 1;
        drawTetromino(tft, purple, 0, 200);
        //bottom-right decoration
        cyan.orientation = 0;
        drawTetromino(tft, cyan, 180, 0);
        yellow.orientation = 0;
        drawTetromino(tft, yellow, 210, 15);
        blue.orientation = 1;
        drawTetromino(tft, blue, 180, 15);
        orange.orientation = 3;
        drawTetromino(tft, orange, 150, 0);
        green.orientation = 1;
        drawTetromino(tft, green, 135, 0);
        purple.orientation = 1;
        drawTetromino(tft, purple, 195, 30);
        red.orientation = 1;
        drawTetromino(tft, red, 210, 45);
        blue.orientation = 2;
        drawTetromino(tft, blue, 90, 0);
        purple.orientation = 3; 
        drawTetromino(tft, purple, 210, 75);



    return;
}





