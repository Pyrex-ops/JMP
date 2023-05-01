#include "TrainingManager.hpp"

TrainingManager::TrainingManager(BackendServer* server_in,uint32_t sample_period_seconds,Schermo* schermo_in, uint32_t revolutions_in ,
                        MotorinoGravity* motorino_in) : SAMPLE_PERIOD_MILLISECONDS(sample_period_seconds*1000),
                        INITIAL_REVOLUTIONS(revolutions_in){
    schermo = schermo_in;
    server = server_in;
    moltiplicatoreCalorie = server->getMoltiplicatoreCalorie();
    obiettivo = server->getObiettivo();
    lastSentRevolutions = 0;
    revolutions = 0; 
    motorino = motorino_in;
    lastSentTimestamp = millis();
    raggiuntoObiettivo = false;
    server->startTraining();
}

void TrainingManager::storeData(uint32_t revolutions_in) {

    if(checkObiettivo()) {
        for(int i=0;i<4;i++) {
            motorino->vibraIntermittente(200,100,2);
            motorino->vibra(400);
        }
    }
    revolutions = revolutions_in - INITIAL_REVOLUTIONS;
    if(millis() - lastSentTimestamp > SAMPLE_PERIOD_MILLISECONDS) {
        Serial.print("data sent to server = ");
        Serial.println(revolutions - lastSentRevolutions);
        server->sendData(revolutions - lastSentRevolutions);
        lastSentTimestamp = millis();
        lastSentRevolutions = revolutions;
    }
}

bool TrainingManager::checkObiettivo() {
    if(!raggiuntoObiettivo) {
        if(revolutions>20) {
            raggiuntoObiettivo = true;
            return true;
        }
    }
    return false;
}