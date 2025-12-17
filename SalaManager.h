#pragma once
#include "Sala.h"
#include "SalaArchivo.h"

class SalaManager {
private:
    SalaArchivo _archivoS;

    bool cargarSala(Sala &obj);

public:
    void cargar();
    void mostrarSala(Sala &obj);
    void mostrarTodas();
    void modificar();
    void eliminar();
    void restaurar();
};
