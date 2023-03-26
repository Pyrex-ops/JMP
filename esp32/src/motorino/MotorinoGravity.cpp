#include "MotorinoGravity.hpp"

MotorinoGravity::MotorinoGravity(uint8_t motorinoPin,uint8_t minimumIntensity, uint8_t ledcChannel, uint32_t ledcFrequency, 
    uint8_t ledcResolution , uint8_t taskPriority , uint8_t taskCore) :
    PIN(motorinoPin) , MINIMUM_INTENSITY(minimumIntensity) , LEDC_CHANNEL(ledcChannel) ,
    LEDC_FREQ(ledcFrequency) , LEDC_RESOLUTION(ledcResolution) , TASK_PRIORITY(taskPriority) ,
    TASK_CORE(taskCore){}

void MotorinoGravity::begin() {
    pinMode(PIN,OUTPUT);
    ledcAttachPin(PIN, LEDC_CHANNEL); 
    ledcSetup(LEDC_CHANNEL, LEDC_FREQ, LEDC_RESOLUTION);
}

void MotorinoGravity::vibraTask(void* informazioniVibrazioneVoid) {
    InformazioniVibrazione* infoVibrazione = (InformazioniVibrazione*)(informazioniVibrazioneVoid);
    Serial.print("Sono nel thread. res =");
    Serial.println(infoVibrazione->ledcResolution);
    pinMode(infoVibrazione->pin,OUTPUT);
    ledcAttachPin(infoVibrazione->pin, infoVibrazione->ledcChannel); 
    ledcSetup(infoVibrazione->ledcChannel, infoVibrazione->ledcFrequency, infoVibrazione->ledcResolution);
    ledcWrite(infoVibrazione->ledcChannel, 255);
    delay(infoVibrazione->millisecondi);
    ledcWrite(infoVibrazione->ledcChannel, 0);
    vTaskDelete(NULL);
}

void MotorinoGravity::vibra(uint16_t millisecondi, uint16_t intensity) {
    InformazioniVibrazione infoVibrazione;
    if(intensity < MINIMUM_INTENSITY)
        intensity = MINIMUM_INTENSITY;
    infoVibrazione.intensity = intensity;
    infoVibrazione.ledcChannel = LEDC_CHANNEL;
    infoVibrazione.millisecondi = millisecondi;
    infoVibrazione.pin = PIN;
    infoVibrazione.ledcFrequency = LEDC_FREQ;
    infoVibrazione.ledcResolution = LEDC_RESOLUTION;
    Serial.print("Sono quasi nel thread. res =");
    Serial.println(infoVibrazione.ledcResolution);
    xTaskCreatePinnedToCore(vibraTask, "vibrazione", 8192, (void*)&infoVibrazione, TASK_PRIORITY, &taskVibrazione, 0);
}

void MotorinoGravity::vibra(uint16_t millisecondi) {
    vibra(millisecondi , (1<<LEDC_RESOLUTION)-1);
}

void MotorinoGravity::vibraIntermittente(uint16_t millisecondiSpento, uint16_t millisecondiAceso, uint16_t numeroPeriodi, uint16_t intensity) {

}

void MotorinoGravity::vibraIntermittente(uint16_t millisecondiSpento, uint16_t millisecondiAceso, uint16_t numeroPeriodi) {

}

