#include "Server.hpp"
#include "AsyncJson.h"
#include <ArduinoJson.h>
#include <HTTPClient.h>
#include <WiFi.h>


const char* BackendServer::GIOCOMUNE_CA =
	"-----BEGIN CERTIFICATE-----\n"
	"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\n"
	"-----END CERTIFICATE-----\n";

TaskHandle_t BackendServer::taskSendData;
TaskHandle_t BackendServer::taskStartTraining;
TaskHandle_t BackendServer::taskGetObiettivo;
TaskHandle_t BackendServer::taskGetMoltiplicatoreCalorie;
std::mutex BackendServer::mutexServer;
HTTPClient BackendServer::http;

BackendServer::BackendServer(const char* serverName) {
	SERVER_NAME		  = String(serverName);
	creatoAllenamento = false;
}

void BackendServer::connect() {
	mutexServer.lock();
	Serial.print("Risultato connessione : ");
	http.setReuse(true);
	bool connected = http.begin(SERVER_NAME, GIOCOMUNE_CA);
	Serial.println(connected);
	mutexServer.unlock();
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
				const char* stato = jsonDocument["stato"];
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
			const char* stato		= jsonDocument["stato"];
			long tipologiaObiettivo = jsonDocument["idCategoria"];
			long parametro			= jsonDocument["parametro"];

			Serial.print("tipologia obiettivo = ");
			Serial.println(tipologiaObiettivo);
			Serial.print("target = ");
			Serial.println(parametro);
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
		StaticJsonDocument<400> jsonDocument;
		String response = http.getString();
		Serial.println(response);
		DeserializationError error = deserializeJson(jsonDocument, response);

		if (!error) {
			const char* stato = jsonDocument["stato"];
			moltiplicatore	  = jsonDocument["moltiplicatore"].as<float>();
			Serial.print("moltiplicatore = ");
			Serial.println(moltiplicatore);

			if (strcmp(stato, "errore") == 0) { moltiplicatore = 0.2; }
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
			const char* stato = jsonDocument["stato"];
			associato		  = jsonDocument["associato"];

			if (strcmp(stato, "errore") == 0) { associato = false; }
		}
	}
	mutexServer.unlock();
	return associato;
}