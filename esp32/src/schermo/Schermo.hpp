#ifndef SCHERMO
#define SCHERMO

#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <mutex>
#include <Wire.h>
#include "../server/Server.hpp"


#define SCREEN_WIDTH 128  // pixel
#define SCREEN_HEIGHT 64
#define OLED_RESET -1	  // Reset pin (-1 se non presente)
#define SCREEN_ADDRESS 0x3C
#define SCHERMO_DEBUG 1


/**
	Classe per l'utilizzo dello schermo per comunicare messaggi all'utente
*/
class Schermo {
  private:
	std::mutex mutexDisplay;
  public:
	/**
	 * Costruttore della classe
	 */
	Schermo();
	/**
	 * Inizializzazione dello schermo
	 *
	 * @warning Fa uso di delay
	 */
	void begin();
	/**
	 * Mostra a schermo le informazioni sull'allenamento
	 *
	 * @param salti numeri di salti registrati
	 * @param tempoAllenamento numero di secondi trascorsi dall'inizio
	 * dell'allenamento
	 */
	void informazioniAllenamento(uint32_t salti, uint32_t tempoAllenamento, uint32_t calorie);
	/**
	 * Mostra a schermo l'avviso di connessione persa
	 *
	 * @warning Fa uso di delay
	 */
	void connessionePersa();
	/**
	 * Mostra a schermo l'invito verso l'utente a fornire le credenziali di una
	 * rete
	 */
	void inserisciCredenziali();
	/**
	 * Pulisci schermo (sembra spento)
	 */
	void pulisci();
	/**
	 * Mostra a schermo l'avviso di raggiungimento obiettivo
	 */
	void obiettivoRaggiunto(tipologiaObiettivo_t tipo);
	/**
	 * Lampeggia schermo invertendo i colori
	 *
	 * @warning Usa delay
	 */
	void lampeggia(uint8_t volte);
	/**
	 * Mostra le credenziali della rete di configurazione
	 *
	 * @param SSID - SSID della rete (11 caratteri)
	 * @param password - password della rete (11 caratteri)
	 *
	 * @warning Non rispettare i limiti porterà alla stampa di caratteri
	 * sovrapposti
	 */
	void mostraCredenziali(String SSID, String password);
};

#endif