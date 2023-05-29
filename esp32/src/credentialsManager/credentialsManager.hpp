#ifndef CREDENTIALS_MANAGER
#define CREDENTIALS_MANAGER

#include <Arduino.h>
#include <Preferences.h>

/**
 * @brief Classe per la gestione dell'archivio Key-Value su memoria flash
 * dell'ESP32. Fornisce un interfaccia più astratta rispetto alla libreria
 * "Preferences.h". Memorizza una singola coppia (SSID,password).
 *
 */
class credentialsManager {
  private:
	/**
	 * @brief Il nome del namespace dove sono conservate le credenziali.
	 *
	 */
	static const char* namespaceName;
	/**
	 * @brief Dimensione del namespace.
	 *
	 */
	static int namespaceSize;
	/**
	 * @brief Impostazioni dell'archivio.
	 *
	 */
	Preferences preferences;


  public:
	/**
	 * Costruttore della classe.
	 * @param namespaceName nome arbitrario con cui identificare il contesto in
	 * cui saranno salvate le credenziali.
	 */
	credentialsManager(const char* namespaceName);
	/**
	 * Aggiunge due record all'archivio.
	 * @param SSID Identificativo della rete.
	 * @param password password.
	 */
	bool newRecord(String SSID, String password);
	/**
	 * Restituisce la password memorizzata.
	 */
	String getPassword();
	/**
	 * Restituisce l'SSID salvato.
	 */
	String getSSID();
	/**
	 * Rimuove tutte le voci senza eliminare il namespace.
	 */
	bool deleteNamespace();
	/**
	 * Elimina l'intero contenuto della memoria in quanto non è fornito un modo
	 * per eliminare il singolo namespace.
	 * @warning Sono eliminati anche i dati scritti nella memoria flash da altre
	 * funzioni.
	 */
	void dropEveryNamespace();
	/**
	 * Distruttore, chiude il namespace aperto.
	 */
	~credentialsManager();
	/**
	 * Restituisce il numero di credenziali salvate.
	 * Valori interi in [0,1].
	 */
	int getSize();
};

#endif