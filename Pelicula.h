#pragma once
#include "Fecha.h"

class Pelicula {
    private:
        int _idPelicula;
        char _nombrePelicula[50];
        char _nombreDirector[50];
        char _genero[50];
        int _clasificacion;
        Fecha _fechaEstreno;
        bool _estado;

    public:
        Pelicula();
        Pelicula(int id, const char* nombrePeli, const char* nombreDire,
                 const char* genero, int clasificacion, Fecha fecha, bool estado);

        //setters
        void setIDPelicula(int idPeli);
        void setNombrePelicula(const char *nombrePeli);
        void setNombreDirector(const char *nombreDirector);
        void setGenero(const char *genero);
        void setClasificacion(int clasificacion);
        void setFechaEstreno(Fecha fechaEstreno);
        void setEstado(bool estado);

        //getters
        int getIDPelicula();
        const char* getNombrePelicula();
        const char* getNombreDirector();
        const char* getGenero();
        int getClasificacion();
        Fecha getFechaEstreno();
        bool getEstado();
};
