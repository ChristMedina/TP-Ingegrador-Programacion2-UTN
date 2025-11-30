#pragma once
#include "ClienteManager.h"
#include "PeliculaManager.h"
#include "SalaManager.h"
#include "VentaManager.h"

class Menu{
    private:
        ClienteManager _managerCliente;
        PeliculaManager _managerPelicula;
        SalaManager _managerSala;
        VentaManager _managerVenta;

        void menuPrincipal();
        void menuClientes();
        void menuPeliculas();
        void menuSalas();
        void menuVentas();

    public:
        void ejecutar();
};
