#include "src/wifiManager/WifiManager.hpp"
#include "src/motorino/MotorinoGravity.hpp"
#include "src/encoder/NewEncoderAdapter.hpp"
#include "constants.hpp"

void handleDisconnected();
void handleNewCredentialsRequired();
void handleIdle();
void handleTraining();

MotorinoGravity motorino(MOTORINO_PIN,MINIMUM_MOTORINO_INTENSITY ,
  MOTORINO_LEDC_CHANNEL , MOTORINO_LEDC_FREQUENCY, MOTORINO_LEDC_RESOLUTION , 
  MOTORINO_TASK_PRIORITY , MOTORINO_TASK_CORE , MOTORINO_TEMPO_FRA_VIBRAZIONI);

NewEncoderAdapter encoder(ENCODER_CLK_PIN,ENCODER_DT_PIN,ENCODER_PPR);

typedef enum {
  DISCONNECTED,
  NEW_CREDENTIALS_REQUIRED,
  IDLE,
  TRAINING,
} state_t;

WifiManager wifiManager;
state_t currentState = DISCONNECTED;

void setup() {
  Serial.begin(115200);
  encoder.begin();
  motorino.begin();
}

void loop() {
  switch(currentState) {
    case DISCONNECTED:
      handleDisconnected();
      break;
    case NEW_CREDENTIALS_REQUIRED:
      handleNewCredentialsRequired();
      break;
    case IDLE:
      handleIdle();
      break;
    case TRAINING:
      handleTraining();
      break;
  }
}

void handleDisconnected() {
  Serial.println("disconnected");
  if(!wifiManager.connect()) {
    Serial.println("new credentials required");
    currentState = NEW_CREDENTIALS_REQUIRED;
  }
  else if(wifiManager.checkConnection()){
    Serial.println("connected");
    encoder.reset();
    currentState = IDLE;
  }
}

void handleNewCredentialsRequired() {
  wifiManager.getNewCredentials();
  currentState = DISCONNECTED;
}

void handleIdle() {
  if(!wifiManager.checkConnection()) {
    Serial.println("connection lost");
    currentState = DISCONNECTED;
  }
  else if(encoder.getRevolutions() != 0) {
    Serial.println("training started");
    currentState = TRAINING;
    encoder.reset();
  }
  //motorino.vibra(100);
  delay(500);
}

void handleTraining() {
  static uint32_t timestampLastRevolution = millis();
  static uint32_t lastRevolutionNumber = encoder.getRevolutions();
  if(encoder.getRevolutions() != lastRevolutionNumber) {
    lastRevolutionNumber = encoder.getRevolutions();
    timestampLastRevolution = millis();
  }
  if((millis() - timestampLastRevolution) > TIMEOUT_STOP_TRAINING_MILLISECONDS) {
    Serial.println("training ended");
    encoder.reset();
    currentState = IDLE;
  }
  if(!wifiManager.checkConnection()) {
    Serial.println("connection lost");
    currentState = DISCONNECTED;
  }
  delay(500);
}