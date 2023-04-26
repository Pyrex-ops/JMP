#include "src/wifiManager/WifiManager.hpp"
#include "src/motorino/Motorino.hpp"
#include "src/motorino/MotorinoGravity.hpp""
#include "constants.hpp"

void handleDisconnected();
void handleNewCredentialsRequired();
void handleIdle();
void handleTraining();

Motorino* motorino = new MotorinoGravity(MOTORINO_PIN,MINIMUM_MOTORINO_INTENSITY ,
  MOTORINO_LEDC_CHANNEL , MOTORINO_LEDC_FREQUENCY, MOTORINO_LEDC_RESOLUTION , 
  MOTORINO_TASK_PRIORITY , MOTORINO_TASK_CORE , MOTORINO_TEMPO_FRA_VIBRAZIONI);


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
  motorino->begin();
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
    currentState = NEW_CREDENTIALS_REQUIRED;
  }
  else if(wifiManager.checkConnection()){
    currentState = IDLE;
  }
}

void handleNewCredentialsRequired() {
  wifiManager.getNewCredentials();
  currentState = DISCONNECTED;
}

void handleIdle() {
  if(!wifiManager.checkConnection()) {
    currentState = DISCONNECTED;
  }
  motorino->vibra(100);
  delay(500);
}

void handleTraining() {

}