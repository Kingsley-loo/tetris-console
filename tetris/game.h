#ifndef GAME_H
#define GAME_H
#include <string>
#include <array>
using namespace std;

struct Block {

    bool occupied = false; 
    string colour = "black";


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
        string colour; 

        Tetromino(array <Cell, 4> shape, unsigned int x, unsigned int y, string newColour);
        Tetromino();
};


Tetromino createTetromino(char type);




#endif