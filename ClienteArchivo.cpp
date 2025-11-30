#include <iostream>
#include <cstring>
#include <cstdio>
#include "ClienteArchivo.h"
#include "Cliente.h"

using namespace std;

ClienteArchivo::ClienteArchivo(const char* nombreArchivo) {
    strncpy(_nombreArchivo, nombreArchivo, sizeof(_nombreArchivo) - 1);
}

bool ClienteArchivo::guardar(Cliente& obj) {
    FILE *pFile;
    pFile = fopen(_nombreArchivo, "ab");

    if (pFile == nullptr) { return false; }

    bool escribio = fwrite(&obj, sizeof(Cliente), 1, pFile);
    fclose(pFile);

    return escribio;
}

bool ClienteArchivo::modificar(Cliente& obj, int pos) {
    FILE *pFile;
    pFile = fopen(_nombreArchivo, "rb+");

    if (pFile == nullptr) { return false; }

    fseek(pFile, pos * sizeof(Cliente), SEEK_SET);

    // Escribe el objeto modificado
    bool escribio = fwrite(&obj, sizeof(Cliente), 1, pFile);
    fclose(pFile);

    return escribio;
}

bool ClienteArchivo::leer(Cliente &obj, int pos) {
    FILE *pFile;
    pFile = fopen(_nombreArchivo, "rb");

    if (pFile == nullptr) { return false; }

    fseek(pFile, pos * sizeof(Cliente), SEEK_SET);

    bool leyo = fread(&obj, sizeof(Cliente), 1, pFile);
    fclose(pFile);

    return leyo;
}

int ClienteArchivo::contarRegistros() {
    FILE *p;
    p = fopen(_nombreArchivo, "rb");

    if (p == nullptr) { return 0; }

    fseek(p, 0, SEEK_END); // Mueve el puntero al final del archivo
    int tam = ftell(p);
    fclose(p);

    return tam / sizeof(Cliente);
}

int ClienteArchivo::buscarPorDNI(const char* dni) {
    int total = contarRegistros();

    Cliente obj;

    for (int i = 0; i < total; i++) {
        if (leer(obj, i)) {
            if (strcmp(obj.getDNI(), dni) == 0) {// Compara el dni del registro con el dni buscado
                return i; //retorna la posicion
            }
        }
    }

    return -1; //si no lo encontro retorna -1
}
