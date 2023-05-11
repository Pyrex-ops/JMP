#ifndef ENCODER_H
#define ENCODER_H

#include <Arduino.h>

class Encoder {
  public:
	virtual ~Encoder() {}
	virtual int16_t getPosition()					  = 0;
	virtual uint32_t getClockwiseRevolutions()		  = 0;
	virtual uint32_t getCounterclockwiseRevolutions() = 0;
	virtual uint32_t getRevolutions()				  = 0;
	virtual void begin()							  = 0;
};

#endif