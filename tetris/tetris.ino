#include <TFT_eSPI.h>
#include "utils.h"

TFT_eSPI tft = TFT_eSPI();

void setup() {
  tft.begin();
  tft.setRotation(2);
}

void loop() {
  LoadHomescreen(tft);
  delay(2000000);
}

