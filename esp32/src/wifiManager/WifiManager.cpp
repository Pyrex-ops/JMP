#include "WifiManager.hpp"

#define DEFAULT_TEMPORARY_NETWORK_SSID "Configurazione JMPCorda"
#define DEFAULT_TEMPORARY_NETWORK_PASSWORD "JMPitnow"
#define CREDENTIALS_KEY "credenzialiWiFi"

bool WifiManager::checkConnection() {
	return WiFi.status() == WL_CONNECTED;
}

void WifiManager::connect() {

	credentialsManager cManager(CREDENTIALS_KEY);

	wifi_configuration_t wifi_config;

	WiFi.mode(WIFI_STA);

	wifi_config.SSID	 = cManager.getSSID();
	wifi_config.password = cManager.getPassword();

	/*
		Provo a connettermi.
	*/
	WiFi.begin(wifi_config.SSID.c_str(), wifi_config.password.c_str());
}

void WifiManager::getNewCredentials(String& ssid,String& password) {
	credentialsManager cManager(CREDENTIALS_KEY);
	wifi_configuration_t wifi_config;
	WifiPasswordGetter wifiPasswordGetter(ssid.c_str(), password.c_str());
	wifi_config = (wifiPasswordGetter.getWifiConfiguration());
	cManager.newRecord(wifi_config.SSID, wifi_config.password);
}

WifiManager::WifiManager() {}

bool WifiManager::hasSavedCredentials() {
	credentialsManager cManager(CREDENTIALS_KEY);
	return cManager.getSSID().length() != 0;
}

void WifiManager::deleteCredentials() {
	credentialsManager cManager(CREDENTIALS_KEY);
	cManager.dropEveryNamespace();
}