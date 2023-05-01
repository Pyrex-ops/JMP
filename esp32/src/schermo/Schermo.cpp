#include "Schermo.hpp"

LiquidCrystal_I2C lcd(0x27, lcdColumns, lcdRows);

Schermo::Schermo() {}

void Schermo::begin() {
	lcd.init();
	lcd.backlight();
}

void Schermo::cursore(int riga, int colonna) {
	if ((riga == 0 || riga == 1) && (colonna >= 0 && colonna < 16)) {
		lcd.setCursor(colonna, riga);
	}
}

void Schermo::scriviCarattere(int riga, int colonna, char carattere) {
	if ((riga == 0 || riga == 1) && (colonna >= 0 && colonna < 16)) {
		lcd.setCursor(colonna, riga);
		lcd.print(carattere);
	}
}

void Schermo::scrivi(int riga, String messaggio) {
	if (riga == 0 || riga == 1) {
        Schermo::pulisci();
		if (messaggio.length() < 16) {
			lcd.setCursor(0, riga);
			lcd.print(messaggio);
		} else {
			lcd.setCursor(0, riga);
			lcd.print(messaggio.substring(0, 15));
		}
	}
}

size_t Schermo::scriviCarattereSalvato(uint8_t id) {
	return lcd.write(id);
}

void Schermo::salvaCarattere(uint8_t id, uint8_t* bytes) {
	lcd.createChar(id, bytes);
}

void Schermo::accendi() {
	lcd.backlight();
}

void Schermo::spegni() {
	lcd.noBacklight();
}

void Schermo::pulisci() {
	lcd.clear();
}