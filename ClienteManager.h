#pragma once
#include "Cliente.h"
#include "ClienteArchivo.h"

class ClienteManager{
private:
    ClienteArchivo _archivoC;
    void mostrarCliente(Cliente &obj);

    void buscarPorDNI();
    void buscarPorNombre();
    void buscarPorApellido();

public:
    void cargar();
    bool cargarCliente(Cliente &obj);
    void mostrarTodos();
    void buscar();
    void modificar();
    void eliminar();
    void restaurar();
};
