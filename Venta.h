#pragma once
#include "Fecha.h"

class Venta {
    private:
        int _idVenta;
        int _idPelicula;
        int _idSala;
        int _cantEntradas;
        float _importeTotal;
        Fecha _fechaProyeccion;
        char _dniComprador[9];
        bool _estado;

    public:
        Venta();
        Venta(int id, int idPeli, int idSala, int cantEnt,
        float impTotal, Fecha fecha, const char* dni, bool estado);

        //setters
        void setIDVenta(int idVenta);
        void setIDPelicula(int idPelicula);
        void setIDSala(int idSala);
        void setCantEntradas(int cantEntradas);
        void setImporteTotal(float importe);
        void setFechaProyeccion(Fecha fechaP);
        void setDNIComprador(const char *dniComprador);
        void setEstado(bool estado);

        //getters
        int getIDVenta();
        int getIDPelicula();
        int getIDSala();
        int getCantEntradas();
        float getImporteTotal();
        Fecha getFechaProyeccion();
        const char* getDNIComprador();
        bool getEstado();
};


