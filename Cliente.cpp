#include <iostream>
#include <cstring>
#include "Cliente.h"

using namespace std;

Cliente::Cliente(){
    strcpy(_dni, "");
    strcpy(_nombre, "");
    strcpy(_apellido, "");
    strcpy(_email, "");
    strcpy(_telefono, "");
    _estado=false;
}

Cliente::Cliente(const char* dni, const char* nombre,
                 const char* apellido, const char* email,
                 const char* telefono, bool estado)
{
    setDNI(dni);
    setNombre(nombre);
    setApellido(apellido);
    setEmail(email);
    setTelefono(telefono);
    setEstado(estado);
}

// Setters
void Cliente::setDNI(const char *dni){
    strncpy(_dni, dni, sizeof(_dni) - 1); //strncpy(destino, origen, tama¤o - 1)
    _dni[sizeof(_dni) - 1] = '\0'; //sizeof(_campo) - 1 = '\0' Se asegura que la cadena termine bien
}

void Cliente::setNombre(const char *nombre){
    strncpy(_nombre, nombre, sizeof(_nombre) - 1);
    _nombre[sizeof(_nombre) - 1] = '\0';
}

void Cliente::setApellido(const char *apellido){
    strncpy(_apellido, apellido, sizeof(_apellido) - 1);
    _apellido[sizeof(_apellido) - 1] = '\0';
}

void Cliente::setEmail(const char *mail){
    strncpy(_email, mail, sizeof(_email) - 1);
    _email[sizeof(_email) - 1] = '\0';
}

void Cliente::setTelefono(const char *telefono){
    strncpy(_telefono, telefono, sizeof(_telefono) - 1);
    _telefono[sizeof(_telefono) - 1] = '\0';
}

void Cliente::setEstado(bool estado){
    _estado = estado;
}


// Getters
const char* Cliente::getDNI() { return _dni; }
const char* Cliente::getNombre() { return _nombre; }
const char* Cliente::getApellido() { return _apellido; }
const char* Cliente::getEmail() { return _email; }
const char* Cliente::getTelefono() { return _telefono; }
bool Cliente::getEstado() { return _estado; }
