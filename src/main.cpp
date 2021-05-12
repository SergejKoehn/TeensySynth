#include <Arduino.h>

#include "Adafruit_ILI9341_8bit.h"
#include "TouchScreen.h"

#include "synth_voice.h"

Adafruit_ILI9341_8bit_STM tftDisplay;
TouchScreen               tftTouch(1,2,3,4,200);

void setup() {
  // put your setup code here, to run once:
  tftDisplay.begin();
}

void loop() {
  // put your main code here, to run repeatedly:
}