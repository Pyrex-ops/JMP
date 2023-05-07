#ifndef WIFI_MANAGER_H
#define WIFI_MANAGER_H

#include "../credentialsManager/credentialsManager.hpp"
#include "../wifiPasswordGetter/WifiPasswordGetter.hpp"

/**
 * @brief Classe che ha fornisce un'interfaccia per controllare che il microcontrollore sia connesso al wifi, 
 * recuperare le credenziali dall'utente e dalla memoria flash.
 * 
 */
class WifiManager {
    private:
        bool checkCredentials(wifi_configuration_t wifi_config);
        wifi_configuration_t getCredentialsFromUser();
    public:
        WifiManager();
        bool connect();
        void getNewCredentials();
        bool checkConnection();
        bool hasSavedCredentials();
        void deleteCredentials();
};

#endif