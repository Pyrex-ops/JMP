#include "src/motorino/Motorino.hpp"
#include "src/motorino/MotorinoGravity.hpp"
#include "constants.h"

Motorino* motorino = new MotorinoGravity(MOTORINO_PIN,MINIMUM_MOTORINO_INTENSITY ,
  MOTORINO_LEDC_CHANNEL , MOTORINO_LEDC_FREQUENCY, MOTORINO_LEDC_RESOLUTION , 
  MOTORINO_TASK_PRIORITY , MOTORINO_TASK_CORE);

void setup() {
  Serial.begin(115200);
  motorino->begin();
}

void loop() {
  motorino->vibra(500);
  delay(1000);
}