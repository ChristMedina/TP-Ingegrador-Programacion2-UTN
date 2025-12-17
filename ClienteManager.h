#pragma once
#include "Cliente.h"
#include "ClienteArchivo.h"

class ClienteManager{
private:
    ClienteArchivo _archivoC;
    Cliente _cliente;

public:
    void cargar();
    bool cargarCliente(const char* dni);
    void mostrarCliente(Cliente &obj);
    void mostrarTodos();
    void buscar();
    void modificar();
    void eliminar();
    void restaurar();
    void buscarPorDNI();
    void buscarPorNombre();
    void buscarPorApellido();
};

