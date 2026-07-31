#include "game.h"

TFT_eSPI tft = TFT_eSPI();

const int ACTION = 32;
const int MENU = 33;
const int LEFT = 25; 
const int RIGHT = 26;
const int UP = 27;
const int DOWN = 14;

void setup() {
    Serial.begin(115200); 
    Serial.print("hello world!");
    tft.begin();
    tft.setRotation(2);
    pinMode(ACTION, INPUT_PULLUP);
    pinMode(MENU, INPUT_PULLUP);
    pinMode(LEFT, INPUT_PULLUP);
    pinMode(RIGHT, INPUT_PULLUP);
    pinMode(UP, INPUT_PULLUP);
    pinMode(DOWN, INPUT_PULLUP);

}

void loop() {

    /*
    LoadHomescreen(tft);

    Block board[BOARD_WIDTH][BOARD_HEIGHT];
    Tetromino test = createTetromino('O');
    Tetromino bruh = createTetromino('G');
    Tetromino red = createTetromino('R');
    Tetromino blue = createTetromino('B'); 
    Tetromino purple = createTetromino('P');
    Tetromino cyan = createTetromino('C'); 
    Tetromino yellow = createTetromino('Y');
    drawTetromino(tft, board, test, 0, 1);
    drawTetromino(tft, board, bruh, 3, 5);
    drawTetromino(tft, board, red, 8, 8);
    drawTetromino(tft, board, blue, 0, 17); 
    drawTetromino(tft, board, purple, 5, 12);
    drawTetromino(tft, board, yellow, 2, 18);
    drawTetromino(tft, board, test, 4, 17);
    drawTetromino(tft, board, yellow, 6, 18);
    drawTetromino(tft, board, yellow, 8, 18);
    */

    bool buttonPressed = false;

    if (digitalRead(ACTION) == LOW) {
        Serial.print("ACTION ");
        buttonPressed = true;
    }

    if (digitalRead(MENU) == LOW) {
        Serial.print("MENU ");
        buttonPressed = true;
    }

    if (digitalRead(LEFT) == LOW) {
        Serial.print("LEFT ");
        buttonPressed = true;
    }

    if (digitalRead(RIGHT) == LOW) {
        Serial.print("RIGHT ");
        buttonPressed = true;
    }

    if (digitalRead(UP) == LOW) {
        Serial.print("UP ");
        buttonPressed = true;
    }

    if (digitalRead(DOWN) == LOW) {
        Serial.print("DOWN ");
        buttonPressed = true;
    }

    if (buttonPressed) {
        Serial.print("\n");
    }

    delay(100);
    

}

