#pragma once
#include "PeliculaArchivo.h"

class PeliculaManager {
private:
    PeliculaArchivo _archivoP;

    bool cargarPelicula(Pelicula &obj);
    void mostrarPelicula(Pelicula &obj);

    void buscarPorID();
    void buscarPorNombre();
    void buscarPorDirector();
    void buscarPorGenero();
    void buscarPorClasificacion();

public:
    void cargar();
    void mostrarTodas();
    void buscar();
    void modificar();
    void eliminar();
    void restaurar();

    const char* generoToStr(int tipo);
    const char* clasificacionToStr(int tipo);
};
