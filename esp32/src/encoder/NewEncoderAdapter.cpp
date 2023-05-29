#include "NewEncoderAdapter.hpp"

NewEncoderAdapter::NewEncoderAdapter(uint8_t clkPin, uint8_t dtPin, int16_t ppr)
	: PPR(ppr), CLK_PIN(clkPin), DT_PIN(dtPin), MAX_POS(ppr - 2),
	  MIN_POS(-ppr + 2), newEncoder(dtPin, clkPin, -ppr, ppr, 0, HALF_PULSE) {
	clockwiseRevolutions		= 0;
	counterClockwiseRevolutions = 0;
	newEncoder.attachCallback(rotatedEncoder, this);
}

void NewEncoderAdapter::rotatedEncoder(
	NewEncoder* newEncoder, const volatile NewEncoder::EncoderState* state,
	void* newEncoderAdapterCasted) {
	NewEncoderAdapter* newEncoderAdapter =
		static_cast<NewEncoderAdapter*>(newEncoderAdapterCasted);
	NewEncoder::EncoderState oldEncoderState, newEncoderState;
	/*
		Le seguenti righe normalizzano la posizione angolare in (-PPR/2,PPR/2]
	*/
	if (state->currentValue >= newEncoderAdapter->MAX_POS) {
		newEncoderAdapter->clockwiseRevolutions++;
		newEncoder->getAndSet(0, oldEncoderState, newEncoderState);
	} else if (state->currentValue <= newEncoderAdapter->MIN_POS) {
		newEncoderAdapter->counterClockwiseRevolutions++;
		newEncoder->getAndSet(0, oldEncoderState, newEncoderState);
	}
}

int16_t NewEncoderAdapter::getPosition() {
	NewEncoder::EncoderState state;
	newEncoder.getState(state);
	return state.currentValue;
}
uint32_t NewEncoderAdapter::getClockwiseRevolutions() {
	return clockwiseRevolutions;
}
uint32_t NewEncoderAdapter::getCounterclockwiseRevolutions() {
	return counterClockwiseRevolutions;
}
uint32_t NewEncoderAdapter::getRevolutions() {
	return clockwiseRevolutions + counterClockwiseRevolutions;
}
void NewEncoderAdapter::begin() {
	newEncoder.begin();
}

void NewEncoderAdapter::reset() {
	clockwiseRevolutions		= 0;
	counterClockwiseRevolutions = 0;
}