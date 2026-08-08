#include "game.h"
#include <string>

//display 
TFT_eSPI tft = TFT_eSPI();

//pin numbers for the buttons 
const int HARD_DROP = 32;
const int SOFT_DROP = 33;
const int LEFT = 25; 
const int RIGHT = 26;
const int ROTATE = 27;
const int HOLD = 14;

//variables to prevent the hard_drop button from triggering too quickly 
const unsigned long HARD_DROP_RELEASE_DELAY = 200;
bool hardDropReady = true;
unsigned long hardDropReleaseTime = 0;

//game board, all collision logic is done here. 
Block board[BOARD_WIDTH][BOARD_HEIGHT];


Tetromino boi = spawnTetromino();

bool playingTetromino = false; 

int xCursor = 0;
int yCursor = 0;


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

}

bool moveCursor = HIGH; 
int counter = 0;
void loop() {
    //drawTetromino(tft, board, boi, xCursor, yCursor);

    //moveCursor prevents the block from moving multiple times when the button 
    //is pressed only once 

    //spawns a new tetromino if one has been placed onto the board already 
    if (playingTetromino == false) {
        boi = spawnTetromino(); 
        xCursor = boi.x;
        yCursor = boi.y;   
        drawTetromino(tft, board, boi, xCursor, yCursor);
        playingTetromino = true; 
    }
    //left movement 
    if (moveCursor == HIGH) {
        if (digitalRead(LEFT) == LOW) {
            moveCursor = digitalRead(LEFT); 
            if ((wallCollision(boi, xCursor -1, yCursor) == LOW) && (blockCollision(boi, board, (xCursor -1), yCursor) == LOW))  {
                //draw Tetromino in new location, drawing black empty blocks in the previous location 
                drawTetromino(tft, board, boi, xCursor - 1, yCursor, xCursor, yCursor);
                //sets new location of cursor 
                xCursor = xCursor - 1;
                //stops movement

                printBoard(board);
                Serial.print("cursor is at (");
                Serial.print(xCursor);
                Serial.print(", ");
                Serial.print(yCursor);
                Serial.print(") \n");

            } else {
                Serial.println("tetromino has hit a wall or block"); 
            }
        }

        
        //right movement, same logic as left 
        else if (digitalRead(RIGHT) == LOW) {
            moveCursor = digitalRead(RIGHT);
            if ((wallCollision(boi, xCursor +1, yCursor) == LOW) && (blockCollision(boi, board, (xCursor + 1), yCursor) == LOW)) {

                drawTetromino(tft, board, boi, xCursor + 1, yCursor, xCursor, yCursor);
                //move cursor one block right instead of left 
                xCursor = xCursor + 1;
   
                printBoard(board);
                Serial.print("cursor is at (");
                Serial.print(xCursor);
                Serial.print(", ");
                Serial.print(yCursor);
                Serial.print(") \n");

  
            } else {
                Serial.println("tetromino has hit a wall or block"); 
            }



        //rotating tetromino 
        } else if (digitalRead(ROTATE) == LOW) {
            moveCursor = digitalRead(ROTATE);
            rotateTetromino(tft, boi, board, xCursor, yCursor);


            printBoard(board); 
            Serial.print("cursor is at (");
            Serial.print(xCursor);
            Serial.print(", ");
            Serial.print(yCursor);
            Serial.print(") \n");

        
        //lock Tetromino and draw blocks onto board
        } else if (digitalRead(HARD_DROP) == LOW) {
            moveCursor = digitalRead(HARD_DROP); 
            
            //prevents the hard_drop button from being pressed multiple times 
            if (hardDropReady) {
                hardDropReady = false; 
                lockTetromino(tft, boi, board, xCursor, yCursor);
                playingTetromino = false; 
                
            }
            hardDropReleaseTime = millis();

            Serial.print("cursor is at (");
            Serial.print(xCursor);
            Serial.print(", ");
            Serial.print(yCursor);
            Serial.print(") \n");


        }
        

    } else {
        if ((digitalRead(LEFT) == HIGH) && (digitalRead(RIGHT) == HIGH) 
                    && (digitalRead(ROTATE) == HIGH) && (digitalRead(HARD_DROP) == HIGH))   {
            moveCursor = HIGH;
        if (millis() - hardDropReleaseTime >= HARD_DROP_RELEASE_DELAY) {
            hardDropReady = true;
        }

        }

    }


}

