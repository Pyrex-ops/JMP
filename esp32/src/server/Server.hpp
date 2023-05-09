#ifndef SERVER_H
#define SERVER_H

#include <Arduino.h>

typedef struct {
	uint32_t jumps;
} training_sample_t;

typedef enum {
	NUMERO_SALTI,
	CALORIE_SPESE,
	TEMPO_ALLENAMENTO_MINUTI,
} tipologiaObiettivo_t;

typedef struct {
	tipologiaObiettivo_t tipologiaObiettivo;
	uint32_t valore;
} obiettivo_t;

class BackendServer {
  private:
	String* SERVER_NAME;
  public:
	BackendServer(String* serverName);
	void startTraining();
	void sendData(uint32_t revolutions);
	obiettivo_t getObiettivo();
	float getMoltiplicatoreCalorie();
};

#endif