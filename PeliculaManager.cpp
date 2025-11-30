#include <iostream>
#include <cstring>
#include "PeliculaManager.h"
#include "funcionesGlobales.h"

using namespace std;

void PeliculaManager::cargar(){
    system("cls");

    Pelicula nueva;

    if(!cargarPelicula(nueva)) return;

    if(_archivoP.guardar(nueva)){
        cout<<"Pelicula cargada exitosamente."<<endl;
    }else{
        cout<<"Error al guardar la pelicula."<<endl;
    }
}

bool PeliculaManager::cargarPelicula(Pelicula &obj){
    int id = _archivoP.asignarID();
    obj.setIDPelicula(id);
    cout<<"ID asignado: "<<id<<endl;

    char nombre[50];
    cout << "Nombre de la pel¡cula: ";
    cargarCadena(nombre, 50);
    obj.setNombrePelicula(nombre);

    char director[50];
    cout << "Director: ";
    do{
        cargarCadena(director, 50);
        if (!sonLetras(director)){
            cout<<"El nombre tiene que tener letras. Intente de nuevo: ";
        }

    } while (!sonLetras(director));
    obj.setNombreDirector(director);

    int genero;
    cout << "Genero:" << endl;
    cout << " 1) Accion" << endl;
    cout << " 2) Animacion" << endl;
    cout << " 3) Ciencia Ficcion" << endl;
    cout << " 4) Comedia" << endl;
    cout << " 5) Drama" << endl;
    cout << " 6) Documental" << endl;
    cout << " 7) Musical" << endl;
    cout << " 8) Terror" << endl;
    cout << " 9) Otros" << endl;
    cout << "Opcion: ";
    genero = leerEntero();

    while(genero < 1 || genero > 9){
        cout << "Opcion invalida. Intente de nuevo: ";
        genero = leerEntero();
    }

    //Seteamos el genero al elegir la opcion
    switch(genero){
        case 1: obj.setGenero("Accion"); break;
        case 2: obj.setGenero("Animacion"); break;
        case 3: obj.setGenero("Ciencia Ficcion"); break;
        case 4: obj.setGenero("Comedia"); break;
        case 5: obj.setGenero("Drama"); break;
        case 6: obj.setGenero("Documental"); break;
        case 7: obj.setGenero("Musical"); break;
        case 8: obj.setGenero("Terror"); break;
        case 9: obj.setGenero("Otros"); break;
    }

    int clasificacion;
    do {
        cout << "\nClasificacion:\n";
        cout << " 1) ATP\n";
        cout << " 2) +13\n";
        cout << " 3) +18\n";
        cout << "Opcion: ";
        clasificacion = leerEntero();

        if (clasificacion < 1 || clasificacion > 3) {
            cout << "Opcion invalida. Intente de nuevo.\n";
        }
    } while (clasificacion < 1 || clasificacion > 3);
    obj.setClasificacion(clasificacion);

    Fecha fecha;
    cout<<"Fecha de estreno: ";
    fecha.cargar();
    obj.setFechaEstreno(fecha);

    obj.setEstado(true);
    return true;

}

void PeliculaManager::mostrarTodas(){
    Pelicula obj;
    int total = _archivoP.contarRegistros();

    if (total==0){
        cout<<"No hay peliculas cargadas"<<endl;
        return;
    }

    int opcion;
    while(true){
        system("cls");
        cout << "================================" << endl;
        cout << "      Listado de Peliculas      " << endl;
        cout << "================================" << endl;
        cout << "1. Activas" << endl;
        cout << "2. Inactivas" << endl;
        cout << "3. Mostrar todas" << endl;
        cout << "0. Volver" << endl;
        cout << "================================" << endl;
        cout << "Opcion: ";
        opcion = leerEntero();

        if(opcion==0) return;
        if (opcion<0 || opcion >3){
            cout<<"Opcion incorrecta."<<endl;
            continue;
        }

        system("cls");
        int mostradas=0;

        for (int i=0; i<total; i++){
            if(_archivoP.leer(obj,i)){
                switch(opcion){
                    case 1:
                        if(obj.getEstado()){
                            mostrarPelicula(obj);
                            mostradas++;
                        }
                        break;
                    case 2:
                        if(!obj.getEstado()){
                            mostrarPelicula(obj);
                            mostradas++;
                        }
                        break;
                    case 3:
                        mostrarPelicula(obj);
                        mostradas++;
                        break;
                }
            }
        }

        if(mostradas==0){
            cout<<"No hay peliculas para mostrar."<<endl;
        }
        system("pause");
    }

}

void PeliculaManager::mostrarPelicula(Pelicula &obj){
    cout << "--------------------------------" << endl;
    cout << " ID: "<<obj.getIDPelicula()<<endl;
    cout << " Pelicula: "<<obj.getNombrePelicula()<<endl;
    cout << " Director: "<<obj.getNombreDirector()<<endl;
    cout << " Genero: "<<obj.getGenero()<<endl;
    cout << " Clasificacion: "<<clasificacionToStr(obj.getClasificacion())<<endl;
    cout << " Fecha de Estreno: ";
    obj.getFechaEstreno().mostrar();
    cout << "\n--------------------------------" << endl;
}

void PeliculaManager::buscar(){
    int opcion;

    while(true){
        system("cls");
        cout << "================================" << endl;
        cout << "        Buscar Pelicula         " << endl;
        cout << "================================" << endl;
        cout << " 1. ID" << endl;
        cout << " 2. Pelicula " << endl;
        cout << " 3. Director" << endl;
        cout << " 4. Genero" << endl;
        cout << " 5. Clasificacion" << endl;
        cout << " 0. Volver" << endl;
        cout << "================================" << endl;
        cout << "Opcion: ";

        opcion = leerEntero();

        switch(opcion){
            case 1:
                buscarPorID();
                break;
            case 2:
                buscarPorNombre();
                break;
            case 3:
                buscarPorDirector();
                break;
            case 4:
                buscarPorGenero();
                break;
            case 5:
                buscarPorClasificacion();
                break;
            case 0:
                return;
            default:
                cout << "Opcion incorrecta." << endl;
                break;
        }

        system("pause");
    }
}

void PeliculaManager::buscarPorID(){
    system("cls");

    int id;
    Pelicula obj;

    cout<<"ID de la pelicula: ";
    id=leerEntero();

    int pos = _archivoP.buscarPorID(id);

    if (pos == -1){
        cout<<"No se encontro ninguna pelicula."<<endl;
        return;
    }

    if (_archivoP.leer(obj, pos)){
        cout<<endl;
        mostrarPelicula(obj);

        if (obj.getEstado() == false){
            cout << "AVISO: La pelicua se encuentra inactiva." << endl;
        }
    }
    else {
        cout << "Error al buscar el cliente." << endl;
    }
}

void PeliculaManager::buscarPorNombre(){
    system("cls");
    char nombre[50];
    Pelicula obj;
    int total= _archivoP.contarRegistros();
    bool encontrado=false;

    cout<<"Ingrese la Pelicula: ";
    cargarCadena(nombre, 50);

    for(int i=0; i<total; i++){
        if (_archivoP.leer(obj,i)){
            if (stricmp(obj.getNombrePelicula(), nombre)==0 && obj.getEstado()){
                mostrarPelicula(obj);
                encontrado=true;
            }
        }
    }

    if (!encontrado){
        cout<<"No se encontraron peliculas con ese nombre."<<endl;
    }

    //system("pause");
}

void PeliculaManager::buscarPorDirector(){
    system("cls");
    char director[50];
    Pelicula obj;
    int total= _archivoP.contarRegistros();
    bool encontrado=false;

    cout<<"Ingrese la Pelicula: ";
    cargarCadena(director, 50);

    for(int i=0; i<total; i++){
        if (_archivoP.leer(obj,i)){
            if (stricmp(obj.getNombreDirector(), director)==0 && obj.getEstado()){
                mostrarPelicula(obj);
                encontrado=true;
            }
        }
    }

    if (!encontrado){
        cout<<"No se encontraron peliculas dirigidas por "<<director<<"."<<endl;
    }

    //system("pause");
}

void PeliculaManager::buscarPorGenero(){
    system("cls");
    int opcGenero;
    Pelicula obj;
    int total= _archivoP.contarRegistros();
    bool encontrado= false;

    cout << "================================" << endl;
    cout << "       Buscar por Genero        " << endl;
    cout << "================================" << endl;
    cout << " 1) Accion" << endl;
    cout << " 2) Animacion" << endl;
    cout << " 3) Ciencia Ficcion" << endl;
    cout << " 4) Comedia" << endl;
    cout << " 5) Drama" << endl;
    cout << " 6) Documental" << endl;
    cout << " 7) Musical" << endl;
    cout << " 8) Terror" << endl;
    cout << " 9) Otros" << endl;
    cout << "--------------------------------" << endl;
    cout << "Opcion: ";

    opcGenero=leerEntero();

    while(opcGenero <1 || opcGenero>9){
        cout<<"Opcion invalida. Intente de nuevo: ";
        opcGenero=leerEntero();
    }

    const char* generoBuscado=nullptr;

    switch(opcGenero){
        case 1: generoBuscado = ("Accion"); break;
        case 2: generoBuscado = ("Animacion"); break;
        case 3: generoBuscado = ("Ciencia Ficcion"); break;
        case 4: generoBuscado = ("Comedia"); break;
        case 5: generoBuscado = ("Drama"); break;
        case 6: generoBuscado = ("Documental"); break;
        case 7: generoBuscado = ("Musical"); break;
        case 8: generoBuscado = ("Terror"); break;
        case 9: generoBuscado = ("Otros"); break;
    }

    system("cls");
    for(int i=0; i<total; i++){

        if(_archivoP.leer(obj, i)){
            if(obj.getEstado() && stricmp(obj.getGenero(), generoBuscado)==0){
                mostrarPelicula(obj);
                encontrado=true;
            }
        }
    }

    if(!encontrado){
        cout<<"No se encontraron peliculas de ese genero."<<endl;
        return;
    }

    //system("pause");
}

void PeliculaManager::buscarPorClasificacion(){
    system("cls");
    int clasificacion;
    Pelicula obj;
    int total= _archivoP.contarRegistros();
    bool encontrado=false;

    cout << "================================" << endl;
    cout << "    Buscar por Clasificacion    " << endl;
    cout << "================================" << endl;
    cout << " 1) ATP" << endl;
    cout << " 2) +13" << endl;
    cout << " 3) +18" << endl;
    cout << "================================" << endl;
    cout << "Opcion: ";
    clasificacion = leerEntero();

    while(clasificacion<1 || clasificacion>3){
        cout<<"Opcion invalida. Intente de nuevo: ";
        clasificacion = leerEntero();
    }

    system("cls");
    cout<<"Peliculas:"<<endl;

    for(int i=0; i<total; i++){
        if(_archivoP.leer(obj, i)){
            if(obj.getEstado() && obj.getClasificacion()==clasificacion){
                mostrarPelicula(obj);
                encontrado=true;
            }
        }
    }

    if(!encontrado){
        cout << "\nNo se encontraron peliculas con esta clasificacion.\n";
    }

    system("pause");
}

void PeliculaManager::modificar(){
    system("cls");

    int id;
    cout << "================================" << endl;
    cout << "       Modificar Pelicula       " << endl;
    cout << "================================" << endl;
    cout << "Ingrese el ID: ";
    id =leerEntero();

    int pos=_archivoP.buscarPorID(id);
    if(pos==-1){
        cout<<"No se econtro la pelicula."<<endl;
        return;
    }

    Pelicula obj;
    if(!_archivoP.leer(obj, pos)){
        cout<<"Error en el registro."<<endl;
        return;
    }

    if (!obj.getEstado()){
        cout<<"La pelicula esta dada de baja. Necesita restaurarla."<<endl;
        return;
    }

    //system("cls");
    mostrarPelicula(obj);
    cout << "\n Que desea modificar?"<<endl;
    cout << " 1) Pelicula"<<endl;
    cout << " 2) Director"<<endl;
    cout << " 3) Genero"<<endl;
    cout << " 4) Clasificacion"<<endl;
    cout << " 5) Fecha de Estreno"<<endl;
    cout << " 0) Cancelar"<<endl;
    cout << " Opcion: ";
    int opcion = leerEntero();

    int clasificacion;
    char aux[50];
    Fecha fecha;
    cout<<endl;
    switch(opcion){
        case 1:
            cout<<"Nuevo nombre: ";
            cargarCadena(aux, 50);
            obj.setNombrePelicula(aux);
            break;

        case 2:
            cout <<"Nuevo director: ";
            cargarCadena(aux, 50);
            obj.setNombreDirector(aux);
            break;

        case 3:{
            int opcGenero;
            cout << "Genero:"<<endl;
            cout << " 1) Accion" << endl;
            cout << " 2) Animacion" << endl;
            cout << " 3) Ciencia Ficcion" << endl;
            cout << " 4) Comedia" << endl;
            cout << " 5) Drama" << endl;
            cout << " 6) Documental" << endl;
            cout << " 7) Musical" << endl;
            cout << " 8) Terror" << endl;
            cout << " 9) Otros" << endl;
            cout << "Opcion: ";

            opcGenero=leerEntero();
            while(opcGenero<1 || opcGenero>9){
                cout<<"Opcion invalida. Intente de nuevo: ";
                opcGenero=leerEntero();
            }

            switch(opcGenero){
                case 1: obj.setGenero("Accion"); break;
                case 2: obj.setGenero("Animacion"); break;
                case 3: obj.setGenero("Ciencia Ficcion"); break;
                case 4: obj.setGenero("Comedia"); break;
                case 5: obj.setGenero("Drama"); break;
                case 6: obj.setGenero("Documental"); break;
                case 7: obj.setGenero("Musical"); break;
                case 8: obj.setGenero("Terror"); break;
                case 9: obj.setGenero("Otros"); break;
            }
        } break;

        case 4:
            do{
                cout << "\nClasificacion:"<<endl;
                cout << " 1) ATP\n";
                cout << " 2) +13\n";
                cout << " 3) +18\n";
                cout << "Opcion: ";
                clasificacion = leerEntero();

                if(clasificacion < 1 || clasificacion > 3){
                    cout << "Opcion invalida. Intente de nuevo." << endl;
                }

            } while(clasificacion < 1 || clasificacion > 3);
            obj.setClasificacion(clasificacion);

            break;

        case 5:
            cout<<"Nueva fecha:"<<endl;
            fecha.cargar();
            obj.setFechaEstreno(fecha);
            break;

        case 0:
            return;
        default:
            cout<<"Opcion invalida."<<endl;
            return;
    }

    if(_archivoP.modificar(obj, pos)){
        cout<<"\nPelicula modificada correctamente."<<endl;
        cout<<"Nuevos Cambios:"<<endl;
        mostrarPelicula(obj);
    } else {
        cout<<"Error al modificar la pelicula."<<endl;
    }

    //system("pause");
}

void PeliculaManager::eliminar(){
    system("cls");

    int id;
    cout << "================================" << endl;
    cout << "        Eliminar Pelicula       " << endl;
    cout << "================================" << endl;
    cout << "Ingrese el ID: ";
    id = leerEntero();

    int pos =_archivoP.buscarPorID(id);
    if (pos == -1){
        cout<<"No se encontro la pelicula."<<endl;
        return;
    }

    Pelicula obj;
    if(!_archivoP.leer(obj, pos)){
            cout<<"Error al leer el registro."<<endl;
        return;
    }

    if(!obj.getEstado()){
        cout<<"La pelicula ya esta dada de baja."<<endl;
        return;
    }

    mostrarPelicula(obj);///encontro la pelicula y la muestra
    cout<<"¨Desea continuar con la baja?"<<endl;
    cout<<"1. Si"<<endl;
    cout<<"0. No"<<endl;
    int opcion = leerEntero();

    if(opcion != 1){
        cout<<"Baja cancelada."<<endl;
        return;
    }
    obj.setEstado(false);

    if(_archivoP.modificar(obj, pos)){
        cout<<"Pelicula eliminada."<<endl;
    } else {
        cout<<"Error al eliminar."<<endl;
    }

    //system("pause");
}

void PeliculaManager::restaurar(){
    system("cls");
    int id;
    cout << "================================" << endl;
    cout << "       Restaurar Pelicula       " << endl;
    cout << "================================" << endl;
    cout << "Ingrese el ID: ";
    id = leerEntero();

    int pos = _archivoP.buscarPorID(id);
    if(pos == -1){
        cout << "No se encontro la pelicula."<<endl;
        return;
    }

    Pelicula obj;
    if(!_archivoP.leer(obj, pos)){
        cout<<"Error al leer."<<endl;
        return;
    }

    if(obj.getEstado()){
        cout<<"La pelicula ya esta activa."<<endl;
        return;
    }

    mostrarPelicula(obj);
    cout<<"¨Desea restaurarla?"<<endl;
    cout<<"1. Si"<<endl;
    cout<<"0. No"<<endl;
    int opcion = leerEntero();

    if(opcion != 1){
        cout<<"Restauracion cancelada."<<endl;
        return;
    }

    obj.setEstado(true);

    if(_archivoP.modificar(obj, pos)){
        cout<<"Pelicula restaurada."<<endl;
    } else {
        cout<<"No se pudo restaurar la pelicula."<<endl;
    }

   // system("pause");
}

const char* PeliculaManager::clasificacionToStr(int tipo){
    switch(tipo) {
        case 1: return "ATP";
        case 2: return "+13";
        case 3: return "+18";
    }
    return "Desconocido";
}
