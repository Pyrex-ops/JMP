#include "Schermo.hpp"

Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

Schermo::Schermo() {}

void Schermo::begin() {
	if (!display.begin(SSD1306_SWITCHCAPVCC, SCREEN_ADDRESS)) {
		Serial.println("SSD1306 allocation failed");
	}
	pulisci();
	display.setCursor(0, 18);
	display.setTextSize(4);
	display.println("JMPit");
	display.display();
	delay(3000);
	pulisci();
}

void Schermo::pulisci() {
	display.clearDisplay();
	display.setTextColor(SSD1306_WHITE);
	display.setTextSize(1);
	display.setCursor(0, 0);
	display.display();
}

void Schermo::informazioniAllenamento(
	uint32_t salti, uint32_t tempoAllenamento, uint32_t calorie) {
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
	display.print(tempoAllenamento);
	display.display();
}

void Schermo::connessionePersa() {
	pulisci();
	display.setTextSize(2);
	display.setCursor(30, 0);
	display.print("LINK");
	display.setTextSize(4);
	display.setCursor(6, 32);
	display.println("PERSO");
	display.display();
	lampeggia(3);
}

void Schermo::inserisciCredenziali() {
	pulisci();
	display.setTextSize(2);
	display.setCursor(20, 0);
	display.print("CONNETTI");
	display.setTextSize(4);
	display.setCursor(6, 32);
	display.println("Wi-Fi");
	display.display();
}

void Schermo::obiettivoRaggiunto(uint8_t tipo) {
	/**
	 * (1, 'Numero di salti eseguiti durante l'allenamento.'),
		(2, 'Calorie spese durante l'allenamento.'),
		(3, 'Tempo di allenamento in minuti.')
	*/
	pulisci();
	switch (tipo) {
		case 1:
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
		case 2:
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
		case 3:
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
}

void Schermo::lampeggia(uint8_t volte) {
	for (uint8_t i = 0; i < volte; i++) {
		delay(1000);
		display.invertDisplay(true);
		delay(1000);
		display.invertDisplay(false);
		delay(1000);
	}
}