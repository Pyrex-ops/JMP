#include "MotorinoGravity.hpp"

uint8_t MotorinoGravity::TASK_PRIORITY = 1;
std::queue<InformazioniVibrazioneIntermittente*> MotorinoGravity::infoQueue;
TaskHandle_t MotorinoGravity::taskVibrazione;
uint16_t MotorinoGravity::TEMPO_FRA_VIBRAZIONI;

MotorinoGravity::MotorinoGravity(uint8_t motorinoPin,uint8_t minimumIntensity, uint8_t ledcChannel, uint32_t ledcFrequency, 
    uint8_t ledcResolution , uint8_t taskPriority , uint8_t taskCore , uint16_t tempoFraVibrazioni) :
    PIN(motorinoPin) , MINIMUM_INTENSITY(minimumIntensity) , LEDC_CHANNEL(ledcChannel) ,
    LEDC_FREQ(ledcFrequency) , LEDC_RESOLUTION(ledcResolution),
    TASK_CORE(taskCore){
        TEMPO_FRA_VIBRAZIONI = tempoFraVibrazioni;
        TASK_PRIORITY = taskPriority;
        taskVibrazione = NULL;
    }

void MotorinoGravity::begin() {
    
}

void MotorinoGravity::vibraIntermittenteTask(void* informazioniVibrazioneIntermittenteVoid) {
    InformazioniVibrazioneIntermittente* infoVibrazione = (InformazioniVibrazioneIntermittente*)(informazioniVibrazioneIntermittenteVoid);
    pinMode(infoVibrazione->infoAcceso.pin,OUTPUT);
    ledcSetup(infoVibrazione->infoAcceso.ledcChannel, infoVibrazione->infoAcceso.ledcFrequency, infoVibrazione->infoAcceso.ledcResolution);
    ledcAttachPin(infoVibrazione->infoAcceso.pin, infoVibrazione->infoAcceso.ledcChannel); 
    for(int i=0;i<infoVibrazione->numeroPeriodi;i++) {
        ledcWrite(infoVibrazione->infoAcceso.ledcChannel, infoVibrazione->infoAcceso.intensity);
        delay(infoVibrazione->infoAcceso.millisecondi);
        ledcWrite(infoVibrazione->infoAcceso.ledcChannel, 0);
        delay(infoVibrazione->millisecondiSpento);
    }
    delete(infoVibrazione);
    if(!MotorinoGravity::infoQueue.empty()) {
        void* taskArg = (void*)(infoQueue.front());
        infoQueue.pop();
        delay(MotorinoGravity::TEMPO_FRA_VIBRAZIONI);
        xTaskCreatePinnedToCore(vibraIntermittenteTask, "vibrazioneIntermittente", 4096, taskArg, MotorinoGravity::TASK_PRIORITY, &MotorinoGravity::taskVibrazione, 0);
    }
    else {
        MotorinoGravity::taskVibrazione = NULL;
    }
    vTaskDelete(NULL);
}

void MotorinoGravity::vibraIntermittente(uint16_t millisecondiSpento, uint16_t millisecondiAceso, uint16_t numeroPeriodi, uint16_t intensity) {
    InformazioniVibrazioneIntermittente* infoVibrazione = new InformazioniVibrazioneIntermittente;
    if(intensity < MINIMUM_INTENSITY)
        intensity = MINIMUM_INTENSITY;
    infoVibrazione->infoAcceso.intensity = intensity;
    infoVibrazione->infoAcceso.ledcChannel = LEDC_CHANNEL;
    infoVibrazione->infoAcceso.millisecondi = millisecondiAceso;
    infoVibrazione->infoAcceso.pin = PIN;
    infoVibrazione->infoAcceso.ledcFrequency = LEDC_FREQ;
    infoVibrazione->infoAcceso.ledcResolution = LEDC_RESOLUTION;
    infoVibrazione->millisecondiSpento = millisecondiSpento;
    infoVibrazione->numeroPeriodi = numeroPeriodi;
    if(taskVibrazione != NULL) {
        infoQueue.push(infoVibrazione);
    }
    else {
        xTaskCreatePinnedToCore(vibraIntermittenteTask, "vibrazioneIntermittente", 4096, (void*)infoVibrazione, TASK_PRIORITY, &taskVibrazione, 0);
    }
}

void MotorinoGravity::vibra(uint16_t millisecondi, uint16_t intensity) {
    vibraIntermittente(0,millisecondi,1,intensity);
}

void MotorinoGravity::vibra(uint16_t millisecondi) {
    vibra(millisecondi , (1<<LEDC_RESOLUTION)-1);
}

void MotorinoGravity::vibraIntermittente(uint16_t millisecondiSpento, uint16_t millisecondiAceso, uint16_t numeroPeriodi) {
    vibraIntermittente(millisecondiSpento, millisecondiAceso, numeroPeriodi, (1<<LEDC_RESOLUTION)-1);
}

