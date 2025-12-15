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

void Reportes::RecaudacionAnual(){
    VentaArchivo aVenta ("Ventas.dat");
    int cantRegistros=aVenta.contarRegistros();
    Venta reg;
    int anioBuscado;
    float meses[12]{0};
    const char* mesesN[12]{"Enero","Febrero","Marzo","Abril","Mayo","Junio","Julio","Agosto","Septiembre","Octubre","Noviembre","Diciembre"};
    Fecha fecha;

    system("cls");
    cout << "Ingrese el anio para calcular la recaudacion: ";
    cin >> anioBuscado;

    for(int i=0;i<cantRegistros;i++){
        reg=aVenta.LeerR(i);
        if(reg.getEstado() && reg.getFechaProyeccion().getAnio()==anioBuscado){
            int mes = reg.getFechaProyeccion().getMes();
            meses[mes-1]+=reg.getImporteTotal();
        }
    }

    float total=0;
    cout<< "\nFacturacion del anio: "<<anioBuscado<<endl;
    for(int j=0;j<12;j++){
        cout<<"|"<<mesesN[j]<<": $"<<meses[j];
        total+=meses[j];
        cout<<endl;
    }

    cout <<"\nTotal anual: $"<<total<<endl;

    return;
}
