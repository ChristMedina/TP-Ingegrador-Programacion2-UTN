#include <iostream>
#include <cstring>
#include <cstdlib>
#include "Reportes.h"
#include "Venta.h"
#include "VentaArchivo.h"

using namespace std;

void Reportes::RecaudacionFecha(){
    VentaArchivo aVenta ("Ventas.dat");
    int cantRegistros= aVenta.contarRegistros();
    Venta reg;

    float Recaudacion=0;

    Fecha fecha;

    system("cls");
    cout<<"Ingrese la fecha a calcular la recaudacion: "<<endl;
    fecha.cargar();

    for(int i=0;i<cantRegistros;i++){
        reg=aVenta.LeerR(i);
        if(reg.getEstado() && reg.getFechaProyeccion()==fecha){
            Recaudacion+=reg.getImporteTotal();
        }
    }

    cout<<"Recaudacion total para la fecha : ";
    fecha.mostrar();
    cout<<": $"<<Recaudacion<<endl;

    return;
}


