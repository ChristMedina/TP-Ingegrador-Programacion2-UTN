#include <iostream>
#include <cstring> // Necesario para strlen()
#include "funcionesGlobales.h"

using namespace std;

void cargarCadena(char *palabra, int tam) {
    while (true) {
        cin.getline(palabra, tam);

        if (cin.fail()) {//Detecta si hay un error
            cin.clear(); // Limpia el error
            cin.ignore(1000, '\n');
            cout << "Excediste el limite de caracteres (" <<tam-1<< "). Intente de nuevo: ";
            continue;
        }

        if (strlen(palabra) == 0) {
            cout << "Error, no puede estar vac¡o. Intente de nuevo: ";
            continue;
        }

        break; // Todo correcto
    }
}

bool sonNumeros(const char *cadena) {

    //Si el caracter es menor que '0' o mayor que '9' entonces no es un n£mero
    for (int i = 0; cadena[i] != '\0'; i++) {
        if (cadena[i] < '0' || cadena[i] > '9') {
            return false; // retorna falso si no es numero
        }
    }
    return true; //retorna true si son solo numeros
}


bool sonLetras(const char *cadena) {

    for (int i = 0; cadena[i] != '\0'; i++) {

        char c = cadena[i];//obtiene el caracter actual

        bool mayuscula = (c >= 'A' && c <= 'Z');
        bool minuscula = (c >= 'a' && c <= 'z');
        bool espacio = (c == ' ');

        // Si no es mayuscula, min£scula y no  es un espacio, entonces es inv lido

        if (!mayuscula && !minuscula && !espacio) {
            return false; //retorna falso si no cumple con lo anterior
        }
    }
    return true; //retorna true si se cumple con todo
}

// Funcion para verificar que se haya ingresado solo un entero
int leerEntero(){
    int opcion;
    cin>>opcion;

    while(cin.fail()){//verifica si se ingreso un numero
        cout<<"Ingrese un n£mero valido. Intente de nuevo: ";
        cin.clear(); //limpia el error
        cin.ignore(1000, '\n');//ignora 1000 caracteres o hasta el salto de linea
        cin>>opcion;
    }

    cin.ignore(1000, '\n');
    return opcion;
}

bool validarEmail(const char* email) {
    //strchr verifica que el mail contenga un "@" y un "."
    //Busca dentro de una cadena un caracter especifico, si no lo encuentra devuelve null
    const char *arroba = strchr(email, '@');
    const char *punto = strrchr(email, '.');

    //verifica si los dos existen en la cadena
    if (arroba == nullptr || punto == nullptr) {return false;}

    if (punto < arroba) {return false;} //verifica que el punto este despues del arroba

    if (strlen(email) < 5) {return false;}//Verifica que se escriba un minimo de 5 caracteres

    return true;//Si esta todo bien retorna true

}
