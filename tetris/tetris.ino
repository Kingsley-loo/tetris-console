#include "game.h"
#include <string>

//display 

TFT_eSPI tft = TFT_eSPI();
unsigned long levelSpeed[10] = {800, 700, 600, 500, 400, 320, 250, 200, 180, 175};

//pin numbers for the buttons 
const int HARD_DROP = 32;
const int SOFT_DROP = 33;
const int LEFT = 25; 
const int RIGHT = 26;
const int ROTATE = 27;
const int HOLD = 14;

int gameScore = 0;
int level = 1; 
int rowsCleared = 0; 

//variables to prevent the hard_drop button from triggering too quickly 
const unsigned long HARD_DROP_DELAY = 275;
const unsigned long BUTTON_DELAY = 175; 
const unsigned long LOCK_TETROMINO_DELAY = 500; 
unsigned long gravity = levelSpeed[level + 1];

unsigned long buttonReleaseTime = 0;
unsigned long moveDownTime = 0;
unsigned long hardDropReleaseTime = 0;
unsigned long softDropTime = 0;
/*                
Serial.print("cursor is at (");
Serial.print(xCursor);
Serial.print(", ");
Serial.print(yCursor);
Serial.print(") \n");
*/


//game board, all collision logic is done here. 
Block board[BOARD_WIDTH][BOARD_HEIGHT];


Tetromino playingPiece;
Tetromino nextPiece;
Tetromino holdPiece;

//booleans for various game functions 
bool playingTetromino = false; 
bool gameStart = false; 
bool holdEmpty = true; 
bool canHold = true; 
bool hardDropReady = true; 
bool buttonReady = true;
bool startMenu = true; 

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
}

void loop() {
    //start menu when console first boots up
    while (startMenu) {

        loadStartMenu(tft);

        //do nothing while waiting for button input 
        while ((digitalRead(HARD_DROP) == HIGH) && (digitalRead(SOFT_DROP) == HIGH) &&
                (digitalRead(LEFT) == HIGH) && (digitalRead(RIGHT) == HIGH) &&
                    (digitalRead(ROTATE) == HIGH) && (digitalRead(HOLD) == HIGH)) {

        }

        startMenu = false;

        delay(200);
    }

    //once the game is about to begin, resets all game values 
    if (!(gameStart)) {
        gameStart = true; 
        gameScore = 0; 
        LoadHomescreen(tft);
        nextPiece = spawnTetromino(tft);
        rowsCleared = 0; 
        level = 1;
        gravity = levelSpeed[level + 1];
        updateLevel(tft, level); 
        //clears the game board 
        for (int j = 0; j < BOARD_HEIGHT; j++) {
            for (int i = 0; i < BOARD_WIDTH; i++) {
                board[i][j].occupied = false; 
                board[i][j].colour = BLACK;
            }
        }
    }

    

//spawns a new tetromino if one has been placed onto the board already 
        if (playingTetromino == false) {
            //only if the HOLD button hasnt already been placed before locking 
            //the tetromino into the board 
            playingPiece = nextPiece;
            nextPiece = spawnTetromino(tft); 

            xCursor = playingPiece.x;
            yCursor = playingPiece.y;   
            drawTetromino(tft, board, playingPiece, xCursor, yCursor);
            playingTetromino = true; 
            clearNextWindow(tft); 
            
            drawNextTetromino(tft, nextPiece);

            //stuff to check if the game should end (too many tetrominoes) 
            if (blockCollision(playingPiece, board, xCursor, yCursor + 1) == HIGH) {
                    
                gameStart = false; 
                playingTetromino = false;  
                loadGameOver(tft);
                delay(1000);
                //waits for every button to be released
                while ((digitalRead(HARD_DROP) == LOW) || (digitalRead(SOFT_DROP) == LOW) ||
                    (digitalRead(LEFT) == LOW) ||(digitalRead(RIGHT) == LOW) ||
                    (digitalRead(ROTATE) == LOW) || (digitalRead(HOLD) == LOW)) {
                }
                //waits for button input before restarting
                while ((digitalRead(HARD_DROP) == HIGH) &&
                    (digitalRead(SOFT_DROP) == HIGH) && (digitalRead(LEFT) == HIGH) &&
                    (digitalRead(RIGHT) == HIGH) && (digitalRead(ROTATE) == HIGH) &&
                    (digitalRead(HOLD) == HIGH)) {
                }                
                tft.fillScreen(BLACK);         
            }

        }

    //do these things only once the game has begun     
    if (gameStart) {
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



                } else {
                    Serial.println("tetromino has hit a wall or block"); 
                }



            //rotating tetromino 
            } else if (digitalRead(ROTATE) == LOW) {
                if ((wallCollision(playingPiece, xCursor, yCursor + 1) == LOW) 
                            && (blockCollision(playingPiece, board, xCursor, yCursor + 1) == LOW)) {

                    
                buttonReady = false; 
                rotateTetromino(tft, playingPiece, board, xCursor, yCursor);
                buttonReleaseTime = millis();
                }
            
            //lock Tetromino and draw blocks onto board
            } else if (digitalRead(HARD_DROP) == LOW) {
                if ((millis() - hardDropReleaseTime >= HARD_DROP_DELAY)) {
                    hardDropReleaseTime = millis();
                    //prevents the hard_drop button from being pressed multiple times 
                    buttonReady = false; 
                    lockTetromino(tft, playingPiece, board, xCursor, yCursor);
                    playingTetromino = false; 
                    int rows = redrawBoard(tft, board); 
                    rowsCleared = rowsCleared + rows; 
                    int distance = BOARD_HEIGHT - yCursor; 
                    gameScore = gameScore + calculateScore(rows, distance, level); 
                    updateGameScore(tft, gameScore);
                    //printBoard(board); 
                    buttonReleaseTime = millis();
                    canHold = true; 
                }
                

                

            //moves the tetromino one row down 
            } else if (digitalRead(SOFT_DROP) == LOW) {
                if ((wallCollision(playingPiece, xCursor, yCursor + 1) == LOW) 
                                        && (blockCollision(playingPiece, board, xCursor, yCursor + 1) == LOW)) {
                    buttonReady = false; 
                    drawTetromino(tft, board, playingPiece, xCursor, yCursor + 1, xCursor, yCursor);
                    yCursor = yCursor + 1;
                    gameScore = gameScore + calculateScore(0, 1, level); 
                    updateGameScore(tft, gameScore);
                    buttonReleaseTime = millis();

                //if the tetromino cannot move any further but soft_drop is still held down, 
                //lock the tetromino into the board. 
                } else if ((wallCollision(playingPiece, xCursor, yCursor + 1) == HIGH) 
                                        || (blockCollision(playingPiece, board, xCursor, yCursor + 1) == HIGH)) {
                    lockTetromino(tft, playingPiece, board, xCursor, yCursor);
                    buttonReady = false; 
                    playingTetromino = false; 
                    int rows = redrawBoard(tft, board); 
                    rowsCleared = rowsCleared + rows;
                    gameScore = gameScore + calculateScore(rows, 0, level);
                    updateGameScore(tft, gameScore);
                    canHold = true;
                    //printBoard(board); 
                    buttonReleaseTime = millis();
                }


            //holding a tetromino 
            } else if (digitalRead(HOLD) == LOW) {
                buttonReady = false; 
                //if no previous tetrominoes have been held 
                if (holdEmpty == true) {
                    deleteTetromino(tft, board, playingPiece, xCursor, yCursor);

                    holdPiece = playingPiece;
                    holdEmpty = false; 
                    canHold = false;
                    playingTetromino = false; 
                    
                    drawHoldTetromino(tft, holdPiece);
                    //printBoard(board);
                //swaps the held and playing tetrominoes
                } else if (canHold == true) {

                    deleteTetromino(tft, board, playingPiece, xCursor, yCursor);
                    Tetromino temp = holdPiece;
                    holdPiece = playingPiece; 
                    playingPiece = temp; 

                    canHold = false; 

                    clearHoldWindow(tft); 
                    drawHoldTetromino(tft, holdPiece);

                    xCursor = playingPiece.x;
                    yCursor = playingPiece.y;   
                    drawTetromino(tft, board, playingPiece, xCursor, yCursor);

                }
            }
            

        //this slows down how many times a button can be activated when held down. 
        } else {

            if ((millis() - buttonReleaseTime >= BUTTON_DELAY))  {
                    buttonReady = true;

            }   
                            

        }

        //automatic gravity of tetromino 
        if ((digitalRead(SOFT_DROP) == HIGH) && (playingTetromino == true) 
                    && (wallCollision(playingPiece, xCursor, yCursor + 1) == LOW) 
                            && (blockCollision(playingPiece, board, xCursor, yCursor + 1) == LOW)) {
            //interval that moves the tetromino down 
            if (millis() - moveDownTime >= gravity) {
                drawTetromino(tft, board, playingPiece, xCursor, yCursor + 1, xCursor, yCursor);
                yCursor = yCursor + 1;
                moveDownTime = millis();
                
            }
        
        }

        //if no buttons are pressed, and the tetromino experiences a block or wall collision, 
        //lock it into the board, and spawn a new piece. 
        if ((millis() - moveDownTime >= LOCK_TETROMINO_DELAY) && (millis() - buttonReleaseTime >= BUTTON_DELAY)
                    && ((wallCollision(playingPiece, xCursor, yCursor + 1) == HIGH) 
                            || (blockCollision(playingPiece, board, xCursor, yCursor + 1) == HIGH)) && (playingTetromino == true)) {

            lockTetromino(tft, playingPiece, board, xCursor, yCursor);

            playingTetromino = false; 
            int rows = redrawBoard(tft, board);
            rowsCleared = rowsCleared + rows;  
            gameScore = gameScore + calculateScore(rows, 0, level);
            updateGameScore(tft, gameScore);
            //printBoard(board); 
            buttonReady = true; 
            canHold = true; 
            moveDownTime = millis(); 

        }

        //increases level every 10 rows cleared
        if ((rowsCleared >= 9) && (level != 10)) {
            level++; 

            gravity = levelSpeed[level + 1];
            rowsCleared = 0; 
            updateLevel(tft, level);

        }  

    }
}
    









