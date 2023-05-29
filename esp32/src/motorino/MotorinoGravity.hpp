#ifndef MOTORINO_GRAVITY_H
#define MOTORINO_GRAVITY_H

#include "Motorino.hpp"
#include <Arduino.h>
#include <queue>

/**
 * @brief Informazioni su un comando di vibrazione singola.
 *
 */
typedef struct {
	uint8_t ledcChannel;
	uint16_t intensity;
	uint16_t millisecondi;
	uint8_t pin;
	uint32_t ledcFrequency;
	uint8_t ledcResolution;
} InformazioniVibrazione;

/**
 * @brief Informazioni su un comando di vibrazione intermittente.
 *
 */
typedef struct {
	InformazioniVibrazione infoAcceso;
	uint16_t millisecondiSpento;
	uint16_t numeroPeriodi;
} InformazioniVibrazioneIntermittente;

/**
 * @brief Classe che permette la gestione del motorino vibrante Gravity.
 *
 */
class MotorinoGravity : public Motorino {
  private:
	/**
	 * @brief Il pin che permette di controlare il motorino vibrante.
	 *
	 */
	const uint8_t PIN;
	/**
	 * @brief Minima intensità di vibrazione.
	 *
	 */
	const uint8_t MINIMUM_INTENSITY;
	/**
	 * @brief Canale LEDC da usare per il pin del motorino.
	 *
	 */
	const uint8_t LEDC_CHANNEL;
	/**
	 * @brief Frequenza da usare per il LEDC.
	 *
	 */
	const uint32_t LEDC_FREQ;
	/**
	 * @brief Frequenza da usare per il LEDC.
	 *
	 */
	const uint8_t LEDC_RESOLUTION;
	/**
	 * @brief Frequenza da usare per il LEDC.
	 *
	 */
	static uint8_t TASK_PRIORITY;
	/**
	 * @brief Core da usare per il task di vibrazione.
	 *
	 */
	const uint8_t TASK_CORE;
	/**
	 * @brief Tempo che verrà fatto passare tra due task di vibrazione.
	 *
	 */
	static uint16_t TEMPO_FRA_VIBRAZIONI;
	/**
	 * @brief Handle del task di vibrazione.
	 *
	 */
	static TaskHandle_t taskVibrazione;
	/**
	 * @brief Coda che contiene i nuovi comandi di vibrazione.
	 *
	 */
	static std::queue<InformazioniVibrazioneIntermittente*> infoQueue;
	/**
	 * @brief Esegue un comando di vibrazione in un thread separato.
	 *
	 * @param informazioniVibrazioneIntermittenteVoid Informazioni sul comando
	 * di vibrazione.
	 */
	static void vibraIntermittenteTask(void* informazioniVibrazioneIntermittenteVoid);
  public:
	/**
	 * @brief Costruisce un nuovo oggetto MotorinoGravity.
	 *
	 * @param motorinoPin Il pin che permette di controlare il motorino
	 * vibrante.
	 * @param minimumIntensity Minima intensità di vibrazione.
	 * @param ledcChannel Canale LEDC da usare per il pin del motorino.
	 * @param ledcFrequency Frequenza da usare per il LEDC.
	 * @param ledcResolution Risoluzione da usare per il LEDC.
	 * @param tasPriority Priorità del task di vibrazione.
	 * @param taskCore Core da usare per il task di vibrazione.
	 * @param tempoFraVibrazioni Tempo che verrà fatto passare tra due task di
	 * vibrazione.
	 */
	MotorinoGravity(uint8_t motorinoPin, uint8_t minimumIntensity, uint8_t ledcChannel,
					uint32_t ledcFrequency, uint8_t ledcResolution, uint8_t tasPriority,
					uint8_t taskCore, uint16_t tempoFraVibrazioni);

	/**
	 * @brief Inizializza l'oggetto MotorinoGravity.
	 *
	 */
	void begin() override;
	/**
	 * @brief Fa vibrare il motorino per un certo tempo ad una certa intensità.
	 *
	 * @param millisecondi Tempo di vibrazione in millisecondi.
	 * @param intensity Intensità di vibrazione.
	 */
	void vibra(uint16_t millisecondi, uint16_t intensity) override;
	/**
	 * @brief Fa vibrare il motorino per un certo tempo all'intensità massima.
	 *
	 * @param millisecondi Tempo di vibrazione in millisecondi.
	 */
	void vibra(uint16_t millisecondi) override;
	/**
	 * @brief Fa vibrare il motorino in maniera intermittente ad una certa
	 * intensità.
	 *
	 * @param millisecondiSpento Tempo di vibrazione per periodo in
	 * millisecondi.
	 * @param millisecondiAcceso Tempo di non vibrazione per periodo in
	 * millisecondi.
	 * @param numeroPeriodi Numero di periodi.
	 * @param intensity Intensità di vibrazione.
	 */
	void vibraIntermittente(uint16_t millisecondiSpento, uint16_t millisecondiAcceso,
							uint16_t numeroPeriodi, uint16_t intensity) override;
	/**
	 * @brief Fa vibrare il motorino in maniera intermittente.
	 *
	 * @param millisecondiSpento Tempo di vibrazione per periodo in
	 * millisecondi.
	 * @param millisecondiAcceso Tempo di non vibrazione per periodo in
	 * millisecondi.
	 * @param numeroPeriodi Numero di periodi.
	 */
	void vibraIntermittente(uint16_t millisecondiSpento, uint16_t millisecondiAcceso,
							uint16_t numeroPeriodi) override;
};

#endif