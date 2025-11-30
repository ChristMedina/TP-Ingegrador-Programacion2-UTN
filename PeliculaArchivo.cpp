#include <cstdio>
#include <cstring>
#include "PeliculaArchivo.h"

PeliculaArchivo::PeliculaArchivo(const char* nombreArchivo){
    strncpy(_nombreArchivo, nombreArchivo, sizeof(_nombreArchivo)-1);
}

bool PeliculaArchivo::guardar(Pelicula &obj){
    FILE *pFile = fopen(_nombreArchivo, "ab");
    if(pFile == nullptr) return false;

    bool ok = (fwrite(&obj, sizeof(Pelicula), 1, pFile) == 1);
    fclose(pFile);
    return ok;
}

bool PeliculaArchivo::modificar(Pelicula &obj, int pos){
    FILE *pFile = fopen(_nombreArchivo, "rb+");
    if(pFile == nullptr) return false;

    fseek(pFile, pos * sizeof(Pelicula), SEEK_SET);
    bool ok = (fwrite(&obj, sizeof(Pelicula), 1, pFile) == 1);
    fclose(pFile);
    return ok;
}

bool PeliculaArchivo::leer(Pelicula &obj, int pos){
    FILE *pFile = fopen(_nombreArchivo, "rb");
    if(pFile == nullptr) return false;

    fseek(pFile, pos * sizeof(Pelicula), SEEK_SET);
    bool ok = (fread(&obj, sizeof(Pelicula), 1, pFile) == 1);
    fclose(pFile);
    return ok;
}

int PeliculaArchivo::contarRegistros(){
    FILE *pFile = fopen(_nombreArchivo, "rb");
    if(pFile == nullptr) return 0;

    fseek(pFile, 0, SEEK_END);
    int tam = ftell(pFile);
    fclose(pFile);

    return tam / sizeof(Pelicula);
}

int PeliculaArchivo::buscarPorID(int idPelicula){
    int total = contarRegistros();
    Pelicula obj;

    for(int i = 0; i < total; i++){
        if(leer(obj, i)){
            if(obj.getIDPelicula() == idPelicula){
                return i;
            }
        }
    }
    return -1;
}

int PeliculaArchivo::asignarID() {
    Pelicula obj;
    int total = contarRegistros();

    if (total==0) return 1;//si no hay registros le asigna ID = 1

    int maxID = 0;

    //busca el maximo ID guardado
    for(int i = 0; i < total; i++){
        if(leer(obj, i)){
            if(obj.getIDPelicula() > maxID){
                maxID = obj.getIDPelicula();//lo asigna temporalmente
            }
        }
    }
    return maxID + 1;//le asignamos el siguiente id disponible
}
