typedef struct {
  byte old_CLK_level;
  byte old_DT_level;
  byte new_CLK_level;
  byte new_DT_level;
  long angular_variation;
  unsigned int revolutions;
} encoder_t;

const byte CLK = 26;
const byte DT = 25;
const byte PPR = 54;
encoder_t encoder;

void setup() {
  pinMode(CLK, INPUT_PULLUP);
  pinMode(DT, INPUT_PULLUP);
  Serial.begin(115200);
  encoder.old_CLK_level = digitalRead(CLK);
  encoder.old_DT_level = digitalRead(DT);
  attachInterrupt(digitalPinToInterrupt(CLK), encoder_clk_interrupt, CHANGE);
  attachInterrupt(digitalPinToInterrupt(DT), encoder_dt_interrupt, CHANGE);
}

void loop() {
  Serial.println(encoder.revolutions);
  delay(10);
}

void encoder_clk_interrupt() {
  encoder.new_CLK_level = digitalRead(CLK);
  encoder_callback();
}

void encoder_dt_interrupt() {
  encoder.new_DT_level = digitalRead(DT);
  encoder_callback();
}

void angle_callback(int variation) {
  encoder.angular_variation += variation;
  if(encoder.angular_variation >= PPR) {
    encoder.angular_variation = 0;
    encoder.revolutions ++;
  }
  else if(encoder.angular_variation <= -PPR) {
    encoder.angular_variation = 0;
    encoder.revolutions ++;
  }
}

void encoder_callback() {
  int switchValue = (encoder.new_CLK_level<<3) + (encoder.new_DT_level<<2) + (encoder.old_CLK_level<<1) + encoder.old_DT_level;
  if(switchValue==1||switchValue==7||switchValue==8||switchValue==14)
    angle_callback(-1);
  else if(switchValue==2||switchValue==4||switchValue==11||switchValue==13)
    angle_callback(1);
  else if(switchValue==3||switchValue==12)
    angle_callback(-2);
  else if(switchValue==6||switchValue==9)
    angle_callback(2);
  encoder.old_CLK_level = encoder.new_CLK_level;
  encoder.old_DT_level = encoder.new_DT_level;
}           