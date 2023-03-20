#ifndef NEW_ENCODER_ADAPTER_H
#define NEW_ENCODER_ADAPTER_H

#include "Encoder.hpp"
#include "NewEncoder/NewEncoder.h"

class NewEncoderAdapter : public Encoder{
    private:
        const uint16_t PPR;
        const uint8_t CLK_PIN;
        const uint8_t DT_PIN;
        const int8_t MAX_POS;
        const int8_t MIN_POS;
        NewEncoder newEncoder;
        uint16_t clockwiseRevolutions;
        uint16_t counterClockwiseRevolutions;
        static void rotatedEncoder(NewEncoder* newEncoder, const volatile NewEncoder::EncoderState* state, void* newEncoderAdapter);
    public:
        NewEncoderAdapter(uint8_t clkPin, uint8_t dtPin, uint16_t ppr);
        int8_t getPosition() override;
        uint16_t getClockwiseRevolutions() override;
        uint16_t getCounterclockwiseRevolutions() override;
        uint16_t getRevolutions() override;
        void begin() override;
};

#endif