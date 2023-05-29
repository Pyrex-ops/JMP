#ifndef ENCODER_H
#define ENCODER_H

#include <Arduino.h>

class Encoder {
  public:
	/**
	 * @brief Distruttore.
	 *
	 */
	virtual ~Encoder() {}
	/**
	 * @brief Ritorna la posizione angolare dell'encoder.
	 *
	 * @return int16_t Posizione angolare dell'encoder. Compresa in
	 * (-PPR/2,PPR/2]
	 */
	virtual int16_t getPosition() = 0;
	/**
	 * @brief Ritorna il numero di rivoluzioni in senso orario.
	 *
	 * @return uint32_t Numero di rivoluzioni in senso orario.
	 */
	virtual uint32_t getClockwiseRevolutions() = 0;
	/**
	 * @brief Ritorna il numero di rivoluzioni in senso antiorario.
	 *
	 * @return uint32_t Numero di rivoluzioni in senso antiorario.
	 */
	virtual uint32_t getCounterclockwiseRevolutions() = 0;
	/**
	 * @brief Ritorna il numero di rivoluzioni totale, somma di orarie e
	 * antiorarie.
	 *
	 * @return uint32_t Numero di rivoluzioni.
	 */
	virtual uint32_t getRevolutions() = 0;
	/**
	 * @brief Inizializza l'oggetto Encoder.
	 *
	 */
	virtual void begin() = 0;
};

#endif