#include "Server.hpp"

BackendServer::BackendServer(String* serverName) {
    SERVER_NAME = serverName;
}

void BackendServer::startTraining() {
    // @todo call endpoint
    return;
}

void BackendServer::sendData(uint32_t revolutions) {
    // @todo call endpoint
    return;
}

obiettivo_t BackendServer::getObiettivo() {
    // @todo call endpoint
    return {
        TEMPO_ALLENAMENTO_MINUTI,
        1,
    };
}

float BackendServer::getMoltiplicatoreCalorie() {
    // @todo call endpoint
    return 1.2;
}