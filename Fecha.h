#pragma once

class Fecha {
    private:
        int _dia;
        int _mes;
        int _anio;

    public:
        Fecha(int dia = 0, int mes = 0, int anio = 0);

        void cargar();
        void mostrar();

        bool esFechaValida();
        bool esBisiesto(int anio);

        bool operator==(const Fecha& otra);
        bool operator<(const Fecha& otra);
        bool operator>(const Fecha& otra);


        //setters
        void setDia(int dia);
        void setMes(int mes);
        void setAnio(int anio);

        //getters
        int getDia();
        int getMes();
        int getAnio();
};
