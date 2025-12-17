#include <iostream>
#include <cstring>
#include "Reportes.h"
#include "Venta.h"
#include "VentaArchivo.h"
#include "funcionesGlobales.h"
#include "VentaManager.h"

using namespace std;

void Reportes::RecaudacionFecha(){
    VentaArchivo aVenta("Ventas.dat");
    int cantRegistros = aVenta.contarRegistros();
    float recaudacion = 0;
    Fecha fecha;

    if(cantRegistros==0){
        cout<<"No hay registro de ventas"<<endl;
        return;
    }

    system("cls");
    cout << "Ingrese la fecha a calcular: " <<endl;
    fecha.cargar();

    for (int i = 0; i < cantRegistros; i++) {
        Venta reg;
        if (aVenta.leer(reg, i)) {
            if (reg.getEstado() && reg.getFechaProyeccion() == fecha) {
                recaudacion += reg.getImporteTotal();
            }
        }
    }

    if(recaudacion==0){
        cout<<"No hay ninguna venta para esa fecha"<<endl;
        return;
    }
    cout<<"========================================="<<endl;
    cout<<"Recaudacion total para ";
    fecha.mostrar();
    cout<<": $" << recaudacion<<endl;
    cout<<"========================================="<<endl;
}

void Reportes::RecaudacionAnual(){
    VentaArchivo aVenta("Ventas.dat");
    int cantRegistros = aVenta.contarRegistros();
    int anioBuscado;
    float recaudacionMes[12]={0};
    int cantVentaMes[12]={0};
    const char* mesesN[12]={"Enero","Febrero","Marzo","Abril","Mayo","Junio","Julio","Agosto","Septiembre","Octubre","Noviembre","Diciembre"};

    if(cantRegistros==0){
        cout<<"No hay registro de ventas"<<endl;
        return;
    }


    system("cls");
    cout << "Ingrese el anio a calcular: ";
    anioBuscado = leerEntero();
    if (anioBuscado<2000 || anioBuscado>2026){
        cout<<"A¤o invalido. Intente entre el 2000 y 2026."<<endl;
        return;
    }

    for(int i=0; i<cantRegistros; i++){
        Venta reg;

        if (aVenta.leer(reg, i)){
            if (reg.getEstado() && reg.getFechaProyeccion().getAnio() == anioBuscado){
                int mes = reg.getFechaProyeccion().getMes();
                if (mes >= 1 && mes <= 12) {
                    recaudacionMes[mes-1] += reg.getImporteTotal();
                    cantVentaMes[mes-1]++;
                }
            }
        }
    }

    float totalAnual = 0;
    int totalVentas = 0;

    cout<<"\n===================================="<<endl;
    cout<<"      Facturacion Anual - " << anioBuscado<<endl;
    cout<<"===================================="<<endl;
    cout<<"Mes             Ventas  Recaudacion "<<endl;
    cout<<"------------------------------------"<<endl;

    for(int j=0; j<12; j++){
        cout<<mesesN[j];

        if (strlen(mesesN[j]) < 8){//Hace dos tabulaciones si el mes mide menos de 8 caracteres
            cout << "\t\t";
        }
        else {cout << "\t";}

        cout << cantVentaMes[j] << "\t$" << recaudacionMes[j] << endl;

        totalAnual+=recaudacionMes[j];
        totalVentas+=cantVentaMes[j];
    }

    cout<<"-----------------------------------"<<endl;
    cout<<"TOTAL\t\t" << totalVentas << "\t$" << totalAnual<<endl;
    cout<<"==================================="<<endl;
}

void Reportes::DetallePeliculaAnual() {
    VentaArchivo arch("Ventas.dat");
    Venta reg;

    system("cls");
    cout << "Ingrese el ID de la pelicula: ";
    int idPelicula=leerEntero();

    Pelicula peli;
    PeliculaArchivo archiP;
    int posPeli = archiP.buscarPorID(idPelicula);
    if (posPeli==-1){
        cout<<"No se encontr¢ la pelicula."<<endl;
        return;
    }

    if (!archiP.leer(peli, posPeli)) {
        cout<<"Error al leer la pelicula."<<endl;
        return;
    }
    if (!peli.getEstado()) {
        cout<<"La pelicula est  inactiva."<<endl;
        return;
    }

    cout << "Ingrese a¤o: ";
    int anio=leerEntero();
    while (anio < 2000 || anio > 2026){
        cout<<"A¤o invalido. Reintente entre 2000 y 2026: ";
        anio=leerEntero();
    }

    int ventas = 0;
    int entradas = 0;
    float recaudacion = 0;

    int total = arch.contarRegistros();

    for(int i=0; i<total; i++){

        if (arch.leer(reg, i) && reg.getEstado() && reg.getIDPelicula() == idPelicula &&
            reg.getFechaProyeccion().getAnio() == anio) {

            ventas++;
            entradas += reg.getCantEntradas();
            recaudacion += reg.getImporteTotal();
        }
    }
    if (ventas == 0){
        cout << "No hubo ventas para esa pelicula en ese a¤o."<<endl;
        return;
    }

    cout<<"\n======================================"<<endl;
    cout<<"         Detalle de Pelicula          "<<endl;
    cout<<"======================================"<<endl;
    cout<<" Pelicula:\t\t" << peli.getNombrePelicula() << endl;
    cout<<" A¤o:\t\t\t" << anio << endl;
    cout<<" Ventas:\t\t" << ventas << endl;
    cout<<" Entradas vendidas:\t" << entradas << endl;
    cout<<" Recaudacion total:\t$" << recaudacion << endl;
    cout<<"======================================"<<endl;
}

void Reportes::DetalleSalaAnual() {
    VentaArchivo arch("Ventas.dat");
    Venta reg;

    system("cls");
    cout << "Ingrese el ID de la sala: ";
    int idSala = leerEntero();

    Sala sala;
    SalaArchivo archSala;
    int posSala = archSala.buscarPorID(idSala);
    if (posSala == -1) {
        cout << "No se encontr¢ la sala." << endl;
        return;
    }

    if (!archSala.leer(sala, posSala)) {
        cout << "Error al leer la sala." << endl;
        return;
    }

    if (!sala.getEstado()) {
        cout << "La sala est  inactiva." << endl;
        return;
    }

    cout << "Ingrese a¤o: ";
    int anio = leerEntero();
    while (anio < 2000 || anio > 2026) {
        cout << "A¤o invalido. Reintente entre 2000 y 2026: ";
        anio = leerEntero();
    }

    int ventas = 0;
    int entradas = 0;
    float recaudacion = 0;

    int total = arch.contarRegistros();
    for (int i = 0; i < total; i++) {
        if (arch.leer(reg, i) &&
            reg.getEstado() && reg.getIDSala() == idSala &&
            reg.getFechaProyeccion().getAnio() == anio) {

            ventas++;
            entradas += reg.getCantEntradas();
            recaudacion += reg.getImporteTotal();
        }
    }

    if (ventas==0){
        cout<<"No hubo ventas para esa Sala en ese a¤o."<<endl;
        return;
    }

    cout<<"\n======================================"<<endl;
    cout<<"            Detalle de Sala            "<<endl;
    cout<<"======================================"<<endl;
    cout<<"Sala: " << sala.getNombreSala() << endl;
    cout<<"A¤o: " << anio << endl;
    cout<<"Ventas: " << ventas << endl;
    cout<<"Entradas vendidas: " << entradas << endl;
    cout<<"Recaudacion total: $ " << recaudacion << endl;
    cout<<"======================================"<<endl;
}
