#include "credentialsManager.hpp"
#include <nvs_flash.h>
#include <stdio.h>

const char *credentialsManager::namespaceName = nullptr;
int credentialsManager::namespaceSize		  = 0;

credentialsManager::credentialsManager(const char *namespaceName) {
	if (namespaceName[0] != '\0') {	 //Controlliamo che il vettore di caratteri
									 //fornito non sia vuoto
		credentialsManager::namespaceName = namespaceName;
		credentialsManager::namespaceSize = 0;
		preferences.begin(credentialsManager::namespaceName, false);

	} else {
		credentialsManager::namespaceName = "credenziali";
		credentialsManager::namespaceSize = 0;
		preferences.begin(credentialsManager::namespaceName, false);
	}
}

bool credentialsManager::newRecord(String SSID, String password) {
	//Non supportate reti senza password (lunghezza minima 8 caratteri,
	//richiesto da WPA)
	if (SSID.length() < 2 || password.length() < 8 || SSID.length() > 32
		|| password.length() > 63) {
		return false;
	}
	//Senza questi "+1" perdiamo pezzi dei valori
	//Casting delle Stringe a vettori di caratteri
	char *charSSID	   = new char[SSID.length() + 1];
	char *charPASSWORD = new char[password.length() + 1];
	SSID.toCharArray(charSSID, SSID.length() + 1);
	password.toCharArray(charPASSWORD, password.length() + 1);
	//Salviamo le credenziali in corrispondenza delle chiavi "ssid" e "password"
	if (preferences.putString("ssid", charSSID) > 0
		&& preferences.putString("password", charPASSWORD) > 0) {
		delete charPASSWORD;
		delete charSSID;
		credentialsManager::namespaceSize++;
		return true;
	}
	delete charPASSWORD;
	delete charSSID;
	return false;
}

String credentialsManager::getSSID() {
	return preferences.getString("ssid");
}

String credentialsManager::getPassword() {
	return preferences.getString("password");
}

bool credentialsManager::deleteNamespace() {
	credentialsManager::namespaceSize = 0;
	return preferences.clear();
}


credentialsManager::~credentialsManager() {
	preferences.end();
}

void credentialsManager::dropEveryNamespace() {
	//TODO: Trova un modo per richiamare il distruttore
	//credentialsManager::~credentialsManager();
	preferences.end();
	credentialsManager::namespaceSize = 0;
	nvs_flash_erase();	// Cancella la memoria flash non volatile
	nvs_flash_init();	// e la inizializza
}

int credentialsManager::getSize() {
	return credentialsManager::namespaceSize;
}