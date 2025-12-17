#include <iostream>
#include <cstring>
#include "VentaManager.h"
#include "ClienteManager.h"
#include "funcionesGlobales.h"

using namespace std;

void VentaManager::cargar() {
    system("cls");
    Venta nuevaVenta;

    if (cargarVenta(nuevaVenta)) {
        if (_archivoV.guardar(nuevaVenta)) {
            cout << "Venta registrada exitosamente." << endl;
        } else {
            cout << "Error al guardar la venta en el archivo." << endl;
        }
    }
}

bool VentaManager::cargarVenta(Venta &obj) {
    system("cls");

    // ID Venta automatica
    int id = _archivoV.asignarID();
    obj.setIDVenta(id);
    cout << "ID de venta asignado: " << id << endl;

    cout << "\nPeliculas disponibles:"<<endl;
    cout << "=============================="<<endl;
    for (int i=0; i<_archivoP.contarRegistros(); i++){
        Pelicula p;
        if (_archivoP.leer(p,i) && p.getEstado()){
            cout << p.getIDPelicula() << ") " << p.getNombrePelicula() << "\n";
        }
    }
    cout << "=============================="<<endl;


    // Pelicula
    cout << "Ingrese el ID de la pelicula: ";
     int idPeli = leerEntero();

    if (!peliculaActiva(idPeli)) {
        cout << "La pelicula no existe o esta inactiva." << endl;
        return false;
    }
    obj.setIDPelicula(idPeli);

    Pelicula peli;
    int posPeli = _archivoP.buscarPorID(idPeli);
    if (posPeli == -1 || !_archivoP.leer(peli, posPeli)) {
        cout << "Error al leer la pelicula." << endl;
        return false;
    }
    cout << "Pelicula: " << peli.getNombrePelicula();
    cout << " (Estreno: ";
    peli.getFechaEstreno().mostrar();
    cout<<")"<<endl<<endl;


    // Fecha de proyeccion
    Fecha fecha;
    cout << "Ingrese la fecha de proyeccion: " << endl;
    fecha.cargar();

    if (fecha < peli.getFechaEstreno()) {
        cout << "La proyeccion no puede ser antes del estreno." << endl;
        return false;
    }
    obj.setFechaProyeccion(fecha);


    // Tipo de sala
    cout << "\nSeleccione el tipo de sala:" << endl;
    cout << " 1) Estandar $8000" << endl;
    cout << " 2) Premium $12000" << endl;
    cout << " 3) Comfort Plus $16000" << endl;
    cout << "Opcion: ";

    int tipoSala = leerEntero();
    while (tipoSala < 1 || tipoSala > 3) {
        cout << "Opcion invalida. Intente nuevamente: ";
        tipoSala = leerEntero();
    }

    // Buscar sala activa
    Sala salaElegida;
    bool encontrada = false;
    int totalSalas = _archivoS.contarRegistros();

    for (int i=0; i<totalSalas; i++) {

        Sala sala;
        if (_archivoS.leer(sala, i)) {
            if (sala.getTipoSala() == tipoSala && sala.getEstado()){

                int cap=capacidadSala(sala.getIDSala());
                int vendidas=entradasVendidas(idPeli, sala.getIDSala(), fecha);
                int disponibles = cap-vendidas;

                if(disponibles>0){
                    salaElegida=sala;
                    obj.setIDSala(sala.getIDSala());//seteo el ID de la sala aca
                    cout<<"Sala asignada: "<<sala.getNombreSala()<<endl;
                    encontrada=true;
                    break;
                }
            }
        }
    }

    if (!encontrada) {
        cout << "No se encontro ninguna sala activa de este tipo." << endl;
        return false;
    }


    // Capacidad y cantidad de entradas
    int cap = capacidadSala(salaElegida.getIDSala());
    int vendidas = entradasVendidas(idPeli, salaElegida.getIDSala(), fecha);
    int disponibles = cap - vendidas;

    if (disponibles <= 0) {
        cout << "No hay asientos disponibles para esta funcion." << endl;
        return false;
    }

    cout<<"\nEntradas disponibles: "<<disponibles<<endl;
    cout<<"Ingrese la cantidad a comprar: ";
    int cant = leerEntero();

    while (cant <= 0 || cant > disponibles) {
        cout << "Cantidad invalida. Intente nuevamente: ";
        cant = leerEntero();
    }
    obj.setCantEntradas(cant);

    // Precio
    float precioUnitario = precioPorTipoSala(salaElegida.getTipoSala());
    if (precioUnitario <= 0) {
        cout << "Error: tipo de sala invalido." << endl;
        return false;
    }

    float total = precioUnitario * cant;
    obj.setImporteTotal(total);

    // Resumen
    cout<<endl;
    cout<<"================================" << endl;
    cout<<"         RESUMEN COMPRA         " << endl;
    cout<<"================================" << endl;
    cout<<" Pelicula:\t" << peli.getNombrePelicula()  << endl;
    cout<<" Sala:\t\t" << salaElegida.getNombreSala()<<endl;
    cout<<" Fecha:\t\t"; fecha.mostrar();
    cout<<endl;
    cout<<" Entradas:\t" << cant << endl;
    cout<<" Total:\t\t$" << total << endl;
    cout<<"================================" << endl;
    cout<<"¨Confirmar compra? (1-Si / 0-No): ";

    int ok = leerEntero();
    if (ok != 1) {
        cout << "Compra cancelada." << endl;
        return false;
    }

    // Cliente
    char dni[9];
    cout<<"\nPara finalizar necesitaremos sus datos."<<endl;
    cout<<"Ingrese su DNI para buscarlo en el sistema."<<endl;
    while (true) {
        cout<<"DNI: ";
        cargarCadena(dni, 9);

        if (!sonNumeros(dni) || strlen(dni) != 8) {
            cout << "El DNI debe ser numerico y tener 8 digitos. Intente de nuevo.\n";
            continue;
        }
        break;
    }

    int estadoCli = estadoDeCliente(dni);
    if (estadoCli==0) {
        cout<<"El cliente existe pero esta inactivo. Requiere reactivacion."<<endl;
        cout<<"Venta cancelada."<<endl;
        return false;
    }

    if (estadoCli == -1) {
        cout << "El cliente no existe."<<endl;
        cout << "¨Desea registrarlo ahora? (1-Si / 0-No): ";
        int op = leerEntero();

        if (op == 1) {
            ClienteManager cm;
            if(!cm.cargarCliente(dni)){
                cout<<"No se pudo registrar el cliente. Venta cancelada."<<endl;
                return false;
            } else {
                cout<<"Cliente cargado exitosamente"<<endl;
            }
        }else{
            cout<<"No se puede continuar sin cliente."<<endl;
            return false;
        }
    }
    obj.setDNIComprador(dni);

    // Estado
    obj.setEstado(true);
    return true;
}

void VentaManager::anular() {
    system("cls");
    cout << "================================" << endl;
    cout << "         Anular Venta           " << endl;
    cout << "================================" << endl;

    int id;
    cout << "Ingrese el ID: ";
    id = leerEntero();

    int pos = _archivoV.buscarPorID(id);

    if (pos == -1) {
        cout << "No se encontr¢ la venta." << endl;
        return;
    }

    Venta obj;
    if (!_archivoV.leer(obj, pos)) {
        cout << "Error al leer el registro." << endl;
        return;
    }

    if (!obj.getEstado()) {
        cout << "La venta ya se encuentra anulada." << endl;
        return;
    }

    mostrarVenta(obj);
    cout<<"¨Desea continuar con la anulacion?"<<endl;
    cout<<"1. Si"<<endl;
    cout<<"0. No"<<endl;
    int opcion = leerEntero();

    if(opcion != 1){
        cout<<"Anulacion cancelada."<<endl;
        return;
    }
    obj.setEstado(false);

    if (_archivoV.modificar(obj, pos)) {
        cout << "Venta anulada correctamente." << endl;
    } else {
        cout << "Error al anular la venta." << endl;
    }
}

void VentaManager::mostrarVenta(Venta &obj) {
    cout << "--------------------------------" << endl;
    cout << " ID Venta:\t" << obj.getIDVenta() << endl;

    Pelicula peli;
    int posPeli=_archivoP.buscarPorID(obj.getIDPelicula());

    if (_archivoP.leer(peli, posPeli)) {
        cout << " Pelicula:\t" << peli.getNombrePelicula() << endl;
    } else {
        cout << " Pelicula: (no encontrada)" << endl;
    }

    Sala sala;
    int posSala = _archivoS.buscarPorID(obj.getIDSala());

    if (_archivoS.leer(sala,posSala)) {
        cout << " Sala:\t\t" << sala.getNombreSala() << endl;
    } else {
        cout << " Sala: (no encontrada)" << endl;
    }

    cout << " Fecha:\t\t";
    obj.getFechaProyeccion().mostrar();
    cout << endl;

    cout << " DNI:\t\t" << obj.getDNIComprador() << endl;
    cout << " Entradas:\t" << obj.getCantEntradas() << endl;
    cout << " Total:\t\t$" << obj.getImporteTotal() << endl;
    cout << "--------------------------------" << endl;
}

void VentaManager::mostrarTodas() {
    Venta obj;
    int total = _archivoV.contarRegistros();

    if (total == 0) {
        cout << "No hay ventas registradas." << endl;
        return;
    }

    int opcion;
    while (true) {
        system("cls");
        cout << "================================" << endl;
        cout << "        Listado de Ventas       " << endl;
        cout << "================================" << endl;
        cout << " 1. Activas" << endl;
        cout << " 2. Anuladas" << endl;
        cout << " 3. Mostrar todas" << endl;
        cout << " 0. Volver" << endl;
        cout << "================================" << endl;
        cout << "Opcion: ";
        opcion = leerEntero();

        if (opcion == 0) return;
        if (opcion < 0 || opcion > 3) {
            cout << "Opcion incorrecta." << endl;
            continue;
        }

        system("cls");
        int mostradas = 0;

        for (int i = 0; i < total; i++) {
            if (_archivoV.leer(obj, i)) {
                switch (opcion) {
                    case 1:
                        if (obj.getEstado()) {
                            mostrarVenta(obj);
                            mostradas++;
                        }
                        break;

                    case 2:
                        if (!obj.getEstado()) {
                            mostrarVenta(obj);
                            mostradas++;
                        }
                        break;

                    case 3:
                        mostrarVenta(obj);
                        mostradas++;
                        break;
                }
            }
        }

        if (mostradas == 0) {
            if (opcion == 1) cout << "No hay ventas activas." <<endl;
            if (opcion == 2) cout << "No hay ventas anuladas." << endl;
            if (opcion == 3) cout << "No hay ventas registradas." << endl;
        }

        system("pause");
    }
}

bool VentaManager::peliculaActiva(int idPelicula) {
    int pos = _archivoP.buscarPorID(idPelicula);
    if (pos == -1) return false;

    Pelicula peli;
    if (!_archivoP.leer(peli, pos)) return false;

    return peli.getEstado();
}

bool VentaManager::salaActiva(int idSala) {
    int pos = _archivoS.buscarPorID(idSala);
    if (pos == -1) return false;

    Sala sala;
    if (!_archivoS.leer(sala, pos)) return false;

    return sala.getEstado();
}

int VentaManager::estadoDeCliente(const char* dni) {
    int pos = _archivoC.buscarPorDNI(dni);
    if (pos == -1) return -1;

    Cliente cli;
    if (!_archivoC.leer(cli, pos)) return -2;

    if(cli.getEstado()){
        return 1;
    } else {return 0;}
}

int VentaManager::capacidadSala(int idSala) {
    int pos = _archivoS.buscarPorID(idSala);
    if (pos == -1) return 0;

    Sala sala;
    if (!_archivoS.leer(sala, pos)) return 0;

    return sala.getCapacidadSala();
}

int VentaManager::entradasVendidas(int idPelicula, int idSala, const Fecha fecha) {
    int total = _archivoV.contarRegistros();
    Venta obj;
    int cant = 0;

    for (int i = 0; i < total; i++) {
        if (_archivoV.leer(obj, i) && obj.getEstado()) {
            if (obj.getIDPelicula() == idPelicula && obj.getIDSala() == idSala && obj.getFechaProyeccion()== fecha) {
                cant += obj.getCantEntradas();
            }
        }
    }
    return cant;
}

float VentaManager::precioPorTipoSala(int tipoSala) {
    switch(tipoSala){
        case 1: return 8000; // Est ndar
        case 2: return 12000; // Premium
        case 3: return 16000; // Comfort Plus
        default: return 0;
    }
}
