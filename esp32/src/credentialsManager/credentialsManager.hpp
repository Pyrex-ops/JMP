#ifndef CREDENTIALS_MANAGER
#define CREDENTIALS_MANAGER

#include <Arduino.h>
#include <Preferences.h>

/**
    Classe per la gestione dell'archivio Key-Value su memoria flash dell'ESP32
    Fornisce un interfaccia più astratta rispetto alla libreria "Preferences.h"
*/
class credentialsManager {
    private:
        static const char* namespaceName;
        static int namespaceSize;
        Preferences preferences;

        
    public:
        credentialsManager(const char* namespaceName);
        /**
         * Aggiunge due record all'archivio
         * @param SSID Identificativo della rete
         * @param password password
        */
        bool newRecord(String SSID, String password);
        /**
         * Rimuove un record dall'archivio
         * @param SSID Identificativo da rimuovere dall'archivio
        */
        //bool deleteRecord(String SSID);
        /**
         * Aggiorna i campi SSID e password
         * @param SSID Nuovo identificativo della rete
         * @param newPassword Nuova password che sostituirà la precedente
        */
        bool updateRecord(String newSSID, String newPassword);
        /**
         * Restituisce il valore associato alla chiave
         * @param key Chiave di cui si vuole conoscere il valore associato
        */
        //String getRecord(String key);
        String getPassword();

        String getSSID();

        /**
         * Rimuove tutte le voci senza eliminare il namespace
        */
        bool deleteNamespace();
        /**
         * Elimina l'intero contenuto della memoria in quanto non è fornito un modo per eliminare il singolo namespace
        */
        void dropEveryNamespace();
        /**
         * Distruttore, chiude il namespace aperto
        */
        ~credentialsManager();
        int getSize();
        
};

#endif