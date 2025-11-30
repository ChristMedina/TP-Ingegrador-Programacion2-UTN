#pragma once
#include "Pelicula.h"

class PeliculaArchivo {
private:
    char _nombreArchivo[30];

public:
    PeliculaArchivo(const char* nombreArchivo = "Peliculas.dat");

    bool guardar(Pelicula &obj);
    bool modificar(Pelicula &obj, int pos);
    bool leer(Pelicula &obj, int pos);
    int contarRegistros();
    int buscarPorID(int idPelicula);
    int asignarID();
};
