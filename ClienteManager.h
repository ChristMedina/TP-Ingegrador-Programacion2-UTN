#pragma once
#include "Cliente.h"
#include "ClienteArchivo.h"

class ClienteManager{
private:
    ClienteArchivo _archivoC;
    Cliente _cliente;

    void buscarPorDNI();
    void buscarPorNombre();
    void buscarPorApellido();

public:
    void cargar();
    bool cargarCliente(Cliente &obj, bool pedirDni);
    void mostrarCliente(Cliente &obj);
    void mostrarTodos();
    void buscar();
    void modificar();
    void eliminar();
    void restaurar();
};
