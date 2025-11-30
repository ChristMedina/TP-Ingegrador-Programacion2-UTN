#include <cstdio>
#include <cstring>
#include "SalaArchivo.h"

SalaArchivo::SalaArchivo(const char* nombreArchivo) {
    strncpy(_nombreArchivo, nombreArchivo, sizeof(_nombreArchivo)-1);
}

bool SalaArchivo::guardar(Sala& obj){
    FILE* pFile = fopen(_nombreArchivo, "ab");
    if(pFile== nullptr) return false;

    bool ok = fwrite(&obj, sizeof(Sala), 1, pFile);
    fclose(pFile);

    return ok;
}

bool SalaArchivo::modificar(Sala& obj, int pos){
    FILE* pFile= fopen(_nombreArchivo, "rb+");
    if(pFile== nullptr) return false;

    fseek(pFile, pos * sizeof(Sala), SEEK_SET);

    bool ok = fwrite(&obj, sizeof(Sala), 1, pFile);
    fclose(pFile);

    return ok;
}

bool SalaArchivo::leer(Sala& obj, int pos){
    FILE* pFile= fopen(_nombreArchivo, "rb");
    if(pFile== nullptr) return false;

    fseek(pFile, pos * sizeof(Sala), SEEK_SET);

    bool ok = fread(&obj, sizeof(Sala), 1, pFile);
    fclose(pFile);

    return ok;
}

int SalaArchivo::contarRegistros(){
    FILE* pFile= fopen(_nombreArchivo, "rb");
    if(pFile== nullptr) return 0;

    fseek(pFile, 0, SEEK_END);

    int tam = ftell(pFile);
    fclose(pFile);

    return tam / sizeof(Sala);
}

int SalaArchivo::buscarPorID(int id){
    int total = contarRegistros();
    Sala obj;

    for(int i = 0; i < total; i++){
        if(leer(obj, i)){
            if(obj.getIDSala() == id){
                return i;
            }
        }
    }

    return -1;
}

int SalaArchivo::asignarID() {
    Sala obj;
    int total = contarRegistros();

    if (total==0) return 1;//si no hay registros le asigna ID = 1

    int maxID = 0;

    //busca el maximo ID guardado
    for(int i = 0; i < total; i++){
        if(leer(obj, i)){
            if(obj.getIDSala() > maxID){
                maxID = obj.getIDSala();//lo asigna temporalmente
            }
        }
    }
    return maxID + 1;//le asignamos el siguiente id disponible
}
