#pragma once
#include "Venta.h"

class VentaArchivo {
private:
    char _nombreArchivo[30];

public:
    VentaArchivo(const char* nombreArchivo = "Ventas.dat");

    bool guardar(Venta &obj);
    bool modificar(Venta &obj, int pos);
    bool leer(Venta &obj, int pos);
    int contarRegistros();
    int buscarPorID(int id);
    int asignarID();
};
