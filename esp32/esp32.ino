#include "src/motorino/Motorino.hpp"
#include "src/motorino/MotorinoGravity.hpp"
#include "src/encoder/Encoder.hpp"
#include "src/encoder/NewEncoderAdapter.hpp"
#include "constants.h"

Motorino* motorino = new MotorinoGravity(MOTORINO_PIN,MINIMUM_MOTORINO_INTENSITY ,
  MOTORINO_LEDC_CHANNEL , MOTORINO_LEDC_FREQUENCY, MOTORINO_LEDC_RESOLUTION , 
  MOTORINO_TASK_PRIORITY , MOTORINO_TASK_CORE , MOTORINO_TEMPO_FRA_VIBRAZIONI);

Encoder* encoder = new NewEncoderAdapter(ENCODER_CLK_PIN,ENCODER_DT_PIN,ENCODER_PPR);

void setup() {
  Serial.begin(115200);
  encoder->begin();
  motorino->begin();
}

void loop() {
  motorino->vibraIntermittente(20,200,3);
  motorino->vibra(500);
  motorino->vibraIntermittente(300,200,5,200);
  for(int i=0;i<500;i++) {
    Serial.print(encoder->getPosition());
    Serial.print(",");
    Serial.print(encoder->getClockwiseRevolutions());
    Serial.print(",");
    Serial.print(encoder->getCounterclockwiseRevolutions());
    Serial.print(",");
    Serial.println(encoder->getRevolutions());
    delay(10);
  }
}