#include <iostream>
#include <cstring>
#include "Sala.h"

using namespace std;

Sala::Sala() {
    _idSala = 0;
    _tipoSala = 0;
    _capacidadSala = 0;
    _nombreSala[0] = '\0';
    _estado = false;
}

// Setters
void Sala::setIDSala(int idSala) {
    _idSala = idSala;
}

void Sala::setTipoSala(int tipoSala) {
    if (tipoSala < 1 || tipoSala > 3) {
        _tipoSala = 0;
    } else {
        _tipoSala = tipoSala;
    }
}

void Sala::setCapacidadSala(int capacidadSala) {
    _capacidadSala = capacidadSala;
}

void Sala::setNombreSala(const char *nombreSala) {
    strncpy(_nombreSala, nombreSala, sizeof(_nombreSala) - 1);
    _nombreSala[sizeof(_nombreSala) - 1] = '\0';
}

void Sala::setEstado(bool estado) {
    _estado = estado;
}


// Getters
int Sala::getIDSala() {
    return _idSala;
}

int Sala::getTipoSala() {
    return _tipoSala;
}

int Sala::getCapacidadSala() {
    return _capacidadSala;
}

const char* Sala::getNombreSala() {
    return _nombreSala;
}

bool Sala::getEstado() {
    return _estado;
}
