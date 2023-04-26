#include "WifiManager.hpp"

#define DEFAULT_TEMPORARY_NETWORK_SSID "ConfigurazioneCorda"
#define DEFAULT_TEMPORARY_NETWORK_PASSWORD "elSugusWifi"
#define DEFAULT_MICROCONTROLLER_IP 8, 8, 8, 8
#define DEFAULT_TEMPORARY_NETWORK_GATEWAY 8, 8, 8, 8
#define DEFAULT_TEMPORARY_NETWORK_SUBNET_MASK 255 , 255, 255, 0
#define CREDENTIALS_KEY "credenzialiWiFi"

bool WifiManager::checkCredentials(wifi_configuration_t wifi_config) {
    uint32_t TIMEOUT_CONNECTION_ATTEMPT_MILLIS = 3000;
    bool connected = false;
    uint32_t time_passed_milliseconds = 0;
    WiFi.begin(wifi_config.SSID.c_str(), wifi_config.password.c_str());
    /*
        A volte il wifi status resta WL_DISCONNECTED indefinitamente. 
        Il timeout impedisce un loop infinito in questo caso.
    */
    while(WiFi.status()==WL_DISCONNECTED && time_passed_milliseconds<TIMEOUT_CONNECTION_ATTEMPT_MILLIS) {
        delay(500);
        time_passed_milliseconds += 500;
    }
    while (WiFi.status()!=WL_CONNECT_FAILED && WiFi.status()!=WL_DISCONNECTED && WiFi.status()!=WL_CONNECTED) {
        delay(500);

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


    Serial.println("\nConnecting");

    Serial.print("Numero totali di chiavi: ");
    Serial.println(cManager.getSize());
    Serial.println("OK");
    if(cManager.getSSID().length()!=0){
        wifi_config.SSID = cManager.getSSID();
        wifi_config.password = cManager.getPassword();

        /*
            Provo a connettermi più volte prima di
            eliminare le credenziali.
        */
        for(int i=0;i<10&&!connected;i++) {
            if(checkCredentials(wifi_config)) {
                connected = true;
            }   
        }
        if(!connected) {
            /*
                Credenziali non più valide. Le elimino.
            */
           cManager.dropEveryNamespace();
        }
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
}

WifiManager::WifiManager() {

}