#ifndef MOTORINO_GRAVITY_H
#define MOTORINO_GRAVITY_H

#include "Motorino.hpp"
#include <Arduino.h>

typedef struct {
    uint8_t ledcChannel;
    uint16_t intensity;
    uint16_t millisecondi;
    uint8_t pin;
    uint32_t ledcFrequency;
    uint8_t ledcResolution;
} InformazioniVibrazione;

class MotorinoGravity : public Motorino {
    private:
        const uint8_t PIN;
        const uint8_t MINIMUM_INTENSITY;
        const uint8_t LEDC_CHANNEL;
        const uint32_t LEDC_FREQ;
        const uint8_t LEDC_RESOLUTION;
        const uint8_t TASK_PRIORITY;
        const uint8_t TASK_CORE;
        TaskHandle_t taskVibrazione;
        static void vibraTask(void* motorino);
        static void vibraIntermittenteTask(void* motorino);
    public:
        MotorinoGravity(uint8_t motorinoPin,uint8_t minimumIntensity, uint8_t ledcChannel, 
            uint32_t ledcFrequency, uint8_t ledcResolution , uint8_t tasPriority , uint8_t taskCore);
        void begin() override;
        void vibra(uint16_t millisecondi, uint16_t intensity) override;
        void vibra(uint16_t millisecondi) override;
        void vibraIntermittente(uint16_t millisecondiSpento, uint16_t millisecondiAcceso, uint16_t numeroPeriodi, uint16_t intensity) override;
        void vibraIntermittente(uint16_t millisecondiSpento, uint16_t millisecondiAcceso, uint16_t numeroPeriodi) override;
};

#endif