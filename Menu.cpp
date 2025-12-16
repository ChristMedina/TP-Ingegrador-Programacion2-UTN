#include <iostream>
#include "Menu.h"
#include "funcionesGlobales.h"

using namespace std;

void Menu::ejecutar(){
    int opcion;

    while(true){
        system("cls");
        menuPrincipal();//Muestra el menu principal
        opcion = leerEntero();

        switch(opcion){
            case 1:
                menuClientes();
                break;
            case 2:
                menuPeliculas();
                break;
            case 3:
                menuSalas();
                break;
            case 4:
                menuVentas();
                break;
            case 5:
                menuReportes();
                break;
            case 0:
                system("cls");
                cout<<"Saliendo del programa..."<<endl;
                return;
            default:
                cout<<"Opci¢n incorrecta."<<endl;
                break;
        }
        //system("pause");
    }
}

void Menu::menuPrincipal(){
    cout << "================================" << endl;
    cout << "          Menu Principal        " << endl;
    cout << "================================" << endl;
    cout << " 1. Clientes" << endl;
    cout << " 2. Peliculas" << endl;
    cout << " 3. Salas" << endl;
    cout << " 4. Ventas" << endl;
    cout << " 5. Reportes" <<endl;
    cout << " 0. Salir" << endl;
    cout << "================================" << endl;
    cout << "Opcion: ";
}

void Menu::menuClientes(){
    int opcion;

    while(true){
        system("cls");
        cout << "================================" << endl;
        cout << "         Menu Clientes          " << endl;
        cout << "================================" << endl;
        cout << " 1. Cargar" << endl;
        cout << " 2. Buscar" << endl;
        cout << " 3. Modificar" << endl;
        cout << " 4. Eliminar" << endl;
        cout << " 5. Restaurar" << endl;
        cout << " 6. Listar" << endl;
        cout << " 0. Volver al Menu Principal" << endl;
        cout << "================================" << endl;
        cout << "Opcion: ";

        opcion= leerEntero();

        switch(opcion){
            case 1:
                _managerCliente.cargar();
                break;
            case 2:
                _managerCliente.buscar();
                break;
            case 3:
                _managerCliente.modificar();
                break;
            case 4:
                _managerCliente.eliminar();
                break;
            case 5:
                _managerCliente.restaurar();
                break;
            case 6:
                _managerCliente.mostrarTodos();
                break;
            case 0:
                return;
            default:
                cout<<"Opci¢n incorrecta."<<endl;
                break;
        }
        system("pause");
    }
}

void Menu::menuPeliculas(){
    int opcion;

    while(true){
        system("cls");
        cout << "================================" << endl;
        cout << "         Menu Peliculas         " << endl;
        cout << "================================" << endl;
        cout << " 1. Cargar" << endl;
        cout << " 2. Buscar" << endl;
        cout << " 3. Modificar" << endl;
        cout << " 4. Eliminar" << endl;
        cout << " 5. Restaurar" << endl;
        cout << " 6. Listar" << endl;
        cout << " 0. Volver al Menu Principal" << endl;
        cout << "================================" << endl;
        cout << "Opcion: ";

        opcion = leerEntero();

        switch(opcion){
            case 1:
                _managerPelicula.cargar();
                break;
            case 2:
                _managerPelicula.buscar();
                break;
            case 3:
                _managerPelicula.modificar();
                break;
            case 4:
                _managerPelicula.eliminar();
                break;
            case 5:
                _managerPelicula.restaurar();
                break;
            case 6:
                _managerPelicula.mostrarTodas();
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

void Menu::menuSalas(){
    int opcion;

    while(true){
        system("cls");
        cout << "================================" << endl;
        cout << "          Menu Salas            " << endl;
        cout << "================================" << endl;
        cout << " 1. Cargar" << endl;
        cout << " 2. Modificar" << endl;
        cout << " 3. Eliminar" << endl;
        cout << " 4. Restaurar" << endl;
        cout << " 5. Listar" << endl;
        cout << " 0. Volver al Menu Principal" << endl;
        cout << "================================" << endl;
        cout << "Opcion: ";

        opcion = leerEntero();

        switch(opcion){
            case 1:
                _managerSala.cargar();
                break;
            case 2:
                _managerSala.modificar();
                break;
            case 3:
                _managerSala.eliminar();
                break;
            case 4:
                _managerSala.restaurar();
                break;
            case 5:
                _managerSala.mostrarTodas();
                break;
            case 0:
                return;
            default:
                cout<<"Opci¢n incorrecta."<<endl;
                break;
        }
        system("pause");
    }
}

void Menu::menuVentas() {
    int opcion;

    while (true) {
        system("cls");
        cout << "================================" << endl;
        cout << "          Menu Ventas           " << endl;
        cout << "================================" << endl;
        cout << " 1. Cargar" << endl;
        cout << " 2. Listar" << endl;
        cout << " 3. Anular" << endl;
        cout << " 0. Volver al Menu Principal" << endl;
        cout << "================================" << endl;
        cout << "Opcion: ";

        opcion = leerEntero();

        switch (opcion) {
            case 1:
                _managerVenta.cargar();
                break;
            case 2:
                _managerVenta.mostrarTodas();
                break;
            case 3:
                _managerVenta.anular();
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

void Menu::menuReportes() {
    int opcion;

    while (true) {
        system("cls");
        cout << "================================" << endl;
        cout << "         Menu Reportes          " << endl;
        cout << "================================" << endl;
        cout << " 1. Reporte de ventas por fecha" << endl;
        cout << " 2. Reporte de ventas anual" << endl;
        cout << " 0. Volver al Menu Principal" << endl;
        cout << "================================" << endl;
        cout << "Opcion: ";

        opcion = leerEntero();

        switch (opcion) {
            case 1:
                _reportes.RecaudacionFecha();
                break;
            case 2:
                _reportes.RecaudacionAnual();
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
