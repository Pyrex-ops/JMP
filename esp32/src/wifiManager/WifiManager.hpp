#ifndef WIFI_MANAGER_H
#define WIFI_MANAGER_H

#include "../credentialsManager/credentialsManager.hpp"
#include "../wifiPasswordGetter/WifiPasswordGetter.hpp"

/**
 * @brief Classe che ha fornisce un'interfaccia per controllare che il
 * microcontrollore sia connesso al wifi, recuperare le credenziali dall'utente
 * e dalla memoria flash.
 *
 */
class WifiManager {
  public:
	/**
	 * @brief Costruisce un nuovo oggetto di tipo WifiManager.
	 *
	 */
	WifiManager();
	/**
	 * @brief Tenta la connessione ad una rete wifi utilizzando le credenziali
	 * salvate nella memoria flash.
	 *
	 */
	void connect();
	/**
	 * @brief Avvia la procedura per l'ottenimento di nuove credenziali da parte
	 * dell'utente.
	 * 
	 * @param ssid SSID dell'AP a cui si connetterà l'utente.
	 * @param password Password dell'AP a cui si connetterà l'utente.
	 */
	void getNewCredentials(String& ssid, String& password);
	/**
	 * @brief Controlla se il dispositivo è connesso a una rete wifi.
	 *
	 * @return true Il dispositivo è connesso a una rete wifi.
	 * @return false Il dispositivo non è connesso a una rete wifi.
	 */
	bool checkConnection();
	/**
	 * @brief Controlla se ci sono credenziali salvate nella memoria flash del
	 * dispositivo.
	 *
	 * @return true Ci sono credenziali salvate nella memoria flash del
	 * dispositivo.
	 * @return false Non ci sono credenziali salvate nella memoria flash del
	 * dispositivo.
	 */
	bool hasSavedCredentials();
	/**
	 * @brief Elimina le credenziali salvate nella memoria flash del
	 * dispositivo.
	 *
	 */
	void deleteCredentials();
};

#endif