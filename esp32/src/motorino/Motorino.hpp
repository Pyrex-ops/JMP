#ifndef MOTORINO_H
#define MOTORINO_H

#include <Arduino.h>

class Motorino {
    public:
        virtual ~Motorino() {}
        virtual void begin() = 0;
        virtual void vibra(uint16_t millisecondi, uint16_t intensity) = 0;
        virtual void vibra(uint16_t millisecondi) = 0;
        virtual void vibraIntermittente(uint16_t millisecondiSpento, uint16_t millisecondiAcceso, uint16_t numeroPeriodi, uint16_t intensity) = 0;
        virtual void vibraIntermittente(uint16_t millisecondiSpento, uint16_t millisecondiAcceso, uint16_t numeroPeriodi) = 0;
};

#endif