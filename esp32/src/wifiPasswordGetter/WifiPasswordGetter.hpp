#ifndef WIFI_PASSWORD_GETTER
#define WIFI_PASSWORD_GETTER

#include <Arduino.h>
#include <ESPAsyncWebServer.h>

/**
 * @brief Tutti gli stati possibili del processo di configurazione del wifi.
 *
 * Lo stato è utilizzato per determinare eventuali messaggi di errore.
 *
 */
typedef enum {
	NO_INPUT_YET,
	INCORRECT_PASSWORD,
	MISSING_INPUT,
} mainpage_status_t;

/**
 * @brief Credenziali per la connessione ad una rete wifi.
 *
 */
typedef struct {
	String SSID;
	String password;
} wifi_configuration_t;

/**
 * @brief Classe utilizzata per l'ottenimento delle credenziali del wifi.
 *
 * Utilizza un web server per raccoglierle tramite input dell'utente.
 *
 */
class WifiPasswordGetter {
  private:
	const char* TEMPORARY_NETWORK_SSID;
	const char* TEMPORARY_NETWORK_PASSWORD;
	static wifi_configuration_t* wifi_config;
	AsyncWebServer server;
	void start_wifi();
	void stop_wifi();
	static uint16_t numberOfWifiNetworks;
	static void handlePasswordInput(AsyncWebServerRequest* request);
	static const char* MAIN_PAGE;
  public:
	/**
	 * @brief Costruttore della classe WifiPasswordGetter
	 *
	 * @param temporary_network_ssid SSID della rete a cui si connetterà
	 * l'utente
	 * @param temporary_network_password password della rete a cui si connetterà
	 * l'utente
	 */
	WifiPasswordGetter(const char* temporary_network_ssid, const char* temporary_network_password);
	/**
	 * @brief Ottieni le credenziali del wifi.
	 *
	 * Il microcontrollore aprirà un webserver per permettere all'utente di
	 * inserirle tramite un browser.
	 *
	 * @return wifi_configuration_t Struct con SSID e password della rete wifi a
	 * cui dovrà connettersi il microcontrollore.
	 */
	wifi_configuration_t getWifiConfiguration();
	/**
	 * @brief Restituisce il numero di reti wifi.
	 *
	 * Utilizzato dall'endpoint get-ssids per costruire l'array di ssid.
	 *
	 * @return uint16_t
	 */
	static uint16_t getNumberOfWifiNetworks();
	/**
	 * @brief Puntatore all'ssid inserito dall'utente.
	 *
	 */
	static String* candidateSSID;
	/**
	 * @brief Puntatore alla password inserita dall'utente.
	 *
	 */
	static String* candeidatePassword;
};
#endif