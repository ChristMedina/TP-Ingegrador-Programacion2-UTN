#include <iostream>
#include <cstring>
#include "Venta.h"

using namespace std;

Venta::Venta() {
    _idVenta = 0;
    _idPelicula = 0;
    _idSala = 0;
    _cantEntradas = 0;
    _importeTotal = 0;
    strcpy(_dniComprador,"");
    _estado = false;
}

Venta::Venta(int id, int idPeli, int idSala, int cantEnt,
    float impTotal, Fecha fecha, const char* dni, bool estado)
{
    setIDVenta(id);
    setIDPelicula(idPeli);
    setIDSala(idSala);
    setCantEntradas(cantEnt);
    setImporteTotal(impTotal);
    setFechaProyeccion(fecha);
    setDNIComprador(dni);
    setEstado(estado);
}

// Setters
void Venta::setIDVenta(int idVenta) {
    _idVenta = idVenta;
}

void Venta::setIDPelicula(int idPelicula) {
    _idPelicula = idPelicula;
}

void Venta::setIDSala(int idSala) {
    _idSala = idSala;
}

void Venta::setCantEntradas(int cantEntradas) {
    _cantEntradas = cantEntradas;
}

void Venta::setImporteTotal(float importe) {
    _importeTotal = importe;
}

void Venta::setFechaProyeccion(Fecha fechaP) {
    _fechaProyeccion = fechaP;
}

void Venta::setDNIComprador(const char *dniComprador){
    strncpy(_dniComprador, dniComprador, sizeof(_dniComprador) - 1);
    _dniComprador[sizeof(_dniComprador) - 1] = '\0';
}

void Venta::setEstado(bool estado) {
    _estado = estado;
}


// Getters
int Venta::getIDVenta() {
    return _idVenta;
}

int Venta::getIDPelicula() {
    return _idPelicula;
}

int Venta::getIDSala() {
    return _idSala;
}

int Venta::getCantEntradas() {
    return _cantEntradas;
}

float Venta::getImporteTotal() {
    return _importeTotal;
}

Fecha Venta::getFechaProyeccion() {
    return _fechaProyeccion;
}

const char* Venta::getDNIComprador() {
    return _dniComprador;
}

bool Venta::getEstado() {
    return _estado;
}
