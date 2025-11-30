#pragma once
#include "Sala.h"

class SalaArchivo {
private:
    char _nombreArchivo[30];

public:
    SalaArchivo(const char* nombreArchivo = "Salas.dat");

    bool guardar(Sala& obj);
    bool modificar(Sala& obj, int pos);
    bool leer(Sala& obj, int pos);
    int contarRegistros();
    int buscarPorID(int id);
    int asignarID();
};
