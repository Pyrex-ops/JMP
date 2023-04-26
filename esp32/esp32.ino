#include "src/wifiManager/WifiManager.hpp"
#include "constants.hpp"

void handleDisconnected();
void handleNewCredentialsRequired();
void handleIdle();
void handleTraining();


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
  Serial.println("idle");
  delay(200);
}

void handleTraining() {

}