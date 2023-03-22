#include "src/motorino/Motorino.hpp"
#include "src/motorino/MotorinoGravity.hpp"
#include "constants.h"

Motorino* motorino = new MotorinoGravity(MOTORINO_PIN,MINIMUM_MOTORINO_INTENSITY);

void setup() {
  Serial.begin(115200);
  motorino->begin();
}

void loop() {
  motorino->vibra(500);
  delay(1000);
  motorino->vibra(500,200);
  delay(1000);
}