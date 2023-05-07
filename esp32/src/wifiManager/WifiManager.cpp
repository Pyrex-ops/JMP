#include "WifiManager.hpp"

#define DEFAULT_TEMPORARY_NETWORK_SSID "ConfigurazioneCorda"
#define DEFAULT_TEMPORARY_NETWORK_PASSWORD "elSugusWifi"
#define DEFAULT_MICROCONTROLLER_IP 8, 8, 8, 8
#define DEFAULT_TEMPORARY_NETWORK_GATEWAY 8, 8, 8, 8
#define DEFAULT_TEMPORARY_NETWORK_SUBNET_MASK 255 , 255, 255, 0
#define CREDENTIALS_KEY "credenzialiWiFi"

bool WifiManager::checkCredentials(wifi_configuration_t wifi_config) {
    uint32_t TIMEOUT_CONNECTION_ATTEMPT_MILLIS = 500;
    bool connected = false;
    uint32_t time_passed_milliseconds = 0;
    WiFi.begin(wifi_config.SSID.c_str(), wifi_config.password.c_str());
    /*
        A volte il wifi status resta WL_DISCONNECTED indefinitamente. 
        Il timeout impedisce un loop infinito in questo caso.
    */
    while(WiFi.status()==WL_DISCONNECTED && time_passed_milliseconds<TIMEOUT_CONNECTION_ATTEMPT_MILLIS) {
        delay(100);
        time_passed_milliseconds += 100;
    }
    while (WiFi.status()!=WL_CONNECT_FAILED && WiFi.status()!=WL_DISCONNECTED && WiFi.status()!=WL_CONNECTED) {
        delay(100);

    }
    if(WiFi.status()==WL_CONNECTED) {
        connected = true;
    }
    return connected;
}

bool WifiManager::checkConnection() {
    return WiFi.status()==WL_CONNECTED;
}

bool WifiManager::connect() {

    if(checkConnection())
        return true;

    credentialsManager cManager(CREDENTIALS_KEY);

    wifi_configuration_t wifi_config;

    bool connected = false;

    WiFi.mode(WIFI_STA); //Optional
    
    wifi_config.SSID = cManager.getSSID();
    wifi_config.password = cManager.getPassword();

    /*
        Provo a connettermi.
    */
    if(checkCredentials(wifi_config)) {
            connected = true;
    } 

    return connected;
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
    Serial.println(wifi_config.SSID);
    Serial.println(wifi_config.password);
    Serial.println(cManager.getSSID());
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