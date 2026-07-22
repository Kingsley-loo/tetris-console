#ifndef GAME_H
#define GAME_H

struct Block {

    bool occupied = false; 
    uin32_t colour = TFT_BLACK;


}

struct Cell {
    unsigned int x;  
    unsigned int y;
}


struct Tetromino {
    Cell shape[4]; 
    unsigned int x; 
    unsigned int y; 
    uin32_t color; 
}


Tetromino createTetromino(char type) {
    switch(type) {
        case 'R': 

            return Tetromino(
                {{0, 0}, {0, 1}, {1, 1}, {1, 2}}, 
                0, 0, TFT_RED
            );

        case 'G':

            return Tetromino(
                {{0, 1}, {0, 2}, {1, }, {1, 1}}, 
                0, 0, TFT_GREEN
            );

        case 'C': 

            return Tetromino(
                {{0, 0}, {0, 1}, {0, 2}, {0, 3}}, 
                0, 0, TFT_CYAN
            );

        case 'B':

            return Tetromino(
                {{0, 0}, {1, 0}, {1, 1}, {1, 2}}, 
                0, 0, TFT_BLUE
            );

        case 'O':

            return Tetromino(
                {{1, 0}, {1, 1}, {1, 2}, {0, 2}}, 
                0, 0, TFT_ORANGE
            );

        case 'P':

            return Tetromino(
                {{1, 0}, {1, 1}, {1, 2}, {0, 1}}, 
                0, 0, TFT_VIOLET
            );

        default: 
            return Tetromino(); 
            
    }

}



#endif