#include "WifiManager.hpp"

#define DEFAULT_TEMPORARY_NETWORK_SSID "ConfigurazioneCorda"
#define DEFAULT_TEMPORARY_NETWORK_PASSWORD "elSugusWifi"
#define DEFAULT_MICROCONTROLLER_IP 8, 8, 8, 8
#define DEFAULT_TEMPORARY_NETWORK_GATEWAY 8, 8, 8, 8
#define DEFAULT_TEMPORARY_NETWORK_SUBNET_MASK 255 , 255, 255, 0
#define CREDENTIALS_KEY "credenzialiWiFi"

bool WifiManager::checkConnection() {
    return WiFi.status()==WL_CONNECTED;
}

void WifiManager::connect() {
    
    credentialsManager cManager(CREDENTIALS_KEY);

    wifi_configuration_t wifi_config;

    WiFi.mode(WIFI_STA); //Optional
    
    wifi_config.SSID = cManager.getSSID();
    wifi_config.password = cManager.getPassword();

    /*
        Provo a connettermi.
    */
    WiFi.begin(wifi_config.SSID.c_str(), wifi_config.password.c_str());
}

void WifiManager::getNewCredentials() {
    credentialsManager cManager(CREDENTIALS_KEY);
    wifi_configuration_t wifi_config;
    wifi_config = (new WifiPasswordGetter(DEFAULT_TEMPORARY_NETWORK_SSID,
                                                  DEFAULT_TEMPORARY_NETWORK_PASSWORD,
                                                  DEFAULT_MICROCONTROLLER_IP,
                                                  DEFAULT_TEMPORARY_NETWORK_GATEWAY,
                                                  DEFAULT_TEMPORARY_NETWORK_SUBNET_MASK))->getWifiConfiguration();
    cManager.newRecord(wifi_config.SSID,wifi_config.password);
}

WifiManager::WifiManager() {

}

bool WifiManager::hasSavedCredentials() {
    credentialsManager cManager(CREDENTIALS_KEY);
    return cManager.getSSID().length()!=0;
}

void WifiManager::deleteCredentials() {
    credentialsManager cManager(CREDENTIALS_KEY);
    cManager.dropEveryNamespace();
}