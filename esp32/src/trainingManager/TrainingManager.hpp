#ifndef TRAINING_MANAGER_H
#define TRAINING_MANAGER_H

#include "../motorino/MotorinoGravity.hpp"
#include "../schermo/Schermo.hpp"
#include "../server/Server.hpp"
#include <Arduino.h>

/**
 * @brief Classe che si occupa di gestire un allenamento.
 *
 */
class TrainingManager {
  private:
	/**
	 * @brief Oggetto schermo per scrivere le informazioni sull'allenamento e la
	 * notifica di obiettivo raggiunto.
	 *
	 */
	Schermo* schermo;
	/**
	 * @brief L'obiettivo da seguire durante l'allenamento.
	 *
	 */
	obiettivo_t obiettivo;
	/**
	 * @brief Tempo in millisecondi fra ogni invio di dati al server.
	 *
	 */
	const uint32_t SAMPLE_PERIOD_MILLISECONDS;
	/**
	 * @brief Numero di rivoluzioni che erano memorizzate nell'oggetto quando
	 * è avvenuto l'ultimo invio di dati.
	 *
	 */
	uint32_t lastSentRevolutions;
	/**
	 * @brief Numero di rivoluzioni all'inizio dell'allenamento.
	 *
	 */
	const uint32_t INITIAL_REVOLUTIONS;
	/**
	 * @brief Numero di rivoluzioni attuali.
	 *
	 */
	uint32_t revolutions;
	/**
	 * @brief Oggetto server per la richiesta e l'invio dei dati al server.
	 *
	 */
	BackendServer& server;
	/**
	 * @brief Oggetto motorino per il feedback sul raggiungimento
	 * dell'obiettivo.
	 *
	 */
	MotorinoGravity* motorino;
	/**
	 * @brief Calorie bruciate per un singolo salto.
	 *
	 */
	float moltiplicatoreCalorie;
	/**
	 * @brief Timestamp in millisecondi dell'ultimo invio di dati al server.
	 *
	 */
	uint32_t lastSentTimestamp;
	/**
	 * @brief Invia una nuova misura al server.
	 *
	 */
	void uploadData();
	/**
	 * @brief Timestamp di inizio allenamento.
	 *
	 */
	const uint32_t TIMESTAMP_START_TRAINING;
	/**
	 * @brief Flag che indica se l'obiettivo è già stato raggiunto.
	 *
	 */
	bool raggiuntoObiettivo;
	/**
	 * @brief Calcola il numero di calorie bruciate.
	 *
	 * @return float Numero di calorie bruciate.
	 */
	float calcolaCalorie();
	/**
	 * @brief Controlla il raggiungimento dell'obiettivo.
	 *
	 * @return true Obiettivo raggiunto.
	 * @return false Obiettivo non raggiungimento.
	 */
	bool checkObiettivo();
  public:
	/**
	 * @brief Costruisce un nuovo oggetto TrainingManager.
	 *
	 * @param server_in Oggetto server per la richiesta e l'invio dei dati al
	 * server.
	 * @param sample_period_seconds Tempo in secondi fra ogni invio di dati al
	 * server.
	 * @param schermo_in Oggetto schermo per scrivere le informazioni
	 * sull'allenamento e la notifica di obiettivo raggiunto.
	 * @param revolutions Numero di rivoluzioni all'inizio dell'allenamento.
	 * @param motorino_in Oggetto motorino per il feedback sul raggiungimento
	 * dell'obiettivo.
	 */
	TrainingManager(BackendServer& server_in, uint32_t sample_period_seconds,
					Schermo* schermo_in, uint32_t revolutions, MotorinoGravity* motorino_in);
	/**
	 * @brief Aggiorna il numero di salti effettuate dall'utente.
	 *
	 * @param revolutions Numero di salti effettuate dall'utente.
	 */
	void storeData(uint32_t revolutions);
	/**
	 * @brief Distrugge l'oggetto TrainingManager.
	 *
	 */
	~TrainingManager();
};


#endif