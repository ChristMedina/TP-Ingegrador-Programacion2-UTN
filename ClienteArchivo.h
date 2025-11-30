#pragma once
#include "Cliente.h"

class ClienteArchivo {
private:
    char _nombreArchivo[30];

public:
    ClienteArchivo(const char* nombreArchivo = "Clientes.dat");

    bool guardar(Cliente& obj);
    bool modificar(Cliente &obj, int pos);
    bool leer(Cliente& obj, int pos);
    int contarRegistros();
    int buscarPorDNI(const char* dni);
};
