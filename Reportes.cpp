#include <iostream>
#include <cstring>
#include "Reportes.h"
#include "Venta.h"
#include "VentaArchivo.h"
#include "funcionesGlobales.h"

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
    cout<<"      FACTURACION ANUAL - " << anioBuscado<<endl;
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
