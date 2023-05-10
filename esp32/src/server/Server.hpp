#ifndef SERVER_H
#define SERVER_H

#include <Arduino.h>

typedef struct {
	uint32_t jumps;
} training_sample_t;

typedef enum {
	NESSUNO = 0,
	NUMERO_SALTI = 1,
	CALORIE_SPESE = 2,
	TEMPO_ALLENAMENTO_MINUTI = 3,
} tipologiaObiettivo_t;

typedef struct {
	tipologiaObiettivo_t tipologiaObiettivo;
	uint32_t valore;
} obiettivo_t;

class BackendServer {
  private:
	String SERVER_NAME;
  public:
	BackendServer(const char* serverName);
	void startTraining();
	void sendData(uint32_t revolutions);
	obiettivo_t getObiettivo();
	float getMoltiplicatoreCalorie();
};

#endif