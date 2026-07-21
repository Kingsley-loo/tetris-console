#include <TFT_eSPI.h>

TFT_eSPI tft = TFT_eSPI();


void setup() {
  tft.begin();
  tft.setRotation(2);


}

void loop() {
  tft.setTextSize(2);
  tft.fillScreen(TFT_BLACK);
  tft.setTextColor(TFT_BLUE, TFT_BLACK);
  tft.drawString("fuck you piece of", 0, 0, 2);
  tft.drawString("shit", 0, 15, 2);
  delay(2000);
}

