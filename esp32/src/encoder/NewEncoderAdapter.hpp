#ifndef NEW_ENCODER_ADAPTER_H
#define NEW_ENCODER_ADAPTER_H

#include "Encoder.hpp"
#include "NewEncoder/NewEncoder.h"

/**
 * @brief Classe che fa da adapter alla libreria newEncoder e permette di
 * ottenere la posizione angolare e il numero di giri.
 *
 */
class NewEncoderAdapter : public Encoder {
  private:
	/**
	 * @brief Pulses Per Revolution. Il numero massimo di variazioni rilevabile
	 * dall'encoder. Una variazione angolare di PPR corrisponde a un giro
	 * completo.
	 *
	 */
	const int16_t PPR;
	/**
	 * @brief La GPIO a cui è collegato il pin CLK dell'encoder.
	 *
	 */
	const uint8_t CLK_PIN;
	/**
	 * @brief La GPIO a cui è collegato il pin DT dell'encoder.
	 *
	 */
	const uint8_t DT_PIN;
	/**
	 * @brief La massima posizione angolare dell'encoder.
	 *
	 */
	const int16_t MAX_POS;
	/**
	 * @brief La minima posizione angolare dell'encoder.
	 *
	 */
	const int16_t MIN_POS;
	/**
	 * @brief Oggetto encoder.
	 *
	 */
	NewEncoder newEncoder;
	/**
	 * @brief Numero di giri effettuati in senso orario.
	 *
	 */
	uint32_t clockwiseRevolutions;
	/**
	 * @brief Numero di giri effettuati in senso antiorario.
	 *
	 */
	uint32_t counterClockwiseRevolutions;
	/**
	 * @brief Callback che verrà richiamata quando l'encoder viene girato.
	 *
	 * @param newEncoder Oggetto newEncoder.
	 * @param state Nuovo stato dell'encoder.
	 * @param newEncoderAdapter Oggetto NewEncoderAdapter i cui dati devono
	 * essere aggiornati.
	 */
	static void rotatedEncoder(
		NewEncoder* newEncoder, const volatile NewEncoder::EncoderState* state,
		void* newEncoderAdapter);
  public:
	/**
	 * @brief Costruisce un oggetto NewEncoderAdapter.
	 *
	 * @param clkPin La GPIO a cui è collegato il pin CLK dell'encoder.
	 * @param dtPin La GPIO a cui è collegato il pin DT dell'encoder.
	 * @param ppr PPR dell'encoder.
	 */
	NewEncoderAdapter(uint8_t clkPin, uint8_t dtPin, int16_t ppr);
	/**
	 * @brief Restituisce la posizione angolare dell'encoder.
	 *
	 * @return int16_t Posizione angolare dell'encoder.
	 */
	int16_t getPosition() override;
	/**
	 * @brief Restituisce il numero di rivoluzioni in senso orario.
	 *
	 * @return uint32_t Numero di rivoluzioni in senso orario.
	 */
	uint32_t getClockwiseRevolutions() override;
	/**
	 * @brief Restituisce il numero di rivoluzioni in senso antiorario.
	 *
	 * @return uint32_t Numero di rivoluzioni in senso antiorario.
	 */
	uint32_t getCounterclockwiseRevolutions() override;
	/**
	 * @brief Ritorna il numero di rivoluzioni totale, somma di orarie e
	 * antiorarie.
	 *
	 * @return uint32_t Numero di rivoluzioni.
	 */
	uint32_t getRevolutions() override;
	/**
	 * @brief Inizializza l'oggetto newEncoderAdapter.
	 *
	 */
	void begin() override;
	/**
	 * @brief Riporta al valore iniziale lo stato dell'encoder, ovvero numero di
	 * giri e posizione angolare.
	 *
	 */
	void reset();
};

#endif