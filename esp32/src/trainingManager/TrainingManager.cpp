#include "TrainingManager.hpp"

TrainingManager::TrainingManager(
	BackendServer* server_in, uint32_t sample_period_seconds,
	Schermo* schermo_in, uint32_t revolutions_in, MotorinoGravity* motorino_in)
	: SAMPLE_PERIOD_MILLISECONDS(sample_period_seconds * 1000),
	  INITIAL_REVOLUTIONS(revolutions_in), TIMESTAMP_START_TRAINING(millis()) {
	schermo				  = schermo_in;
	server				  = server_in;
	moltiplicatoreCalorie = server->getMoltiplicatoreCalorie();
	obiettivo			  = server->getObiettivo();
	lastSentRevolutions	  = 0;
	revolutions			  = 0;
	motorino			  = motorino_in;
	lastSentTimestamp	  = millis();
	raggiuntoObiettivo	  = false;
	server->startTraining();
}

void TrainingManager::storeData(uint32_t revolutions_in) {
	revolutions = revolutions_in - INITIAL_REVOLUTIONS;
	schermo->informazioniAllenamento(
		revolutions, (millis() - TIMESTAMP_START_TRAINING) * 1e-3, 0);
	if (checkObiettivo()) {
		for (int i = 0; i < 4; i++) {
			motorino->vibraIntermittente(200, 100, 2);
			motorino->vibra(400);
		}
	}
	if (millis() - lastSentTimestamp > SAMPLE_PERIOD_MILLISECONDS) {
		uploadData();
	}
}

void TrainingManager::uploadData() {
	server->sendData(revolutions - lastSentRevolutions);
	lastSentTimestamp	= millis();
	lastSentRevolutions = revolutions;
}

bool TrainingManager::checkObiettivo() {
	if (!raggiuntoObiettivo) {
		switch (obiettivo.tipologiaObiettivo) {
			case NUMERO_SALTI:
				raggiuntoObiettivo = revolutions > obiettivo.valore;
				break;
			case CALORIE_SPESE:
				raggiuntoObiettivo = calcolaCalorie() > obiettivo.valore;
				break;
			case TEMPO_ALLENAMENTO_MINUTI:
				raggiuntoObiettivo = ((millis() - TIMESTAMP_START_TRAINING) * 1e-3
									  > (obiettivo.valore * 60));
				break;
			default: break;
		}
		return raggiuntoObiettivo;
	}
	return false;
}

int TrainingManager::calcolaCalorie() {
	return moltiplicatoreCalorie * revolutions;
}

TrainingManager::~TrainingManager() {
	uploadData();
}