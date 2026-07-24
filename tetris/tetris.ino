#include "game.h"

TFT_eSPI tft = TFT_eSPI();

void setup() {
    Serial.begin(115200); 
    Serial.print("hello world!");
    tft.begin();
    tft.setRotation(2);

}

void loop() {
    Serial.print("hello");
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
    delay(36000);
}

