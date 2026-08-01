#ifndef GAME_H
#define GAME_H


#include <string>
#include <array>
#include <iostream>
#include <cstdint>
#include <TFT_eSPI.h>
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

const unsigned int NEXT_WINDOW_WIDTH = 65;
const unsigned int NEXT_WINDOW_HEIGHT = 65; 

const unsigned int CELL_SIZE = 4;



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

        array <Cell, 4> shape; 
        unsigned int x; 
        unsigned int y; 
        uint16_t colour; 

        Tetromino(array <Cell, 4> shape, unsigned int x, unsigned int y, uint16_t newColour);
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
#endif