#include <iostream>
#include <cstring>
#include "SalaManager.h"
#include "funcionesGlobales.h"

using namespace std;

void SalaManager::cargar(){
    system("cls");
    Sala obj;

    if(cargarSala(obj)){
        if(_archivoS.guardar(obj)){
            cout << "Sala cargada correctamente." << endl;
        } else {
            cout << "Error al guardar la sala." << endl;
        }
    }
}

bool SalaManager::cargarSala(Sala &obj){
    int id= _archivoS.asignarID();
    obj.setIDSala(id);
    cout<<"ID asginado: "<<id<<endl;

    char nombre[30];
    cout<<"Nombre de la sala: ";
    cargarCadena(nombre, 30);
    obj.setNombreSala(nombre);

    cout << "Tipo de sala:" << endl;
    cout << " 1) Est ndar" << endl;
    cout << " 2) Premium" << endl;
    cout << " 3) Comfort Plus" << endl;
    cout << "Opci¢n: ";
    int tipo = leerEntero();

    while(tipo < 1 || tipo > 3){
        cout << "Opci¢n inv lida, intente de nuevo: ";
        tipo = leerEntero();
    }
    obj.setTipoSala(tipo);

    cout << "Capacidad de la sala: ";
    int capacidad = leerEntero();

    while(capacidad<10 || capacidad>500){
        cout << "Capacidad invalida. Reintente: ";
        capacidad = leerEntero();
    }
    obj.setCapacidadSala(capacidad);

    obj.setEstado(true);
    return true;
}

void SalaManager::mostrarSala(Sala &obj){
    cout << "--------------------------------" << endl;
    cout << "ID Sala: " << obj.getIDSala() << endl;
    cout << "Nombre: " << obj.getNombreSala() << endl;

    cout << "Tipo: ";
    switch(obj.getTipoSala()){
        case 1: cout << "Est ndar"; break;
        case 2: cout << "Premium"; break;
        case 3: cout << "Comfort Plus"; break;
    }
    cout << endl;
    cout << "Capacidad: " << obj.getCapacidadSala() << endl;
    cout << "--------------------------------" << endl;
}

void SalaManager::mostrarTodas(){
    system("cls");
    Sala obj;
    int total =_archivoS.contarRegistros();

    if(total ==0){
        cout<<"No hay salas registradas."<<endl;
    }

    int opcion;

    while(true){
        system("cls");
        cout << "================================" << endl;
        cout << "         Listado de Salas       " << endl;
        cout << "================================" << endl;
        cout << "1. Activas" << endl;
        cout << "2. Inactivas" << endl;
        cout << "3. Mostrar Todas" << endl;
        cout << "0. Volver al Menu" << endl;
        cout << "================================" << endl;
        cout << "Opcion: ";
        opcion= leerEntero();

        if(opcion==0) return;

        if(opcion<0 || opcion>3){
            cout<<"Opcion invalida. Reintente."<<endl;
            continue;
        }

        int mostradas=0;

        system("cls");
        for(int i=0; i<total; i++){
            if(_archivoS.leer(obj, i)){

                switch(opcion){
                    case 1:
                        if(obj.getEstado()){
                            mostrarSala(obj);
                            mostradas++;
                        }
                        break;

                    case 2:
                        if(!obj.getEstado()){
                            mostrarSala(obj);
                            mostradas++;
                        }
                        break;
                    case 3:
                        mostrarSala(obj);
                        mostradas++;
                        break;
                }
            }
        }

        if(mostradas==0){
            cout<<"No hay salas registradas."<<endl;
        }
        system("pause");
    }
}

void SalaManager::modificar(){
    system("cls");

    int id;
    cout << "================================" << endl;
    cout << "        Modificar Sala          " << endl;
    cout << "================================" << endl;
    cout << "Ingrese el ID de la sala: ";
    id = leerEntero();

    int pos=_archivoS.buscarPorID(id);
    if(pos==-1){
        cout<<"No se encontr¢ la sala."<<endl;
        return;
    }

    Sala obj;
    if(!_archivoS.leer(obj, pos)){
        cout<<"Error al lerr el registro."<<endl;
        return;
    }

    if(!obj.getEstado()){
        cout<<"La sala esta inactiva. Primero debe restaurarla."<<endl;
        return;
    }

    mostrarSala(obj);
    cout << "\n¨Qu‚ desea modificar?" << endl;
    cout << "1) Nombre" << endl;
    cout << "2) Tipo de sala" << endl;
    cout << "3) Capacidad" << endl;
    cout << "0) Cancelar" << endl;
    cout << "Opci¢n: ";

    int opcion=leerEntero();
    char aux[30];
    int tipo;
    int cap;

    switch(opcion){
        case 1:
            cout<<"Nuevo nombre: ";
            cargarCadena(aux, 30);
            obj.setNombreSala(aux);
            break;

        case 2:
            cout << "\nTipo de sala:" <<endl;
            cout << " 1) Est ndar" <<endl;
            cout << " 2) Premium" <<endl;
            cout << " 3) Comfort Plus" <<endl;
            cout << "Opci¢n: ";
            tipo = leerEntero();
            while(tipo<1 || tipo >3){
                cout<<"Opcion invalida. Reintente:";
                tipo=leerEntero();
            }
            obj.setTipoSala(tipo);
            break;

        case 3:
            do{
                cout<<"Nueva Capacidad: ";
                cap=leerEntero();
                if(cap<10 || cap>500){
                    cout<<"Capacidad invalida. Reintente."<<endl;
                }

            }while(cap<10 || cap >500);
            obj.setCapacidadSala(cap);
            break;
        case 0:
            return;
        default:
            cout<<"Opcion invalida."<<endl;
            return;
    }

    if(_archivoS.modificar(obj, pos)){
        cout<<"\nSala modificada correctamente."<<endl;
        cout<<"Nuevos cambios:"<<endl;
        mostrarSala(obj);
    }else {
        cout<<"Error al modificar la sala."<<endl;
    }

}

void SalaManager::eliminar(){
    system("cls");

    int id;
    cout << "================================" << endl;
    cout << "        Eliminar Sala           " << endl;
    cout << "================================" << endl;
    cout << "Ingrese el ID de la sala: ";
    id = leerEntero();

    int pos=_archivoS.buscarPorID(id);

    if(pos==-1){
        cout<<"No se encontro la sala."<<endl;
        return;
    }

    Sala obj;
    if(!_archivoS.leer(obj, pos)){
        cout<<"Error al leer el registro."<<endl;
        return;
    }

    if(!obj.getEstado()){
        cout<<"La sala ya est  inactiva."<<endl;
        return;
    }

    mostrarSala(obj);
    cout<<"¨Desea continuar con la baja?"<<endl;
    cout<<"1. Si"<<endl;
    cout<<"0. No"<<endl;
    int opcion = leerEntero();

    if(opcion != 1){
        cout<<"Baja cancelada."<<endl;
        return;
    }
    obj.setEstado(false);

    if(_archivoS.modificar(obj, pos)){
        cout<<"Sala eliminada correctamente."<<endl;
    } else {
        cout<<"No se pudo eliminar la sala."<<endl;
    }
}

void SalaManager::restaurar(){
    system("cls");
    int id;
    cout << "================================" << endl;
    cout << "         Restaurar Sala         " << endl;
    cout << "================================" << endl;
    cout << "Ingrese el ID: ";
    id = leerEntero();

    int pos = _archivoS.buscarPorID(id);
    if(pos == -1){
        cout << "No se encontro la pelicula."<<endl;
        return;
    }

    Sala obj;
    if(!_archivoS.leer(obj, pos)){
        cout<<"Error al leer."<<endl;
        return;
    }

    if(obj.getEstado()){
        cout<<"La Sala ya esta activa."<<endl;
        return;
    }

    mostrarSala(obj);
    cout<<"¨Desea restaurarla?"<<endl;
    cout<<"1. Si"<<endl;
    cout<<"0. No"<<endl;
    int opcion = leerEntero();

    if(opcion != 1){
        cout<<"Restauracion cancelada."<<endl;
        return;
    }

    obj.setEstado(true);

    if(_archivoS.modificar(obj, pos)){
        cout<<"Sala restaurada."<<endl;
    } else {
        cout<<"No se pudo restaurar la sala."<<endl;
    }

   // system("pause");
}
