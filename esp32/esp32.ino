#include "src/wifiManager/WifiManager.hpp"
#include "src/motorino/MotorinoGravity.hpp"
#include "src/encoder/NewEncoderAdapter.hpp"
#include "constants.hpp"
#include "src/schermo/Schermo.hpp"
#include "src/trainingManager/TrainingManager.hpp"

void handleDisconnected();
void handleNewCredentialsRequired();
void handleIdle();
void handleTraining();

MotorinoGravity motorino(MOTORINO_PIN,MINIMUM_MOTORINO_INTENSITY ,
  MOTORINO_LEDC_CHANNEL , MOTORINO_LEDC_FREQUENCY, MOTORINO_LEDC_RESOLUTION , 
  MOTORINO_TASK_PRIORITY , MOTORINO_TASK_CORE , MOTORINO_TEMPO_FRA_VIBRAZIONI);

NewEncoderAdapter encoder(ENCODER_CLK_PIN,ENCODER_DT_PIN,ENCODER_PPR);
TrainingManager* trainingManager = nullptr;
BackendServer backendServer(new String(API_URL));


typedef enum {
  DISCONNECTED,
  NEW_CREDENTIALS_REQUIRED,
  IDLE,
  TRAINING,
} state_t;

WifiManager wifiManager;
state_t currentState = DISCONNECTED;

Schermo schermo;

void setup() {
  Serial.begin(115200);
  encoder.begin();
  motorino.begin();
  schermo.begin();
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
  Serial.println("disconnected");
  schermo.scrivi(0,"disconnected");
  if(!wifiManager.connect()) {
    Serial.println("new credentials required");
    schermo.scrivi(0,"new credentials required");
    currentState = NEW_CREDENTIALS_REQUIRED;
  }
  else if(wifiManager.checkConnection()){
    Serial.println("connected");
    schermo.scrivi(0,"connected");
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
    schermo.scrivi(0,"connection lost");
    currentState = DISCONNECTED;
  }
  else if(encoder.getRevolutions() != 0) {
    Serial.println("training started");
    schermo.scrivi(0,"training started");
    encoder.reset();
    trainingManager = new TrainingManager(&backendServer,SAMPLE_SENDING_PERIOD_SECONDS,
                                                      &schermo,encoder.getRevolutions(),&motorino);
    currentState = TRAINING;
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
  trainingManager->storeData(encoder.getRevolutions());
  if((millis() - timestampLastRevolution) > TIMEOUT_STOP_TRAINING_MILLISECONDS) {
    Serial.println("training ended");
    schermo.scrivi(0,"training ended");
    encoder.reset();
    currentState = IDLE;
  }
  if(!wifiManager.checkConnection()) {
    Serial.println("connection lost");
    schermo.scrivi(0,"connection lost");
    currentState = DISCONNECTED;
  }
}