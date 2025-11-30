#include <cstdio>
#include <cstring>
#include "VentaArchivo.h"

VentaArchivo::VentaArchivo(const char* nombreArchivo){
    strncpy(_nombreArchivo, nombreArchivo, sizeof(_nombreArchivo)-1);
}

bool VentaArchivo::guardar(Venta &obj){
    FILE *pFile = fopen(_nombreArchivo, "ab");
    if(pFile == nullptr) return false;

    bool ok = (fwrite(&obj, sizeof(Venta), 1, pFile) == 1);
    fclose(pFile);
    return ok;
}

bool VentaArchivo::modificar(Venta &obj, int pos){
    FILE *pFile = fopen(_nombreArchivo, "rb+");
    if(pFile == nullptr) return false;

    fseek(pFile, pos * sizeof(Venta), SEEK_SET);
    bool ok = (fwrite(&obj, sizeof(Venta), 1, pFile) == 1);
    fclose(pFile);
    return ok;
}

bool VentaArchivo::leer(Venta &obj, int pos){
    FILE *pFile = fopen(_nombreArchivo, "rb");
    if(pFile == nullptr) return false;

    fseek(pFile, pos * sizeof(Venta), SEEK_SET);
    bool ok = (fread(&obj, sizeof(Venta), 1, pFile) == 1);
    fclose(pFile);
    return ok;
}

int VentaArchivo::contarRegistros(){
    FILE *pFile = fopen(_nombreArchivo, "rb");
    if(pFile == nullptr) return 0;

    fseek(pFile, 0, SEEK_END);
    int tam = ftell(pFile);
    fclose(pFile);

    return tam / sizeof(Venta);
}

int VentaArchivo::buscarPorID(int id){
    int total = contarRegistros();
    Venta obj;

    for(int i = 0; i < total; i++){
        if(leer(obj, i)){
            if(obj.getIDVenta() == id){
                return i;
            }
        }
    }
    return -1;
}

int VentaArchivo::asignarID() {
    Venta obj;
    int total = contarRegistros();

    if (total==0) return 1;//si no hay registros le asigna ID = 1

    int maxID = 0;

    //busca el maximo ID guardado
    for(int i = 0; i < total; i++){
        if(leer(obj, i)){
            if(obj.getIDVenta() > maxID){
                maxID = obj.getIDVenta();//lo asigna temporalmente
            }
        }
    }
    return maxID + 1;//le asignamos el siguiente id disponible
}
