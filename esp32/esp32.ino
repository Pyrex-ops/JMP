#include "constants.hpp"
#include "src/encoder/NewEncoderAdapter.hpp"
#include "src/motorino/MotorinoGravity.hpp"
#include "src/schermo/Schermo.hpp"
#include "src/trainingManager/TrainingManager.hpp"
#include "src/wifiManager/WifiManager.hpp"

void handleDisconnected();
void handleNewCredentialsRequired();
void handleIdle();
void handleTraining();
void disconnected();

MotorinoGravity motorino(
	MOTORINO_PIN, MINIMUM_MOTORINO_INTENSITY, MOTORINO_LEDC_CHANNEL,
	MOTORINO_LEDC_FREQUENCY, MOTORINO_LEDC_RESOLUTION, MOTORINO_TASK_PRIORITY,
	MOTORINO_TASK_CORE, MOTORINO_TEMPO_FRA_VIBRAZIONI);

NewEncoderAdapter encoder(ENCODER_CLK_PIN, ENCODER_DT_PIN, ENCODER_PPR);
TrainingManager* trainingManager = nullptr;
BackendServer backendServer(API_URL);
uint32_t timestampLastRevolution;
uint32_t lastRevolutionNumber;


typedef enum {
	BOOTSTRAP,
	DISCONNECTED,
	NEW_CREDENTIALS_REQUIRED,
	UNREGISTERED,
	IDLE,
	TRAINING,
} state_t;

WifiManager wifiManager;
state_t currentState = DISCONNECTED;

Schermo schermo;

uint32_t lostConnectionTimestamp;

void setup() {
	Serial.begin(115200);
	encoder.begin();
	motorino.begin();
	schermo.begin();
	lostConnectionTimestamp = millis();
	wifiManager.connect();
	currentState = DISCONNECTED;
	delay(3000);
}

void loop() {
	static state_t lastState = BOOTSTRAP;
	if (lastState != currentState) {
		lastState = currentState;
		schermo.interrompi();
		schermo.pulisci();
	}
	switch (currentState) {
		case DISCONNECTED: handleDisconnected(); break;
		case NEW_CREDENTIALS_REQUIRED: handleNewCredentialsRequired(); break;
		case IDLE: handleIdle(); break;
		case TRAINING: handleTraining(); break;
		case UNREGISTERED: handleUnregistered(); break;
	}
	delay(200);
}

void handleDisconnected() {
	schermo.connessionePersa();
	if (millis() - lostConnectionTimestamp > TIMEOUT_NEW_CREDENTIALS_MILLISECONDS
		|| !wifiManager.hasSavedCredentials()) {
		wifiManager.deleteCredentials();
		Serial.println("new credentials required");
		//schermo.scrivi(0, "new credentials required");
		currentState = NEW_CREDENTIALS_REQUIRED;
	}
	if (wifiManager.checkConnection()) {
		Serial.println("connected");
		//schermo.scrivi(0, "connected");
		encoder.reset();
		currentState = UNREGISTERED;
	}
}

void handleNewCredentialsRequired() {
	char passwordArray[LENGTH + 1];
	for (int i = 0; i < LENGTH; i++) {
		passwordArray[i] = CHARS[esp_random() % (sizeof(CHARS) - 1)];
	}
	passwordArray[LENGTH] = '\0';
	String ssid			  = CONFIGURATION_SSID;
	String password		  = passwordArray;
	schermo.mostraCredenziali(ssid, password);
	wifiManager.getNewCredentials(ssid, password);
	lostConnectionTimestamp = millis();
	wifiManager.connect();
	currentState = DISCONNECTED;
}

void handleUnregistered() {
	schermo.mostraMAC();
	if (!wifiManager.checkConnection()) {
		disconnected();
	} else if (backendServer.checkRegistered()) {
		currentState = IDLE;
	}
	else {
		delay(1000);
	}
}

void handleIdle() {
	if (!wifiManager.checkConnection()) {
		disconnected();
	} else if (encoder.getRevolutions() != 0) {
		Serial.println("training started");
		//schermo.scrivi(0, "training started");
		backendServer.reset();
		trainingManager = new TrainingManager(
			backendServer, SAMPLE_SENDING_PERIOD_SECONDS, &schermo, 0, &motorino);
		timestampLastRevolution = millis();
		encoder.reset();
		lastRevolutionNumber = encoder.getRevolutions();
		currentState		 = TRAINING;
	}
	//motorino.vibra(100);
}

void handleTraining() {
	if (encoder.getRevolutions() != lastRevolutionNumber) {
		lastRevolutionNumber	= encoder.getRevolutions();
		timestampLastRevolution = millis();
	}
	trainingManager->storeData(encoder.getRevolutions());
	if ((millis() - timestampLastRevolution) > TIMEOUT_STOP_TRAINING_MILLISECONDS) {
		Serial.println("training ended");
		//schermo.scrivi(0, "training ended");

		encoder.reset();
		delete (trainingManager);
		currentState = IDLE;
	}
	if (!wifiManager.checkConnection()) {
		encoder.reset();
		delete (trainingManager);
		disconnected();
	}
}

void disconnected() {
	Serial.println("connection lost");
	//schermo.scrivi(0, "connection lost");
	lostConnectionTimestamp = millis();
	wifiManager.connect();
	currentState = DISCONNECTED;
}