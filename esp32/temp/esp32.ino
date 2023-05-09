#include "src/wifiManager/WifiManager.hpp"
#include "src/motorino/MotorinoGravity.hpp"
#include "src/encoder/NewEncoderAdapter.hpp"
#include "constants.hpp"
#include "src/schermo/Schermo.hpp"

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

Schermo schermo;

uint32_t lostConnectionTimestamp;

void setup() {
  Serial.begin(115200);
  encoder.begin();
  motorino.begin();
  schermo.begin();
  lostConnectionTimestamp = millis();
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
  delay(200);
}

void handleDisconnected() {
  if(millis() - lostConnectionTimestamp > TIMEOUT_NEW_CREDENTIALS_MILLISECONDS ||
        !wifiManager.hasSavedCredentials()) {
    wifiManager.deleteCredentials();
    Serial.println("new credentials required");
    schermo.scrivi(0,"new credentials required");
    currentState = NEW_CREDENTIALS_REQUIRED;
  }
  else {
    wifiManager.connect();
  }
  if(wifiManager.checkConnection()){
    Serial.println("connected");
    schermo.scrivi(0,"connected");
    encoder.reset();
    currentState = IDLE;
  }
}

void handleNewCredentialsRequired() {
  wifiManager.getNewCredentials();
  lostConnectionTimestamp = millis();
  currentState = DISCONNECTED;
}

void handleIdle() {
  if(!wifiManager.checkConnection()) {
    Serial.println("connection lost");
    schermo.scrivi(0,"connection lost");
    lostConnectionTimestamp = millis();
    currentState = DISCONNECTED;
  }
  else if(encoder.getRevolutions() != 0) {
    Serial.println("training started");
    schermo.scrivi(0,"training started");
    currentState = TRAINING;
    encoder.reset();
  }
  //motorino.vibra(100);
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
    schermo.scrivi(0,"training ended");
    encoder.reset();
    currentState = IDLE;
  }
  if(!wifiManager.checkConnection()) {
    Serial.println("connection lost");
    schermo.scrivi(0,"connection lost");
    lostConnectionTimestamp = millis();
    currentState = DISCONNECTED;
  }
}

void disconnected() {
  Serial.println("connection lost");
  schermo.scrivi(0,"connection lost");
  lostConnectionTimestamp = millis();
  currentState = DISCONNECTED;
}