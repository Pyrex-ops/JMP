#include "src/motorino/Motorino.hpp"
#include "src/motorino/MotorinoGravity.hpp"
#include "constants.h"

Motorino* motorino = new MotorinoGravity(MOTORINO_PIN,MINIMUM_MOTORINO_INTENSITY ,
  MOTORINO_LEDC_CHANNEL , MOTORINO_LEDC_FREQUENCY, MOTORINO_LEDC_RESOLUTION , 
  MOTORINO_TASK_PRIORITY , MOTORINO_TASK_CORE , MOTORINO_TEMPO_FRA_VIBRAZIONI);

void setup() {
  Serial.begin(115200);
  motorino->begin();
}

void loop() {
  motorino->vibraIntermittente(20,200,3);
  motorino->vibra(500);
  motorino->vibraIntermittente(300,200,5,200);
  delay(2000);
  delay(3000);
}