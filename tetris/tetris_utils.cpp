#include "tetris_utils.hpp"
#include <TFT_eSPI.h>

const int game_window_width = 150;
const int game_window_height = 300; 

const int next_window_width = 65;
const int next_window_height = 65; 

void LoadHomescreen(TFT_eSPI& tft) {

    tft.setTextSize(2);
    tft.setTextColor(TFT_WHITE);
    tft.fillScreen(TFT_BLACK);
    tft.drawRect(5, 5, game_window_width, game_window_height, TFT_WHITE);
    tft.drawString("NEXT:", 165, 5);
    tft.drawRect(165, 30, next_window_width, next_window_height, TFT_WHITE);
    tft.drawString("SCORE:", 165, 105);
    tft.drawString("123456", 165, 125);

    return; 

}