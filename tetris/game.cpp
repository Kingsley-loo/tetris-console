#include "game.h"
#include <string>
#include <array>
using namespace std;

Tetromino::Tetromino(array <Cell, 4> shape, unsigned int x, unsigned int y, string newColour){
    shape = shape;
    x = x;
    y = y;
    colour = newColour;
}

Tetromino::Tetromino() {
    shape = {{
          {0, 0}, {0, 0}, {0, 0}, {0, 0}
      }};
      x = 0;
      y = 0;
      colour = "black";
}


Tetromino createTetromino(char type) {
    switch(type) {
        case 'R': 

            return Tetromino(
                array<Cell, 4>{{{0, 0}, {0, 1}, {1, 1}, {1, 2}}}, 
                0, 0, "red"
            );

        case 'G':

            return Tetromino(
                array<Cell, 4>{{{0, 1}, {0, 2}, {1, }, {1, 1}}}, 
                0, 0, "green"
            );

        case 'C': 

            return Tetromino(
                array<Cell, 4>{{{0, 0}, {0, 1}, {0, 2}, {0, 3}}}, 
                0, 0, "cyan"
            );

        case 'B':

            return Tetromino(
                array<Cell, 4>{{{0, 0}, {1, 0}, {1, 1}, {1, 2}}}, 
                0, 0, "blue"
            );

        case 'O':

            return Tetromino(
                array<Cell, 4>{{{1, 0}, {1, 1}, {1, 2}, {0, 2}}}, 
                0, 0, "orange"
            );

        case 'P':

            return Tetromino(
                array<Cell, 4>{{{1, 0}, {1, 1}, {1, 2}, {0, 1}}}, 
                0, 0, "violet"
            );

        default: 
            return Tetromino(); 
            
    }

}