#ifndef SERVER_H
#define SERVER_H

#include <Arduino.h>

typedef struct {
	uint32_t jumps;
} training_sample_t;

typedef enum {
	NESSUNO					 = 0,
	NUMERO_SALTI			 = 1,
	CALORIE_SPESE			 = 2,
	TEMPO_ALLENAMENTO_MINUTI = 3,
} tipologiaObiettivo_t;

typedef struct {
	tipologiaObiettivo_t tipologiaObiettivo;
	uint32_t valore;
} obiettivo_t;

typedef struct {
	String serverName;
	uint32_t revolutions;
	bool creatoAllenamento;
} upload_data_t;

typedef struct {
	String serverName;
	bool* creatoAllenamento;
} start_training_data_t;

typedef struct {
	String serverName;
	obiettivo_t* obiettivo;
} get_obiettivo_data_t;

typedef struct {
	String serverName;
	float* moltiplicatore;
} get_moltiplicatore_data_t;

typedef struct {
	String serverName;
	obiettivo_t* obiettivo;
} get_moltiplicatore_calorie_data_t;

class BackendServer {
  private:
	bool creatoAllenamento;
	String SERVER_NAME;
	static void sendDataThreaded(void* uploadData);
	static void startTrainingThreaded(void* startTrainingData);
	static void getObiettivoThreaded(void* getObiettivoData);
	static void getMoltiplicatoreCalorieThreaded(void* getMoltiplicatoreCalorieData);
	static TaskHandle_t taskSendData;
	static TaskHandle_t taskStartTraining;
	static TaskHandle_t taskGetObiettivo;
	static TaskHandle_t taskGetMoltiplicatoreCalorie;
  public:
	BackendServer(const char* serverName);
	void startTraining();
	void sendData(uint32_t revolutions);
	void getObiettivo(obiettivo_t* obiettivo);
	void getMoltiplicatoreCalorie(float* moltiplicatore);
	bool checkRegistered();
};

#endif