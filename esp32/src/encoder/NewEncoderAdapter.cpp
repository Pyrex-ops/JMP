#include "NewEncoderAdapter.hpp"

NewEncoderAdapter::NewEncoderAdapter(uint8_t clkPin, uint8_t dtPin, uint8_t ppr) 
    : PPR(ppr) , CLK_PIN(clkPin) , DT_PIN(dtPin) , MAX_POS(ppr - 2), MIN_POS(-ppr + 2) ,
    newEncoder(dtPin,clkPin,-ppr, ppr, 0, HALF_PULSE) {
        clockwiseRevolutions = 0;
        counterClockwiseRevolutions = 0;
        newEncoder.attachCallback(rotatedEncoder,this);
}

void NewEncoderAdapter::rotatedEncoder(NewEncoder* newEncoder, const volatile NewEncoder::EncoderState* state, void* newEncoderAdapterCasted) {
    NewEncoderAdapter* newEncoderAdapter = static_cast<NewEncoderAdapter*>(newEncoderAdapterCasted);
    NewEncoder::EncoderState oldEncoderState , newEncoderState;
    if(state->currentValue >= newEncoderAdapter->MAX_POS) {
        newEncoderAdapter->clockwiseRevolutions ++;
        newEncoder->getAndSet(0 , oldEncoderState , newEncoderState);
    }
    else if(state->currentValue <= newEncoderAdapter->MIN_POS) {
        newEncoderAdapter->counterClockwiseRevolutions ++;
        newEncoder->getAndSet(0 , oldEncoderState , newEncoderState);
    }
}

int8_t NewEncoderAdapter::getPosition() {
    NewEncoder::EncoderState state;
    newEncoder.getState(state);
    return state.currentValue;
}
uint16_t NewEncoderAdapter::getClockwiseRevolutions() {
    return clockwiseRevolutions;
}
uint16_t NewEncoderAdapter::getCounterclockwiseRevolutions() {
    return counterClockwiseRevolutions;
}
uint16_t NewEncoderAdapter::getRevolutions() {
    return clockwiseRevolutions + counterClockwiseRevolutions;
}
void NewEncoderAdapter::begin() {
    newEncoder.begin();
}