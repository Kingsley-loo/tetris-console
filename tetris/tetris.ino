#include "game.h"

TFT_eSPI tft = TFT_eSPI();

const int HARD_DROP = 32;
const int SOFT_DROP = 33;
const int LEFT = 25; 
const int RIGHT = 26;
const int ROTATE = 27;
const int HOLD = 14;

int xCursor = 4;
int yCursor = 0;

Block board[BOARD_WIDTH][BOARD_HEIGHT];
Tetromino test = createTetromino('P');


void setup() {
    Serial.begin(115200); 
    Serial.print("hello world!");
    tft.begin();
    tft.setRotation(2);
    pinMode(HARD_DROP, INPUT_PULLUP);
    pinMode(SOFT_DROP, INPUT_PULLUP);
    pinMode(LEFT, INPUT_PULLUP);
    pinMode(RIGHT, INPUT_PULLUP);
    pinMode(ROTATE, INPUT_PULLUP);
    pinMode(HOLD, INPUT_PULLUP);
    LoadHomescreen(tft);
    drawTetromino(tft, board, test, 4, 0);


}

bool moveCursor = HIGH; 
int counter = 0;
void loop() {
    drawTetromino(tft, board, test, xCursor, yCursor);

    //moveCursor prevents the block from moving multiple times when the button 
    //is pressed only once 

    //left movement 
    if (moveCursor == HIGH) {
        if (digitalRead(LEFT) == LOW) {
            moveCursor = digitalRead(LEFT); 
            if (wallCollision(test, xCursor -1, yCursor) == LOW) {
                //draw Tetromino in new location, drawing black empty blocks in the previous location 
                drawTetromino(tft, board, test, xCursor - 1, yCursor, xCursor, yCursor);
                //sets new location of cursor 
                xCursor = xCursor - 1;
                //stops movement

                printBoard(board);
            } else {
                Serial.println("tetromino has hit a wall"); 
            }
        }

        
        //right movement, same logic as left 
        else if (digitalRead(RIGHT) == LOW) {
            moveCursor = digitalRead(RIGHT);
            if (wallCollision(test, xCursor +1, yCursor) == LOW) {

                drawTetromino(tft, board, test, xCursor + 1, yCursor, xCursor, yCursor);
                //move cursor one block right instead of left 
                xCursor = xCursor + 1;
                printBoard(board);
  
            } else {
                Serial.println("tetromino has hit a wall"); 
            }



        //rotating tetromino 
        } else if (digitalRead(ROTATE) == LOW) {
            moveCursor = digitalRead(ROTATE);
            rotateTetromino(tft, test, board, xCursor, yCursor);
            printBoard(board); 
        }
        

    } else {
        if ((digitalRead(LEFT) == HIGH) && (digitalRead(RIGHT) == HIGH) && (digitalRead(ROTATE) == HIGH)) {
            moveCursor = HIGH;
        }

    }


}

