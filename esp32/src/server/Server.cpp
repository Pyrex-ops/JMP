#include "Server.hpp"
#include "AsyncJson.h"
#include <ArduinoJson.h>
#include <HTTPClient.h>
#include <WiFi.h>

TaskHandle_t BackendServer::taskSendData;

BackendServer::BackendServer(const char* serverName) {
	SERVER_NAME = String(serverName);
}

void BackendServer::startTraining() {
	HTTPClient http;
	String serverPath(SERVER_NAME.c_str());
	serverPath.concat("api/allenamento?id=");
	serverPath.concat(WiFi.macAddress());
	Serial.println(serverPath);
	http.begin(serverPath.c_str());
	http.GET();
	creatoAllenamento = true;
	return;
}

void BackendServer::sendData(uint32_t revolutions) {
	upload_data_t* uploadData = new upload_data_t();
	uploadData->creatoAllenamento = creatoAllenamento;
	uploadData->revolutions = revolutions;
	uploadData->serverName = SERVER_NAME;
	xTaskCreatePinnedToCore(sendDataThreaded, "vibrazioneIntermittente", 4096,
							(void*)revolutions, 0, &taskSendData, 0);
	return;
}

void BackendServer::sendDataThreaded(void* upload_data_in) {
	HTTPClient http;
	upload_data_t* upload_data = static_cast<upload_data_t*>(upload_data_in);
	String serverPath(upload_data->serverName.c_str());
	serverPath.concat("api/uploadData?id=");
	serverPath.concat(WiFi.macAddress());
	serverPath.concat("&valore=");
	serverPath.concat(upload_data->revolutions);
	Serial.println(serverPath);
	http.begin(serverPath.c_str());
	http.GET();
	Serial.println(http.getString());
	delete (upload_data);
	vTaskDelete(NULL);
}

obiettivo_t BackendServer::getObiettivo() {
	HTTPClient http;
	String serverPath(SERVER_NAME.c_str());
	obiettivo_t obiettivo = { NESSUNO, 0 };
	serverPath.concat("api/getObiettivo?id=");
	serverPath.concat(WiFi.macAddress());
	Serial.println(serverPath);
	http.begin(serverPath.c_str());
	int httpResponseCode = http.GET();


	if (httpResponseCode == 200) {
		StaticJsonDocument<200> jsonDocument;
		String response = http.getString();
		Serial.println(response);
		DeserializationError error = deserializeJson(jsonDocument, response);

		if (!error) {
			// Fetch values.
			//
			// Most of the time, you can rely on the implicit casts.
			// In other case, you can do doc["time"].as<long>();
			const char* stato		= jsonDocument["stato"];
			long tipologiaObiettivo = jsonDocument["idObiettivo"];

			// Print values.
			Serial.println(stato);
			Serial.println(tipologiaObiettivo);
			if (strcmp(stato, "errore") != 0) {
				obiettivo = { (tipologiaObiettivo_t)tipologiaObiettivo, 0 };
			}
		}
	}
	return obiettivo;
}

float BackendServer::getMoltiplicatoreCalorie() {
	// @todo call endpoint
	return 1.2;
}