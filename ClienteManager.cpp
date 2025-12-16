#include <iostream>
#include "Cliente.h"
#include "ClienteManager.h"
#include "funcionesGlobales.h"
#include <cstring>

using namespace std;

void ClienteManager::cargar(){
    system("cls");
    Cliente nuevoCliente;

    if (!cargarCliente(nuevoCliente, true)){
        return;
    }

    if (_archivoC.guardar(nuevoCliente)){

        cout<<"Cliente cargado exitosamente."<<endl;
    }
    else {
        cout<<"No se pudo cargar el cliente. "<<endl;
    }
}

bool ClienteManager::cargarCliente(Cliente &obj, bool pedirDni=true){

    char nombre[30];
    char apellido[30];
    char email[30];
    char telefono[12];

    if(pedirDni){
    char dni[9];
    cout<<"DNI: ";

    while (true) {
        cargarCadena(dni, 9);

        if (!sonNumeros(dni) || strlen(dni)!=8) {
            cout << "El DNI tiene que ser numerico y contener 8 digitos. Intente de nuevo: ";
            continue;// el continue sirve para omitir el resto del bucle y vuelve al inicio
        }

        int pos = _archivoC.buscarPorDNI(dni); //Busca si ya existe el dni
        if (pos == -1) {
            break;  //Si no existe sale del bucle y sigue con el resto de la carga
        }

        // vemos si esta activo o dado de baja
        if (pos != -1) {
            Cliente existe;
            _archivoC.leer(existe, pos);

            if (existe.getEstado()) {
                cout << "Ya existe un cliente con ese DNI." << endl;
                return false;
            }
            else {
                cout << "El cliente ya existe pero est  inactivo." << endl;
                return false;
            }
        }

    }
    obj.setDNI(dni);
    }

    cout<<"Nombre: ";
    do{
        cargarCadena(nombre, 30);
        if (!sonLetras(nombre)){
            cout<<"El nombre tiene que tener letras. Intente de nuevo: ";
        }

    } while (!sonLetras(nombre));
    obj.setNombre(nombre);

    cout<<"Apellido: ";
    do{
        cargarCadena(apellido, 30);
        if (!sonLetras(apellido)){
            cout<<"El apellido tiene que tener letras. Intente de nuevo: ";
        }

    } while (!sonLetras(apellido));
    obj.setApellido(apellido);

    cout<<"Email: ";
    do {
        cargarCadena(email, 30);
        if (!validarEmail(email))
            cout << "El email no es valido. Intente de nuevo: ";

    } while (!validarEmail(email));
    obj.setEmail(email);

    cout<<"Telefono: ";
    cargarCadena(telefono, 12);

    while(!sonNumeros(telefono) || strlen(telefono) != 10) {

        if (!sonNumeros(telefono)) {
            cout << "El telefono tiene que ser numerico. Intente de nuevo: ";
        }
        else if (strlen(telefono) != 10) {
            cout << "El telefono tiene que tener 10 digitos. Intente de nuevo: ";
        }
        cargarCadena(telefono, 12);
    }
    obj.setTelefono(telefono);

    obj.setEstado(true);
    return true;
}

void ClienteManager::mostrarCliente(Cliente &obj){

    cout<<"------------------------------------------"<<endl;
    cout<<" DNI:\t\t"<<obj.getDNI()<<endl;
    cout<<" Nombre:\t"<<obj.getNombre()<<endl;
    cout<<" Apellido:\t"<<obj.getApellido()<<endl;
    cout<<" Email:\t\t"<<obj.getEmail()<<endl;
    cout<<" Telefono:\t"<<obj.getTelefono()<<endl;
    cout<<"------------------------------------------"<<endl;
}

void ClienteManager::mostrarTodos(){
    Cliente obj; //declaro un objeto cliente
    int total = _archivoC.contarRegistros(); //cuento el total del registro
    system("cls");

    if (total==0){
        cout<<"No hay clientes registrados."<<endl; //si no hay registros, vuelve.
        return;
    }
    int opcion;
    while (true) {
        system("cls");
        cout << "================================" << endl;
        cout << "      Listado de clientes       " << endl;
        cout << "================================" << endl;
        cout << " 1. Activos" << endl;
        cout << " 2. Inactivos" << endl;
        cout << " 3. Mostrar todos" << endl;
        cout << " 0. Volver al menu" << endl;
        cout << "================================" << endl;
        cout << "Opcion: ";
        opcion=leerEntero();

        if (opcion < 0 || opcion > 3) {
            cout << "Opcion invalida. Intente de nuevo." << endl;
            system("pause>nul");
            continue;
        }

        if (opcion == 0) return;


        // Contador para saber si hay registros mostrados
        int mostrados = 0;
        system ("cls");

        for (int i = 0; i < total; i++){
            if (_archivoC.leer(obj, i)){
                switch(opcion){
                    case 1: // activos
                        if (obj.getEstado()){
                            mostrarCliente(obj);
                            mostrados++;
                        }
                        break;

                    case 2: // inactivos
                        if (!obj.getEstado()){
                            mostrarCliente(obj);
                            mostrados++;
                        }
                        break;

                    case 3: // todos
                        mostrarCliente(obj);
                        mostrados++;
                        break;
                }
            }
        }

        // Si no se mostr¢ ninguno, avisamos
        if (mostrados == 0){
            if (opcion == 1) cout << "No hay clientes activos." << endl;
            if (opcion == 2) cout << "No hay clientes inactivos." << endl;
            if (opcion == 3) cout << "No hay clientes registrados." << endl;
        }

        system("pause");
    }
}

void ClienteManager::buscar(){
    int opcion;

    while (true) {
        system("cls");
        cout << "================================" << endl;
        cout << "         Buscar Cliente         " << endl;
        cout << "================================" << endl;
        cout << " 1. Buscar por DNI" << endl;
        cout << " 2. Buscar por Nombre" << endl;
        cout << " 3. Buscar por Apellido" << endl;
        cout << " 0. Volver al Menu Principal" << endl;
        cout << "================================" << endl;
        cout << "Opcion: ";

        opcion = leerEntero();

        switch(opcion){
            case 1:
                buscarPorDNI();
                break;
            case 2:
                buscarPorNombre();
                break;
            case 3:
                buscarPorApellido();
                break;
            case 0:
                return;  // vuelve al menu principal
            default:
                cout<<"Opci¢n incorrecta. Intente de nuevo."<<endl;
                //system("pause>nul");
                break;
        }

        system("pause>null");
    }
}


void ClienteManager::buscarPorDNI(){
    char dni[9];
    int pos;
    Cliente obj;
    system("cls");

    cout<<"Ingrese el DNI a buscar: ";
    cargarCadena(dni,9);

    if (!sonNumeros(dni) || strlen(dni) != 8){//strlen para medir la longitud de caracteres
        cout << "DNI invalido. Debe contener solo numeros y tener 8 digitos." << endl;
        return;
    }

    pos = _archivoC.buscarPorDNI(dni);

    if (pos==-1){
        cout<<"No se encontr¢ ningun cliente con ese DNI."<<endl;
        return;
    }

    if (_archivoC.leer(obj, pos)){
        cout<<endl;
        mostrarCliente(obj);

        if (obj.getEstado() == false){
            cout << "El cliente se encuentra inactivo." << endl;
        }
    }
    else {
        cout << "Error al buscar el cliente." << endl;
    }

}

void ClienteManager::buscarPorNombre(){
    system("cls");
    char nombre[30];
    int total = _archivoC.contarRegistros();
    bool encontrado = false;
    Cliente obj;

    cout<<"Ingrese el nombre: ";
    cargarCadena(nombre, 30);
    if (!sonLetras(nombre)){
        cout << "El nombre debe contener solo letras." << endl;
        return;
    }

    for (int i=0; i<total; i++){
        if (_archivoC.leer(obj, i)){

            if (stricmp(obj.getNombre(), nombre)==0 && obj.getEstado() == true){
                mostrarCliente(obj);
                encontrado=true;
            }
        }
    }

    if (!encontrado){
        cout<<"No se encontr¢ el cliente"<<endl;
    }
}

void ClienteManager::buscarPorApellido(){
    system("cls");
    char apellido[30];
    int total = _archivoC.contarRegistros();
    bool encontrado = false;
    Cliente obj;

    cout<<"Ingrese el nombre: ";
    cargarCadena(apellido, 30);
    if (!sonLetras(apellido)){
        cout << "El nombre debe contener solo letras." << endl;
        return;
    }

    for (int i=0; i<total; i++){
        if (_archivoC.leer(obj, i)){

            if (stricmp(obj.getApellido(), apellido)==0 && obj.getEstado() == true){
                mostrarCliente(obj);
                encontrado=true;
            }
        }
    }

    if (!encontrado){
        cout<<"No se encontr¢ el cliente"<<endl;
    }
}

void ClienteManager::modificar(){
    char dni[9];
    int pos;
    Cliente obj;
    system("cls");
    cout << "================================" << endl;
    cout << "       Modificar Cliente        " << endl;
    cout << "================================" << endl;
    cout << "Ingrese el dni: ";
    cargarCadena(dni, 9);
    if (!sonNumeros(dni)) {
            cout << "El DNI tiene que ser numerico."<<endl;
            return;
        }

    if (strlen(dni) != 8) {
        cout << "El DNI tiene que contener 8 digitos."<<endl;
        return;
    }

    pos = _archivoC.buscarPorDNI(dni);
    if(pos==-1){
        cout<<"Cliente no encontrado."<<endl;
        return;
    }

    if(!_archivoC.leer(obj, pos)){
        cout<<"No se pudo leer el archivo."<<endl;
        return;
    }

    //system("cls");
    mostrarCliente(obj);

    if(!obj.getEstado()){
        cout <<endl<< "AVISO: El cliente se encuentra inactivo." << endl;
        cout << "Debe restaurarlo antes de modificar sus datos." << endl;
        return;
    }

    int opcion;
    cout << "¨Que  desea modificar?" << endl;
    cout << " 1. Nombre" << endl;
    cout << " 2. Apellido" << endl;
    cout << " 3. Email" << endl;
    cout << " 4. Telefono" << endl;
    cout << " 0. Cancelar" << endl;
    cout << "Opcion: ";
    opcion = leerEntero();

    char aux[30];
    bool modificado=false;

    switch(opcion){
        case 1:{
            cout<<"\nIngrese el nuevo Nombre: ";

            do{
                cargarCadena(aux, 30);
                if(!sonLetras(aux)){
                    cout<<"El nombre solo admite letras. Intente de nuevo: ";
                }

            } while (!sonLetras(aux));

            obj.setNombre(aux);
            modificado=true;
            break;
        }
        case 2:{
            cout<<"\nIngrese el nuevo Apellido: ";

            do{
                cargarCadena(aux, 30);
                if(!sonLetras(aux)){
                    cout<<"El apellido solo admite letras. Intente de nuevo: ";
                }

            } while (!sonLetras(aux));

            obj.setApellido(aux);
            modificado=true;
            break;
        }
        case 3:{
            cout<<"\nIngrese el nuevo Email: ";
            do{
                cargarCadena(aux, 30);
                if(!validarEmail(aux)){
                    cout<<"El email no es valido. Intente de nuevo: ";
                }
            } while(!validarEmail(aux));

            obj.setEmail(aux);
            modificado=true;
            break;
        }
        case 4:
            cout<<"\nIngrese el nuevo Telefono: ";
            cargarCadena(aux, 12);

            while(!sonNumeros(aux) || strlen(aux) != 10) {

                if (!sonNumeros(aux)) {
                    cout << "El telefono tiene que ser numerico. Reintente: ";
                }
                else if (strlen(aux) != 10) {
                    cout << "El telefono tiene que tener 10 digitos. Reintente: ";
                }
                cargarCadena(aux, 12);
            }
            obj.setTelefono(aux);
            modificado=true;
            break;

        case 0:
            cout<<"Modificaci¢n cancelada." <<endl;
            return;

        default:
            cout<<"Opci¢n incorrecta."<<endl;
            return;
    }

    if (modificado){
        if (_archivoC.modificar(obj, pos)){
            cout<<"Cliente modificado exitosamente."<<endl;
            cout<<"\nNuevos Cambios:"<<endl;
            mostrarCliente(obj);
        }else {
            cout<<"No se pudo modificar."<<endl;
        }
    }

}

void ClienteManager::eliminar(){
    char dni[9];
    int pos;
    Cliente obj;

    system("cls");
    cout << "================================" << endl;
    cout << "       Eliminar Cliente         " << endl;
    cout << "================================" << endl;
    cout << "Ingrese el DNI: ";
    cargarCadena(dni, 9);
    if (!sonNumeros(dni) || strlen(dni)!=8) {
            cout << "El DNI tiene que ser numerico y contener 8 digitos."<<endl;
            return;
        }

    pos=_archivoC.buscarPorDNI(dni);

    if(pos==-1){
        cout<<"No se encontr¢ el cliente."<<endl;
        return;
    }

    if(!_archivoC.leer(obj, pos)){
        cout<<"No se pudo leer el registro."<<endl;
        return;
    }

    if (obj.getEstado()==false){
        cout<<"AVISO:El cliente ya est  inactivo."<<endl;
        return;
    }

    mostrarCliente(obj);
    cout<<"¨Desea continuar con la baja?"<<endl;
    cout<<"1. Si"<<endl;
    cout<<"0. No"<<endl;
    int opcion = leerEntero();

    if(opcion != 1){
        cout<<"Baja cancelada."<<endl;
        return;
    }

    obj.setEstado(false);

    if(_archivoC.modificar(obj, pos)){
        cout<<"Cliente "<<obj.getDNI()<<" eliminado exitosamente."<<endl;
    } else{
        cout<<"No se pudo eliminar, error en el registro."<<endl;
    }
}

void ClienteManager::restaurar(){
    char dni[9];
    int pos;
    Cliente obj;

    system("cls");
    cout << "================================" << endl;
    cout << "      Restaurar Cliente         " << endl;
    cout << "================================" << endl;
    cout << "Ingrese el DNI: ";

    cargarCadena(dni, 9);
    if (!sonNumeros(dni) || strlen(dni)!=8) {
            cout << "El DNI tiene que ser numerico y contener 8 digitos."<<endl;
            return;
    }

    pos=_archivoC.buscarPorDNI(dni);

    if (pos ==-1){
        cout<<"Cliente no encontrado."<<endl;
        return;
    }

    if(!_archivoC.leer(obj, pos)){
        cout<<"No se pudo leer."<<endl;
        return;
    }

    if (obj.getEstado()==true){
        cout<<"El cliente "<<obj.getDNI()<<" ya se encuentra activo."<<endl;
        return;
    }

    mostrarCliente(obj);
    cout<<"¨Desea restaurar el cliente?"<<endl;
    cout<<"1. Si"<<endl;
    cout<<"0. No"<<endl;
    int opcion = leerEntero();

    if(opcion != 1){
        cout<<"Restauracion cancelada."<<endl;
        return;
    }

    obj.setEstado(true);

    if(_archivoC.modificar(obj, pos)){
        cout<<"Cliente restaurado."<<endl;
    } else {
        cout<<"No se pudo restaurar la pelicula."<<endl;
    }
}
