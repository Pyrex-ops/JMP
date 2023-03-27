#ifndef NEW_ENCODER_ADAPTER_H
#define NEW_ENCODER_ADAPTER_H

#include "Encoder.hpp"
#include "NewEncoder/NewEncoder.h"

class NewEncoderAdapter : public Encoder{
    private:
        const int16_t PPR;
        const uint8_t CLK_PIN;
        const uint8_t DT_PIN;
        const int16_t MAX_POS;
        const int16_t MIN_POS;
        NewEncoder newEncoder;
        uint32_t clockwiseRevolutions;
        uint32_t counterClockwiseRevolutions;
        static void rotatedEncoder(NewEncoder* newEncoder, const volatile NewEncoder::EncoderState* state, void* newEncoderAdapter);
    public:
        NewEncoderAdapter(uint8_t clkPin, uint8_t dtPin, int16_t ppr);
        int16_t getPosition() override;
        uint32_t getClockwiseRevolutions() override;
        uint32_t getCounterclockwiseRevolutions() override;
        uint32_t getRevolutions() override;
        void begin() override;
};

#endif