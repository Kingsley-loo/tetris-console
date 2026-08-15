#ifndef GAME_H
#define GAME_H


#include <string>
#include <iomanip>
#include <iostream>
#include <cstdint>
#include <TFT_eSPI.h>
#include <random>
using namespace std;

const unsigned int BOARD_WIDTH = 10;
const unsigned int BOARD_HEIGHT = 20;

constexpr uint16_t RED    = 0xF800;
constexpr uint16_t GREEN  = 0x07E0;
constexpr uint16_t BLUE   = 0x001F;
constexpr uint16_t YELLOW = 0xFFE0;
constexpr uint16_t CYAN   = 0x07FF;
constexpr uint16_t WHITE  = 0xFFFF;
constexpr uint16_t BLACK  = 0x0000;
constexpr uint16_t ORANGE = 0xFDA0;
constexpr uint16_t VIOLET = 0x915C;


const unsigned int GAME_WINDOW_WIDTH = 155;
const unsigned int GAME_WINDOW_HEIGHT = 305; 

const unsigned int NEXT_WINDOW_WIDTH = 70;
const unsigned int NEXT_WINDOW_HEIGHT = 70; 

const unsigned int CELL_SIZE = 4;

const unsigned int ROTATION = 4;
const unsigned int COORDINATE = 4;


//list of tetrominoes, for spawning, choosing next one 
extern char tetrominoList[7];

struct Block {

    bool occupied = false; 
    uint16_t colour; 


};

struct Cell {
    unsigned int x;  
    unsigned int y;
};


class Tetromino {
    public: 
        
        //2D array of the Tetromino's different orientations 
        //rotates clockwise 
        Cell shape[ROTATION][COORDINATE]; 
        //where the starting coordinates should be. centers the Tetromino 
        unsigned int x; 
        unsigned int y; 
        //colour of Tetromino using the TFT library's colours 
        uint16_t colour; 
        //which rotation the Tetromino is currently at. 
        int orientation; 

        Tetromino(Cell newShape[ROTATION][COORDINATE], unsigned int newX, unsigned int newY, uint16_t newColour, int newOrientation);

        Tetromino();

};

void printBoard(Block (&board)[BOARD_WIDTH][BOARD_HEIGHT]);

Tetromino createTetromino(char type);

void drawBlock(TFT_eSPI &tft, unsigned int x, unsigned int y, uint16_t colour);

void LoadHomescreen(TFT_eSPI& tft); 

void drawTetromino(TFT_eSPI& tft, Block (&board)[BOARD_WIDTH][BOARD_HEIGHT],
                    Tetromino& piece, int x, int y);

void drawTetromino(TFT_eSPI& tft, Block (&board)[BOARD_WIDTH][BOARD_HEIGHT],
                    Tetromino& piece, int x, int y, int xPrev, int yPrev);

void drawTetromino(TFT_eSPI& tft, Tetromino& piece, int x, int y);

bool wallCollision(Tetromino& piece, int  x, int y);

void deleteTetromino(TFT_eSPI& tft, Block (&board)[BOARD_WIDTH][BOARD_HEIGHT],
                    Tetromino& piece, int x, int y);

void rotateTetromino(TFT_eSPI& tft, Tetromino& piece, 
                    Block (&board)[BOARD_WIDTH][BOARD_HEIGHT], int& xCursor, int& yCursor);

void lockTetromino (TFT_eSPI& tft, Tetromino& piece, 
                    Block (&board)[BOARD_WIDTH][BOARD_HEIGHT], int x, int y);

bool blockCollision(Tetromino& piece, Block (&board)[BOARD_WIDTH][BOARD_HEIGHT], int x, int y);

void drawGhostBlock(TFT_eSPI &tft, unsigned int x, unsigned int y, uint16_t colour);

Tetromino spawnTetromino(TFT_eSPI& tft);

void shuffleBag();

void redrawBoard(TFT_eSPI tft, Block (&board)[BOARD_WIDTH][BOARD_HEIGHT]);

void clearNextWindow(TFT_eSPI& tft);

void clearHoldWindow(TFT_eSPI& tft);

void loadStartMenu(TFT_eSPI& tft);
#endif