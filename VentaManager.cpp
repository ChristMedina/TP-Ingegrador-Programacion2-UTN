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

    //DNI
    char dni[9];
    cout << "Ingrese su DNI: ";
    cargarCadena(dni, 9);

    if (!clienteActivo(dni)) {
        cout << "El cliente no existe o esta inactivo." << endl;
        cout << "¨Desea registrarlo ahora? (1-Si / 0-No): ";
        int op = leerEntero();

        if (op == 1) {
            ClienteManager cm;
            Cliente nuevo;

            if (cm.cargarCliente(nuevo)) {
                if (_archivoC.guardar(nuevo)) {
                    cout << "Cliente cargado exitosamente." << endl;

                } else {
                    cout << "Error al guardar el cliente." << endl;
                    return false;
                }
            } else {
                cout << "Error al cargar los datos del cliente." << endl;
                return false;
            }
        } else {
            cout << "No se puede continuar sin cliente"<<endl;
            return false;
        }
    }
    obj.setDNIComprador(dni);


    //ID Venta automatica
    int id = _archivoV.asignarID();
    obj.setIDVenta(id);
    cout << "ID de venta asignado: " << id << endl;


    //Pelicula
    cout << "Ingrese el ID de la pelicula: ";
    int idPeli = leerEntero();

    if (!peliculaActiva(idPeli)) {
        cout << "La pelicula no existe o esta inactiva." << endl;
        return false;
    }
    obj.setIDPelicula(idPeli);

    cout << "Seleccione el tipo de sala:" <<endl;
    cout << " 1) Estandar $8000" << endl;
    cout << " 2) Premium $12000" << endl;
    cout << " 3) Comfort Plus $16000" << endl;
    cout << "Opci¢n: ";

    int tipoSala = leerEntero();
    while (tipoSala < 1 || tipoSala > 3) {
        cout << "Opci¢n inv lida. Intente nuevamente: ";
        tipoSala = leerEntero();
    }


    //Sala
    Sala sala;
    bool encontrada = false;
    int totalSalas = _archivoS.contarRegistros();

    for (int i = 0; i < totalSalas; i++) {
        if (_archivoS.leer(sala, i)) {
            if (sala.getTipoSala() == tipoSala && sala.getEstado()){

                obj.setIDSala(sala.getIDSala());// settea el id aca
                cout << "Sala asignada: "
                     << sala.getNombreSala()<<" (ID "<<sala.getIDSala() << ")" << endl;
                encontrada = true;
                break;
            }
        }
    }

    if (!encontrada) {
        cout << "No se encontro ninguna sala activa de este tipo." << endl;
        return false;
    }

    //Fecha
    Fecha fecha;
    cout << "Ingrese la fecha de proyeccion: " << endl;
    fecha.cargar();

    int pos = _archivoP.buscarPorID(idPeli);
    if (pos == -1) {
        cout << "No se encontro la pelicula." << endl;
        return false;
    }

    Pelicula peli;
    if (!_archivoP.leer(peli, pos)) {
        cout << "Error al leer pelicula." << endl;
        return false;
    }

    if (fecha < peli.getFechaEstreno()) {
        cout << "La proyeccion no puede ser antes del estreno." << endl;
        return false;
    }
    obj.setFechaProyeccion(fecha);
    cin.ignore(1000,'\n');


    //Cantidad de entradas
    int cap = capacidadSala(sala.getIDSala());
    int vendidas = entradasVendidas(idPeli, sala.getIDSala(), fecha);
    int disponibles = cap - vendidas;

    if (disponibles <= 0) {
        cout << "No hay asientos disponibles para esta funci¢n." << endl;
        return false;
    }

    cout << "Entradas disponibles: " << disponibles << endl;
    cout << "Ingrese la cantidad a comprar: ";
    int cant = leerEntero();

    while (cant <= 0 || cant > disponibles) {
        cout << "Cantidad inv lida. Intente nuevamente: ";
        cant = leerEntero();
    }
    obj.setCantEntradas(cant);


    //Precio
    float precioUnitario = precioPorTipoSala(sala.getTipoSala());
    if (precioUnitario <= 0) {
        cout << "Error: tipo de sala inv lido." << endl;
        return false;
    }
    float total = precioUnitario * cant;
    cout << "Total: $" << total << endl;
    obj.setImporteTotal(total);

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
    cout << "ID Venta: " << obj.getIDVenta() << endl;

    Pelicula peli;
    int posPeli=_archivoP.buscarPorID(obj.getIDPelicula());

    if (_archivoP.leer(peli, posPeli)) {
        cout << "Pelicula: " << peli.getNombrePelicula() << endl;
    } else {
        cout << "Pelicula: (no encontrada)" << endl;
    }

    Sala sala;
    int posSala = _archivoS.buscarPorID(obj.getIDSala());

    if (_archivoS.leer(sala,posSala)) {
        cout << "Sala: " << sala.getNombreSala() << " (" << sala.getTipoSala() << ")" << endl;
    } else {
        cout << "Sala: (no encontrada)" << endl;
    }

    cout << "Fecha de proyeccion: ";
    obj.getFechaProyeccion().mostrar();
    cout << endl;

    cout << "DNI comprador: " << obj.getDNIComprador() << endl;
    cout << "Entradas: " << obj.getCantEntradas() << endl;
    cout << "Importe total: $" << obj.getImporteTotal() << endl;
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
        cout << "1. Activas" << endl;
        cout << "2. Anuladas" << endl;
        cout << "3. Mostrar todas" << endl;
        cout << "0. Volver" << endl;
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

bool VentaManager::clienteActivo(const char* dni) {
    int pos = _archivoC.buscarPorDNI(dni);
    if (pos == -1) return false;

    Cliente cli;
    if (!_archivoC.leer(cli, pos)) return false;

    return cli.getEstado();
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
