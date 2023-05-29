#ifndef MOTORINO_H
#define MOTORINO_H

#include <Arduino.h>

/**
 * @brief Classe che permette la gestione del motorino vibrante.
 *
 */
class Motorino {
  public:
	/**
	 * @brief Distrugge l'oggetto motorino.
	 *
	 */
	virtual ~Motorino() {}
	/**
	 * @brief Inizializza l'oggetto motorino.
	 *
	 */
	virtual void begin() = 0;
	/**
	 * @brief Fa vibrare il motorino per un certo tempo ad una certa intensità.
	 *
	 * @param millisecondi Tempo di vibrazione in millisecondi.
	 * @param intensity Intensità di vibrazione.
	 */
	virtual void vibra(uint16_t millisecondi, uint16_t intensity) = 0;
	/**
	 * @brief Fa vibrare il motorino per un certo tempo all'intensità massima.
	 *
	 * @param millisecondi Tempo di vibrazione in millisecondi.
	 */
	virtual void vibra(uint16_t millisecondi) = 0;
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
	virtual void
	vibraIntermittente(uint16_t millisecondiSpento, uint16_t millisecondiAcceso,
					   uint16_t numeroPeriodi, uint16_t intensity) = 0;

	/**
	 * @brief Fa vibrare il motorino in maniera intermittente.
	 *
	 * @param millisecondiSpento Tempo di vibrazione per periodo in
	 * millisecondi.
	 * @param millisecondiAcceso Tempo di non vibrazione per periodo in
	 * millisecondi.
	 * @param numeroPeriodi Numero di periodi.
	 */
	virtual void
	vibraIntermittente(uint16_t millisecondiSpento, uint16_t millisecondiAcceso,
					   uint16_t numeroPeriodi) = 0;
};

#endif