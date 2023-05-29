#ifndef WIFI_PASSWORD_GETTER
#define WIFI_PASSWORD_GETTER

#include <Arduino.h>
#include <ESPAsyncWebServer.h>

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
	/**
	 * @brief SSID della rete a cui si connetterà l'utente.
	 *
	 */
	const char* TEMPORARY_NETWORK_SSID;
	/**
	 * @brief Password della rete a cui si connetterà l'utente.
	 *
	 */
	const char* TEMPORARY_NETWORK_PASSWORD;
	/**
	 * @brief Puntatore alla struct dove verranno scritte le credenziali
	 * inserite dall'utente.
	 *
	 */
	static wifi_configuration_t* wifi_config;
	/**
	 * @brief Web server a cui si connetterà l'utente.
	 *
	 */
	AsyncWebServer server;
	/**
	 * @brief Avvia la rete WiFi.
	 *
	 */
	void start_wifi();
	/**
	 * @brief Stoppa la rete WiFi.
	 *
	 */
	void stop_wifi();
	/**
	 * @brief Numero di reti WiFi rilevate dalla scheda di rete.
	 *
	 */
	static uint16_t numberOfWifiNetworks;
	/**
	 * @brief Pagina servita all'utente.
	 *
	 */
	static const char* MAIN_PAGE;
  public:
	/**
	 * @brief Costruttore della classe WifiPasswordGetter.
	 *
	 * @param temporary_network_ssid SSID della rete a cui si connetterà
	 * l'utente.
	 * @param temporary_network_password Password della rete a cui si connetterà
	 * l'utente.
	 */
	WifiPasswordGetter(const char* temporary_network_ssid, const char* temporary_network_password);
	/**
	 * @brief Ottieni le credenziali del wifi.
	 *
	 * Il microcontrollore aprirà un web server per permettere all'utente di
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
	static String* candidatePassword;
};
#endif