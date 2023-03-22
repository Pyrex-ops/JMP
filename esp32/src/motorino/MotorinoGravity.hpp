#ifndef MOTORINO_GRAVITY_H
#define MOTORINO_GRAVITY_H

#include "Motorino.hpp"

class MotorinoGravity : public Motorino {
    private:
        const uint8_t MOTORINO_PIN;
        const uint8_t MINIMUM_INTENSITY;
    public:
        MotorinoGravity(uint8_t motorino_pin,uint8_t minimumIntensity);
        void begin() override;
        void vibra(uint16_t millisecondi, uint8_t intensity) override;
        void vibra(uint16_t millisecondi) override;
        void vibra_intermittente(uint16_t millisecondi_spento, uint16_t millisecondi_acceso, uint16_t numero_periodi, uint8_t intensity) override;
        void vibra_intermittente(uint16_t millisecondi_spento, uint16_t millisecondi_acceso, uint16_t numero_periodi) override;
};

#endif