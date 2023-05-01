#ifndef TRAINING_MANAGER_H
#define TRAINING_MANAGER_H

#include "../schermo/Schermo.hpp"
#include "../server/Server.hpp"
#include "../motorino/MotorinoGravity.hpp"
#include <Arduino.h>

class TrainingManager {
    private:
        Schermo* schermo;
        obiettivo_t obiettivo;
        const uint32_t SAMPLE_PERIOD_MILLISECONDS;
        uint32_t lastSentRevolutions;
        const uint32_t INITIAL_REVOLUTIONS;
        uint32_t revolutions;
        BackendServer* server;
        MotorinoGravity* motorino;
        float moltiplicatoreCalorie;
        uint32_t lastSentTimestamp;
        bool raggiuntoObiettivo;

        bool checkObiettivo();
    public:
        TrainingManager(BackendServer* server_in,uint32_t sample_period_seconds,Schermo* schermo_in, uint32_t revolutions ,
                        MotorinoGravity* motorino_in);
        void storeData(uint32_t revolutions);
};  

#endif