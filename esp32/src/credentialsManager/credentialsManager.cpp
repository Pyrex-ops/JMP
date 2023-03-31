#include "credentialsManager.hpp"
#include <nvs_flash.h>
#include <stdio.h>

const char* credentialsManager::namespaceName = nullptr;
int credentialsManager::namespaceSize = 0;

credentialsManager::credentialsManager(const char* namespaceName){
    if(sizeof(namespaceName)>0){ //Sicuramente c'è un altro modo
        credentialsManager::namespaceName = namespaceName;
        credentialsManager::namespaceSize = 0;
        preferences.begin(credentialsManager::namespaceName,false);

    }else
    {
        credentialsManager::namespaceName = "credenziali";
        credentialsManager::namespaceSize = 0;
        preferences.begin(credentialsManager::namespaceName,false);
    }
    
}

bool credentialsManager::newRecord(String SSID, String password){
    /*char *tempSSID = new char[SSID.length()];
    char *tempPASSWORD = new char[SSID.length()];
    SSID.toCharArray(tempSSID,SSID.length()-1);
    password.toCharArray(tempPASSWORD,password.length()-1);
    if(preferences.putString(tempSSID,tempPASSWORD) > 0){
        credentialsManager::namespaceSize++;
        delete tempSSID;
        delete tempPASSWORD;
        return true;
    }
    delete tempSSID;
    delete tempPASSWORD;
    return false;*/
    //Senza questi "+1" perdiamo pezzi dei valori
    char *tempSSID = new char[SSID.length()+1];
    char *tempPASSWORD = new char[password.length()+1];
    SSID.toCharArray(tempSSID,SSID.length()+1);
    password.toCharArray(tempPASSWORD,password.length()+1);
    
    if(preferences.putString("ssid",tempSSID)>0 && preferences.putString("password",tempPASSWORD)>0){
        delete tempPASSWORD;
        delete tempSSID;
        credentialsManager::namespaceSize++;
        return true;
    }
    delete tempPASSWORD;
    delete tempSSID;
    return false;
}

/*bool credentialsManager::deleteRecord(String SSID){
    char *tempSSID = new char[SSID.length()];
    SSID.toCharArray(tempSSID,SSID.length()-1);
    credentialsManager::namespaceSize--;
    bool temp = preferences.remove(tempSSID);
    delete tempSSID;
    return temp;
}*/

//TODO: Da testare
bool credentialsManager::updateRecord(String newSSID, String newPassword){
    char *tempSSID = new char[newSSID.length()+1];
    char *tempPASSWORD = new char[newPassword.length()+1];
    newSSID.toCharArray(tempSSID,newSSID.length()+1);
    newPassword.toCharArray(tempPASSWORD,newPassword.length()+1);
    if(preferences.putString("ssid",tempSSID)>0 && preferences.putString("password",tempPASSWORD)>0){
        delete tempSSID;
        delete tempPASSWORD;
        return true;
    }
    delete tempSSID;
    delete tempPASSWORD;
    return false;
}

/*String credentialsManager::getRecord(String key){
    char *tempKey = new char[key.length()];
    key.toCharArray(tempKey,key.length()-1);
    String temp = preferences.getString(tempKey); //Non riconosce la chiave fornita
    delete tempKey;
    return preferences.getString("ssid");
}*/

String credentialsManager::getSSID(){
    return preferences.getString("ssid");
}

String credentialsManager::getPassword(){
    return preferences.getString("password");
}

bool credentialsManager::deleteNamespace(){
    credentialsManager::namespaceSize=0;
    return preferences.clear();
}


credentialsManager::~credentialsManager(){
    preferences.end();
}

void credentialsManager::dropEveryNamespace(){
    //credentialsManager::~credentialsManager();
    preferences.end(); //TODO: Trova un modo per richiamare il distruttore
    nvs_flash_erase(); // Cancella la memoria flash non volatile
    nvs_flash_init(); // e la inizializza
}

int credentialsManager::getSize(){
    return credentialsManager::namespaceSize;
}