#include "Schermo.hpp"
#include "WiFi.h"
#include <chrono>
#include <iomanip>
#include <sstream>
#include <thread>

Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

Schermo::Schermo() {}

void Schermo::begin() {
	lampeggiando			   = false;
	this->interrompiEsecuzione = false;
	std::unique_lock<std::mutex> lock(this->mutexDisplay);
	if (!display.begin(SSD1306_SWITCHCAPVCC, SCREEN_ADDRESS)) {
		Serial.println("SSD1306 allocation failed");
	}
	lock.unlock();
	pulisci();
	lock.lock();
	display.setCursor(0, 18);
	display.setTextSize(4);
	display.println("JMPit");
	display.display();
	lock.unlock();
	std::thread t([this]() {
		std::unique_lock<std::mutex> lock(this->mutexDisplay);
		delay(3000);
		lock.unlock();
		pulisci();
	});
	t.detach();
}

void Schermo::pulisci() {
	std::lock_guard<std::mutex> lock(this->mutexDisplay);
	display.clearDisplay();
	display.setTextColor(SSD1306_WHITE);
	display.setTextSize(1);
	display.setCursor(0, 0);
	display.display();
}

void Schermo::informazioniAllenamento(
	uint32_t salti, uint32_t tempoAllenamento, uint32_t calorie) {
	if (!this->mutexDisplay.try_lock() || lampeggiando) { return; }

	//Convertiamo i secondi in ore:minuti:secondi
	auto secondi = std::chrono::seconds(tempoAllenamento);
	auto ore	 = std::chrono::duration_cast<std::chrono::hours>(secondi);
	secondi -= ore;
	auto minuti = std::chrono::duration_cast<std::chrono::minutes>(secondi);
	secondi -= minuti;
	display.fillRect(65, 40, 60, 23, SSD1306_BLACK);
	display.fillRect(1, 40, 63, 23, SSD1306_BLACK);
	display.fillRect(65, 4, 60, 8, SSD1306_BLACK);
	//pulisci();
	display.setTextSize(1);
	display.drawRoundRect(0, 0, 128, 16, 0, SSD1306_WHITE);
	display.drawRoundRect(0, 16, 64, 48, 0, SSD1306_WHITE);
	display.drawRoundRect(64, 16, 64, 48, 0, SSD1306_WHITE);
	display.setCursor(4, 4);
	display.println("CALORIE:");
	display.setCursor(66, 4);
	display.print(calorie);
	display.setTextSize(2);
	display.setCursor(2, 20);
	display.print("SALTI");
	display.setCursor(2, 45);
	display.print(salti);
	display.setCursor(66, 20);
	display.print("TEMPO");
	display.setCursor(66, 45);
	std::stringstream ss;
	//Se è trascorso meno di un minuto allora mostriamo mm:ss, altrimenti hh:mm
	if (tempoAllenamento < 3599) {
		ss << std::setfill('0') << std::setw(2) << minuti.count() << ':'
		   << std::setfill('0') << std::setw(2) << secondi.count() << '\n';
	} else {
		ss << std::setfill('0') << std::setw(2) << ore.count() << ':'
		   << std::setfill('0') << std::setw(2) << minuti.count() << '\n';
	}
	//Convertiamo lo "stringstream" in std::string e poi in String
	display.print(ss.str().c_str());
	display.display();
	this->mutexDisplay.unlock();
}

void Schermo::connessionePersa() {
	// pulisci();
	std::unique_lock<std::mutex> lock(this->mutexDisplay);
	display.setTextSize(2);
	display.setCursor(10, 0);
	display.print("CONNES.");
	display.setTextSize(2);
	display.setCursor(6, 32);
	display.println("IN CORSO");
	display.display();
	lock.unlock();
	// std::thread t([this]() {
	// 	lampeggia(3);
	// });
	// t.detach();
}

void Schermo::inserisciCredenziali() {
	// pulisci();
	std::lock_guard<std::mutex> lock(this->mutexDisplay);
	display.setTextSize(2);
	display.setCursor(20, 0);
	display.print("CONNETTI");
	display.setTextSize(4);
	display.setCursor(6, 32);
	display.println("Wi-Fi");
	display.display();
}

void Schermo::obiettivoRaggiunto(tipologiaObiettivo_t tipo) {
	/**
	 * (1, 'Numero di salti eseguiti durante l'allenamento.'),
		(2, 'Calorie spese durante l'allenamento.'),
		(3, 'Tempo di allenamento in minuti.')
	*/
	// pulisci();
	pulisci();
	this->mutexDisplay.lock();

	switch (tipo) {
		case NUMERO_SALTI:
			display.setTextSize(1);
			display.setCursor(35, 0);
			display.print("OBIETTIVO");
			display.setCursor(35, 9);
			display.print("RAGGIUNTO");
			display.setTextSize(4);
			display.setCursor(6, 32);
			display.println("SALTI");
			display.drawRoundRect(0, 28, 128, 36, 10, SSD1306_WHITE);
			display.display();
			break;
		case CALORIE_SPESE:
			display.setTextSize(1);
			display.setCursor(35, 0);
			display.print("OBIETTIVO");
			display.setCursor(35, 9);
			display.print("RAGGIUNTO");
			display.setTextSize(3);
			display.setCursor(0, 34);
			display.println("CALORIE");
			display.drawRoundRect(0, 28, 128, 36, 10, SSD1306_WHITE);
			display.display();
			break;
		case TEMPO_ALLENAMENTO_MINUTI:
			display.setTextSize(1);
			display.setCursor(35, 0);
			display.print("OBIETTIVO");
			display.setCursor(35, 9);
			display.print("RAGGIUNTO");
			display.setTextSize(4);
			display.setCursor(6, 32);
			display.println("TEMPO");
			display.drawRoundRect(0, 28, 128, 36, 10, SSD1306_WHITE);
			display.display();
			break;

		default: break;
	}
	lampeggiando = true;
	this->mutexDisplay.unlock();
	Serial.println("Sto per entrare nel thread lampeggio");
	std::thread t([this]() {
		lampeggia(1);
	});
	t.detach();
}

void Schermo::lampeggia(uint8_t volte) {
	this->mutexDisplay.lock();
	Serial.println("Sono entrato nel thread lampeggio");
	for (uint8_t i = 0; i < volte; i++) {
		// if (this->interrompiEsecuzione) {
		// 	lampeggiando = false;
		// 	this->mutexDisplay.unlock();
		// 	pulisci();
		// 	this->interrompiEsecuzione = !this->interrompiEsecuzione;
		// 	return;
		// }
		delay(1000);
		display.invertDisplay(true);
		delay(1000);
		display.invertDisplay(false);
		delay(1000);
	}
	Serial.println("Sto per unlockare nel thread lampeggio");
	lampeggiando = false;
	this->mutexDisplay.unlock();
	pulisci();
}

void Schermo::mostraCredenziali(String SSID, String password) {
	// pulisci();
	std::unique_lock<std::mutex> lock(this->mutexDisplay);
	display.setTextSize(1);
	display.setCursor(0, 0);
	display.print("CONNETTITI A");
	display.setCursor(0, 16);
	display.setTextSize(2);
	display.print(SSID);
	display.setCursor(45, 36);
	display.setTextSize(1);
	display.print("PASSWORD");
	display.setCursor(0, 46);
	display.setTextSize(2);
	display.print(password);
	display.display();
	lock.unlock();
	// std::thread t([this]() {
	// 	std::lock_guard<std::mutex> lock(this->mutexDisplay);
	// 	delay(1000);
	// });
	// t.detach();
}

void Schermo::interrompi() {
	if (!this->interrompiEsecuzione) {
		this->interrompiEsecuzione = !this->interrompiEsecuzione;
	}
}

void Schermo::mostraMAC() {
	// pulisci();
	std::unique_lock<std::mutex> lock(this->mutexDisplay);

	String MAC = WiFi.macAddress();
	display.setTextSize(2);
	display.setCursor(0, 0);
	display.print("ASSOCIA ID");
	display.setTextSize(2);
	display.setCursor(0, 32);
	display.println(MAC.substring(0, 9));
	display.println(MAC.substring(9));
	display.display();
	lock.unlock();
}