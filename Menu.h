#pragma once
#include "ClienteManager.h"
#include "PeliculaManager.h"
#include "SalaManager.h"
#include "VentaManager.h"
#include "Reportes.h"

class Menu{
    private:
        ClienteManager _managerCliente;
        PeliculaManager _managerPelicula;
        SalaManager _managerSala;
        VentaManager _managerVenta;
        Reportes _reportes;

        void menuPrincipal();
        void menuClientes();
        void menuPeliculas();
        void menuSalas();
        void menuVentas();
        void menuReportes();

    public:
        void ejecutar();
};
