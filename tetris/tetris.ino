#include "game.h"

TFT_eSPI tft = TFT_eSPI();

const int HARD_DROP = 32;
const int SOFT_DROP = 33;
const int LEFT = 25; 
const int RIGHT = 26;
const int ROTATE = 27;
const int HOLD = 14;


Block board[BOARD_WIDTH][BOARD_HEIGHT];
Tetromino test = createTetromino('R');

int xCursor = test.x;
int yCursor = test.y;




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
    drawTetromino(tft, board, test, xCursor, yCursor);

    //moveCursor prevents the block from moving multiple times when the button 
    //is pressed only once 

    //left movement 
    if (moveCursor == HIGH) {
        if (digitalRead(LEFT) == LOW) {
            moveCursor = digitalRead(LEFT); 
            if ((wallCollision(test, xCursor -1, yCursor) == LOW) && (blockCollision(test, board, (xCursor -1), yCursor) == LOW))  {
                //draw Tetromino in new location, drawing black empty blocks in the previous location 
                drawTetromino(tft, board, test, xCursor - 1, yCursor, xCursor, yCursor);
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
            if ((wallCollision(test, xCursor +1, yCursor) == LOW) && (blockCollision(test, board, (xCursor + 1), yCursor) == LOW)) {

                drawTetromino(tft, board, test, xCursor + 1, yCursor, xCursor, yCursor);
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
            rotateTetromino(tft, test, board, xCursor, yCursor);


            printBoard(board); 
            Serial.print("cursor is at (");
            Serial.print(xCursor);
            Serial.print(", ");
            Serial.print(yCursor);
            Serial.print(") \n");

        
        //lock Tetromino and draw blocks onto board
        } else if (digitalRead(HARD_DROP) == LOW) {
            moveCursor = digitalRead(HARD_DROP); 
            lockTetromino(tft, test, board, xCursor, yCursor);

            Serial.print("cursor is at (");
            Serial.print(xCursor);
            Serial.print(", ");
            Serial.print(yCursor);
            Serial.print(") \n");
            xCursor = test.x;
            yCursor = test.y;

        }
        

    } else {
        if ((digitalRead(LEFT) == HIGH) && (digitalRead(RIGHT) == HIGH) && (digitalRead(ROTATE) == HIGH) && (digitalRead(HARD_DROP) == HIGH))   {
            moveCursor = HIGH;

        }

    }


}

