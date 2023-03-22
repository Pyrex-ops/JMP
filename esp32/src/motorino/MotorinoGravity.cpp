#include "MotorinoGravity.hpp"

MotorinoGravity::MotorinoGravity(uint8_t motorino_pin, uint8_t minimumIntensity) :
    MOTORINO_PIN(motorino_pin) , MINIMUM_INTENSITY(minimumIntensity){}

void MotorinoGravity::begin() {
    pinMode(MOTORINO_PIN,OUTPUT);
    ledcAttachPin(MOTORINO_PIN, 0); 
    ledcSetup(0, 4000, 8); // 12 kHz PWM, 8-bit resolution
}


void MotorinoGravity::vibra(uint16_t millisecondi, uint8_t intensity) {
    if(intensity < MINIMUM_INTENSITY)
        intensity = MINIMUM_INTENSITY;
    ledcWrite(0, intensity);
    delay(millisecondi);
    ledcWrite(0, 0);
}

void MotorinoGravity::vibra(uint16_t millisecondi) {
    ledcWrite(0, 255);
    delay(millisecondi);
    ledcWrite(0, 0);
}

void MotorinoGravity::vibra_intermittente(uint16_t millisecondi_spento, uint16_t millisecondi_acceso, uint16_t numero_periodi, uint8_t intensity) {

}

void MotorinoGravity::vibra_intermittente(uint16_t millisecondi_spento, uint16_t millisecondi_acceso, uint16_t numero_periodi) {

}

