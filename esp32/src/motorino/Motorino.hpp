#ifndef MOTORINO_H
#define MOTORINO_H

#include <Arduino.h>

class Motorino {
    public:
        virtual ~Motorino() {}
        virtual void begin() = 0;
        virtual void vibra(uint16_t millisecondi, uint8_t intensity) = 0;
        virtual void vibra(uint16_t millisecondi) = 0;
        virtual void vibra_intermittente(uint16_t millisecondi_spento, uint16_t millisecondi_acceso, uint16_t numero_periodi, uint8_t intensity) = 0;
        virtual void vibra_intermittente(uint16_t millisecondi_spento, uint16_t millisecondi_acceso, uint16_t numero_periodi) = 0;
};

#endif