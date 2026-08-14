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
const unsigned long HARD_DROP_DELAY = 800;
const unsigned long BUTTON_DELAY = 275; 
const unsigned long LOCK_TETROMINO_DELAY = 500; 
const unsigned long MOVE_DOWN = 1000;
bool hardDropReady = true; 
bool buttonReady = true;
unsigned long buttonReleaseTime = 0;
unsigned long moveDownTime = 0;

//game board, all collision logic is done here. 
Block board[BOARD_WIDTH][BOARD_HEIGHT];


Tetromino playingPiece;
Tetromino nextPiece;

bool playingTetromino = false; 
bool gameStart = false; 

int xCursor = 0;
int yCursor = 0;


void setup() {
    Serial.begin(115200); 
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

void loop() {
    if (!(gameStart)) {
        gameStart = true; 
        nextPiece = spawnTetromino(tft);; 
    }

    //spawns a new tetromino if one has been placed onto the board already 
    if (playingTetromino == false) {
        playingPiece = nextPiece;
        nextPiece = spawnTetromino(tft); 
        xCursor = playingPiece.x;
        yCursor = playingPiece.y;   
        drawTetromino(tft, board, playingPiece, xCursor, yCursor);
        playingTetromino = true; 
        drawTetromino(tft, board, nextPiece, 170, 130);
    }
    //left movement 
    if (buttonReady) {
        if (digitalRead(LEFT) == LOW) {
            if ((wallCollision(playingPiece, xCursor -1, yCursor) == LOW) 
                        && (blockCollision(playingPiece, board, (xCursor -1), yCursor) == LOW))  {
                //draw Tetromino in new location, drawing black empty blocks in the previous location 

                buttonReady = false; 
                drawTetromino(tft, board, playingPiece, xCursor - 1, yCursor, xCursor, yCursor);
                //sets new location of cursor 
                xCursor = xCursor - 1;
                buttonReleaseTime = millis();


                //stops movement

                //printBoard(board);
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
            if ((wallCollision(playingPiece, xCursor +1, yCursor) == LOW) 
                            && (blockCollision(playingPiece, board, (xCursor + 1), yCursor) == LOW)) {

                buttonReady = false; 
                drawTetromino(tft, board, playingPiece, xCursor + 1, yCursor, xCursor, yCursor);
                //move cursor one block right instead of left 
                xCursor = xCursor + 1;
                buttonReleaseTime = millis();
                //printBoard(board);
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


            buttonReady = false; 
            rotateTetromino(tft, playingPiece, board, xCursor, yCursor);
            buttonReleaseTime = millis();

            //printBoard(board); 
            Serial.print("cursor is at (");
            Serial.print(xCursor);
            Serial.print(", ");
            Serial.print(yCursor);
            Serial.print(") \n");

        
        //lock Tetromino and draw blocks onto board
        } else if (digitalRead(HARD_DROP) == LOW) {

            
            //prevents the hard_drop button from being pressed multiple times 
            buttonReady = false; 
            lockTetromino(tft, playingPiece, board, xCursor, yCursor);
            playingTetromino = false; 
            redrawBoard(tft, board); 
            //printBoard(board); 
            buttonReleaseTime = millis();
            Serial.print("cursor is at (");
            Serial.print(xCursor);
            Serial.print(", ");
            Serial.print(yCursor);
            Serial.print(") \n");

            

        //moves the tetromino one row down 
        } else if (digitalRead(SOFT_DROP) == LOW) {

            if ((wallCollision(playingPiece, xCursor, yCursor + 1) == LOW) 
                                    && (blockCollision(playingPiece, board, xCursor, yCursor + 1) == LOW)) {
                buttonReady = false; 
                drawTetromino(tft, board, playingPiece, xCursor, yCursor + 1, xCursor, yCursor);
                yCursor = yCursor + 1;
                buttonReleaseTime = millis();
                Serial.print("cursor is at (");
                Serial.print(xCursor);
                Serial.print(", ");
                Serial.print(yCursor);
                Serial.print(") \n");
            //if the tetromino cannot move any further but soft_drop is still held down, 
            //lock the tetromino into the board. 
            } else {
                lockTetromino(tft, playingPiece, board, xCursor, yCursor);
                buttonReady = false; 
                playingTetromino = false; 
                redrawBoard(tft, board); 
                //printBoard(board); 
                buttonReleaseTime = millis();
            }


        } 
        

    //this slows down how many times a button can be activated when held down. 
    } else {

        if ((millis() - buttonReleaseTime >= BUTTON_DELAY) || (millis() - buttonReleaseTime >= HARD_DROP_DELAY))  {

                buttonReady = true;

        }                   

    }

    //automatic gravity of tetromino 
    if (digitalRead(SOFT_DROP) == HIGH) {
        //interval that moves the tetromino down 
        if (millis() - moveDownTime >= MOVE_DOWN) {
            drawTetromino(tft, board, playingPiece, xCursor, yCursor + 1, xCursor, yCursor);
            yCursor = yCursor + 1;
            moveDownTime = millis();
            
        }
    
    }

    //if no buttons are pressed, and the tetromino experiences a block or wall collision, 
    //lock it into the board, and spawn a new piece. 
    if ((millis() - moveDownTime >= LOCK_TETROMINO_DELAY) && (millis() - buttonReleaseTime >= BUTTON_DELAY)
                && ((wallCollision(playingPiece, xCursor, yCursor + 1) == HIGH) 
                        || (blockCollision(playingPiece, board, xCursor, yCursor + 1) == HIGH))) {

        lockTetromino(tft, playingPiece, board, xCursor, yCursor);
        playingTetromino = false; 
        redrawBoard(tft, board); 
        //printBoard(board); 
        buttonReady = true; 
        moveDownTime = millis(); 

    }
}








