#pragma once
#include "PeliculaArchivo.h"

class PeliculaManager {
private:
    PeliculaArchivo _archivoP;

    bool cargarPelicula(Pelicula &obj);

public:
    void cargar();
    void mostrarPelicula(Pelicula &obj);
    void mostrarTodas();
    void buscar();
    void modificar();
    void eliminar();
    void restaurar();

    void buscarPorID();
    void buscarPorNombre();
    void buscarPorDirector();
    void buscarPorGenero();
    void buscarPorClasificacion();

    const char* generoToStr(int tipo);
    const char* clasificacionToStr(int tipo);
};
