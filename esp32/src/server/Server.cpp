#include "Server.hpp"
#include "AsyncJson.h"
#include <ArduinoJson.h>
#include <HTTPClient.h>
#include <WiFi.h>

TaskHandle_t BackendServer::taskSendData;
TaskHandle_t BackendServer::taskStartTraining;
TaskHandle_t BackendServer::taskGetObiettivo;
TaskHandle_t BackendServer::taskGetMoltiplicatoreCalorie;
std::mutex BackendServer::mutexServer;
HTTPClient BackendServer::http;

BackendServer::BackendServer(const char* serverName) {
	http.setReuse(true);
	http.begin(serverName);
	SERVER_NAME		  = String(serverName);
	creatoAllenamento = false;
}

void BackendServer::reset() {
	creatoAllenamento = false;
}

void BackendServer::startTraining() {
	start_training_data_t* startTrainingData = new start_training_data_t();
	startTrainingData->creatoAllenamento	 = &creatoAllenamento;
	startTrainingData->serverName			 = SERVER_NAME;
	xTaskCreatePinnedToCore(startTrainingThreaded, "startTraining", 8192,
							(void*)startTrainingData, 0, &taskStartTraining, 1);
	return;
}

void BackendServer::startTrainingThreaded(void* trainingData_in) {
	mutexServer.lock();
	delay(100);
	start_training_data_t* trainingData =
		static_cast<start_training_data_t*>(trainingData_in);
	String serverPath("/");
	serverPath.concat("api/allenamento?id=");
	serverPath.concat(WiFi.macAddress());
	Serial.println(serverPath);

	do {
		http.setURL(serverPath);
		int httpResponseCode = http.GET();
		Serial.print("Start training response code: ");
		Serial.println(httpResponseCode);
		Serial.print("Free heap: ");
		Serial.println(ESP.getFreeHeap());
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
				const char* stato = jsonDocument["stato"];
				// Print values.
				if (strcmp(stato, "ok") == 0) {
					(*(trainingData->creatoAllenamento)) = true;
				} else {
					(*(trainingData->creatoAllenamento)) = false;
				}
			} else {
				(*(trainingData->creatoAllenamento)) = false;
			}
		}
		if (!(*(trainingData->creatoAllenamento))) { delay(1000); }
	} while (!(*(trainingData->creatoAllenamento)));

	delete (trainingData);
	mutexServer.unlock();
	vTaskDelete(NULL);
}

void BackendServer::sendData(uint32_t revolutions) {
	upload_data_t* uploadData	  = new upload_data_t();
	uploadData->creatoAllenamento = &creatoAllenamento;
	uploadData->revolutions		  = revolutions;
	uploadData->serverName		  = SERVER_NAME;
	xTaskCreatePinnedToCore(
		sendDataThreaded, "sendData", 8192, (void*)uploadData, 0, &taskSendData, 1);
	return;
}

void BackendServer::sendDataThreaded(void* upload_data_in) {
	upload_data_t* upload_data = static_cast<upload_data_t*>(upload_data_in);
	while (!(*(upload_data->creatoAllenamento))) { delay(500); }
	mutexServer.lock();
	delay(100);
	String serverPath("/");
	Serial.println("reached string creation");
	serverPath.concat("api/uploadData?id=");
	serverPath.concat(WiFi.macAddress());
	serverPath.concat("&valore=");
	serverPath.concat(upload_data->revolutions);
	Serial.println(serverPath);
	http.setURL(serverPath);
	int httpResponseCode = http.GET();
	Serial.print("Start training response code: ");
	Serial.println(httpResponseCode);
	Serial.print("Free heap: ");
	Serial.println(ESP.getFreeHeap());
	Serial.println(http.getString());
	delete (upload_data);
	mutexServer.unlock();
	vTaskDelete(NULL);
}

void BackendServer::getObiettivoThreaded(void* getObiettivoData_in) {
	mutexServer.lock();
	delay(100);
	get_obiettivo_data_t* getObiettivoData =
		static_cast<get_obiettivo_data_t*>(getObiettivoData_in);
	String serverPath("/");
	obiettivo_t obiettivo = { NESSUNO, 0 };
	serverPath.concat("api/getObiettivo?id=");
	serverPath.concat(WiFi.macAddress());
	Serial.println(serverPath);
	http.setURL(serverPath);
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
			long tipologiaObiettivo = jsonDocument["idCategoria"];
			long parametro			= jsonDocument["parametro"];

			Serial.print("tipologia obiettivo = ");
			Serial.println(tipologiaObiettivo);
			Serial.print("target = ");
			Serial.println(parametro);

			// Print values.
			Serial.println(stato);
			Serial.println(tipologiaObiettivo);
			if (strcmp(stato, "errore") != 0) {
				obiettivo = { (tipologiaObiettivo_t)tipologiaObiettivo, (uint32_t)parametro };
			}
		}
	}
	*(getObiettivoData->obiettivo) = obiettivo;
	delete (getObiettivoData);
	mutexServer.unlock();
	vTaskDelete(NULL);
}

void BackendServer::getObiettivo(obiettivo_t* obiettivo_in) {
	get_obiettivo_data_t* getObiettivoData = new get_obiettivo_data_t();
	getObiettivoData->obiettivo			   = obiettivo_in;
	getObiettivoData->serverName		   = SERVER_NAME;
	xTaskCreatePinnedToCore(getObiettivoThreaded, "getObiettivo", 8192,
							(void*)getObiettivoData, 0, &taskGetObiettivo, 1);
	return;
}

void BackendServer::getMoltiplicatoreCalorie(float* moltiplicatore_in) {
	get_moltiplicatore_data_t* getMoltiplicatoreCalorieData =
		new get_moltiplicatore_data_t();
	getMoltiplicatoreCalorieData->moltiplicatore = moltiplicatore_in;
	getMoltiplicatoreCalorieData->serverName	 = SERVER_NAME;
	xTaskCreatePinnedToCore(
		getMoltiplicatoreCalorieThreaded, "getMoltiplicatoreCalorie", 8192,
		(void*)getMoltiplicatoreCalorieData, 0, &taskGetMoltiplicatoreCalorie, 1);
	return;
}

void BackendServer::getMoltiplicatoreCalorieThreaded(void* getMoltiplicatoreCalorieData_in) {
	mutexServer.lock();
	delay(100);
	get_moltiplicatore_data_t* getMoltiplicatoreCalorieData =
		static_cast<get_moltiplicatore_data_t*>(getMoltiplicatoreCalorieData_in);
	String serverPath("/");
	serverPath.concat("api/getMoltiplicatore?id=");
	serverPath.concat(WiFi.macAddress());
	Serial.println(serverPath);
	http.setURL(serverPath);
	int httpResponseCode = http.GET();

	float moltiplicatore = 0.2;


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
			const char* stato = jsonDocument["stato"];
			moltiplicatore	  = jsonDocument["moltiplicatore"];

			Serial.print("moltiplicatore = ");
			Serial.println(moltiplicatore);

			if (strcmp(stato, "errore") != 0) { moltiplicatore = 0.2; }
		}
	}
	*(getMoltiplicatoreCalorieData->moltiplicatore) = moltiplicatore;
	delete (getMoltiplicatoreCalorieData);
	mutexServer.unlock();
	vTaskDelete(NULL);
}

bool BackendServer::checkRegistered() {
	mutexServer.lock();
	delay(100);
	String serverPath("/");
	serverPath.concat("api/getAssociazione?id=");
	serverPath.concat(WiFi.macAddress());
	Serial.println(serverPath);
	http.setURL(serverPath);
	int httpResponseCode = http.GET();

	bool associato = false;


	if (httpResponseCode == 200) {
		StaticJsonDocument<200> jsonDocument;
		String response = http.getString();
		Serial.println(response);
		DeserializationError error = deserializeJson(jsonDocument, response);

		if (!error) {
			const char* stringAssociato;
			// Fetch values.
			//
			// Most of the time, you can rely on the implicit casts.
			// In other case, you can do doc["time"].as<long>();
			const char* stato = jsonDocument["stato"];
			associato		  = jsonDocument["associato"];

			if (strcmp(stato, "errore") == 0) { associato = false; }
		}
	}
	mutexServer.unlock();
	return associato;
}