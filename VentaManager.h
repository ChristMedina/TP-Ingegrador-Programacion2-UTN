#pragma once
#include "VentaArchivo.h"
#include "ClienteArchivo.h"
#include "PeliculaArchivo.h"
#include "SalaArchivo.h"

class VentaManager{
private:
    VentaArchivo _archivoV;
    ClienteArchivo _archivoC;
    PeliculaArchivo _archivoP;
    SalaArchivo _archivoS;

    bool cargarVenta(Venta &obj);
    void mostrarVenta(Venta &obj);

    bool peliculaActiva(int idPelicula);
    bool salaActiva(int idSala);
    bool clienteActivo(const char* dni);

    int capacidadSala(int idSala);
    float precioPorTipoSala(int tipoSala);
    int entradasVendidas(int idPelicula, int idSala, Fecha fecha);

public:
    void cargar();
    void mostrarTodas();
    void anular();
};
