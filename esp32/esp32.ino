#include "src/encoder/Encoder.hpp"
#include "src/encoder/NewEncoderAdapter.hpp"
#include "constants.h"

Encoder* encoder = new NewEncoderAdapter(ENCODER_CLK_PIN,ENCODER_DT_PIN,ENCODER_PPR);

void setup() {
  Serial.begin(115200);
  encoder->begin();
}

void loop() {
  Serial.print(encoder->getPosition());
  Serial.print(",");
  Serial.print(encoder->getClockwiseRevolutions());
  Serial.print(",");
  Serial.print(encoder->getCounterclockwiseRevolutions());
  Serial.print(",");
  Serial.println(encoder->getRevolutions());
  delay(10);
}