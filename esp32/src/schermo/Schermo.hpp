#ifndef SCHERMO
#define SCHERMO

#define lcdColumns 16
#define lcdRows 2

#include <Arduino.h>
#include <LiquidCrystal_I2C.h>

/**
	Classe per l'utilizzo dello schermo per comunicare messaggi all'utente
*/
class Schermo {
  private:
	//static LiquidCrystal_I2C lcd;


  public:
	/**
	 * Costruttore della classe
	 */
	Schermo();
	/**
	 * Inizializzazione dello schermo
	 */
	void begin();
	/**
	 * Sposta il cursore alla cella indicata
	 * @param riga Riga (0,1)
	 * @param colonna Colonna (0,15)
	 */
	void cursore(int riga, int colonna);
	/**
	 * Sposta il cursore e scrive il carattere indicato
	 * @param riga Riga (0,1)
	 * @param colonna Colonna (0,15)
	 * @param carattere Carattere
	 */
	void scriviCarattere(int riga, int colonna, char carattere);
	/**
	 * Scrivi una stringa di massimo 16 caratteri alla riga scelta.
	 * I caratteri in eccedenza saranno ignorati.
     * @warning Lo schermo viene pulito prima di ogni scrittura.
	 */
	void scrivi(int riga, String messaggio);
	/**
	 * Scrive alla posizione del cursore il carattere salvato indicato.
	 * @param id Numero di carattere salvato in precedenza.
	 */
	size_t scriviCarattereSalvato(uint8_t id);
	/**
	 * Salva un carattere personalizzato
	 * @param id Numero da assegnare al carattere.
	 * @param bytes Vettore di 8 byte che costituiscono il carattere
	 * graficamente
	 */
	void salvaCarattere(uint8_t id, uint8_t* bytes);
	/**
	 * Accendi lo schermo
	 */
	void accendi();
	/**
	 * Spegni lo schermo
	 */
	void spegni();
	/**
	 * Pulisci lo schermo
	 */
	void pulisci();
};

#endif