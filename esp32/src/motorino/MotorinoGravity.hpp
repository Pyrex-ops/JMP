#ifndef MOTORINO_GRAVITY_H
#define MOTORINO_GRAVITY_H

#include "Motorino.hpp"
#include <Arduino.h>
#include <queue>

typedef struct {
	uint8_t ledcChannel;
	uint16_t intensity;
	uint16_t millisecondi;
	uint8_t pin;
	uint32_t ledcFrequency;
	uint8_t ledcResolution;
} InformazioniVibrazione;

typedef struct {
	InformazioniVibrazione infoAcceso;
	uint16_t millisecondiSpento;
	uint16_t numeroPeriodi;
} InformazioniVibrazioneIntermittente;

class MotorinoGravity : public Motorino {
  private:
	const uint8_t PIN;
	const uint8_t MINIMUM_INTENSITY;
	const uint8_t LEDC_CHANNEL;
	const uint32_t LEDC_FREQ;
	const uint8_t LEDC_RESOLUTION;
	static uint8_t TASK_PRIORITY;
	const uint8_t TASK_CORE;
	static uint16_t TEMPO_FRA_VIBRAZIONI;
	static TaskHandle_t taskVibrazione;
	static std::queue<InformazioniVibrazioneIntermittente*> infoQueue;
	static void vibraIntermittenteTask(void* informazioniVibrazioneIntermittenteVoid);
  public:
	MotorinoGravity(uint8_t motorinoPin, uint8_t minimumIntensity, uint8_t ledcChannel,
					uint32_t ledcFrequency, uint8_t ledcResolution, uint8_t tasPriority,
					uint8_t taskCore, uint16_t tempoFraVibrazioni);
	void begin() override;
	void vibra(uint16_t millisecondi, uint16_t intensity) override;
	void vibra(uint16_t millisecondi) override;
	void vibraIntermittente(uint16_t millisecondiSpento, uint16_t millisecondiAcceso,
							uint16_t numeroPeriodi, uint16_t intensity) override;
	void vibraIntermittente(uint16_t millisecondiSpento, uint16_t millisecondiAcceso,
							uint16_t numeroPeriodi) override;
};

#endif