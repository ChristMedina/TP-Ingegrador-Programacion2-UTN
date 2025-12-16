#pragma once
#include "VentaArchivo.h"
#include "ClienteArchivo.h"
#include "PeliculaArchivo.h"
#include "PeliculaManager.h"
#include "SalaArchivo.h"

class VentaManager{
private:
    VentaArchivo _archivoV;
    ClienteArchivo _archivoC;
    PeliculaArchivo _archivoP;
    SalaArchivo _archivoS;
    PeliculaManager _managerP;

    bool cargarVenta(Venta &obj);
    void mostrarVenta(Venta &obj);

    bool peliculaActiva(int idPelicula);
    bool salaActiva(int idSala);
    int estadoDeCliente(const char* dni);

    int capacidadSala(int idSala);
    float precioPorTipoSala(int tipoSala);
    int entradasVendidas(int idPelicula, int idSala, const Fecha fecha);

public:
    void cargar();
    void mostrarTodas();
    void anular();
};
