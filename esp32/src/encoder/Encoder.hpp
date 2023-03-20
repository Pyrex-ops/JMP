#ifndef ENCODER_H
#define ENCODER_H

#include <Arduino.h>

class Encoder {
    public:
        virtual ~Encoder() {}
        virtual int8_t getPosition() = 0;
        virtual uint16_t getClockwiseRevolutions() = 0;
        virtual uint16_t getCounterclockwiseRevolutions() = 0;
        virtual uint16_t getRevolutions() = 0;
        virtual void begin() = 0;
};

#endif