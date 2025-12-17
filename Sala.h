#pragma once

class Sala {
    private:
        int _idSala;
        char _nombreSala[30];
        int _tipoSala;
        int _capacidadSala;
        bool _estado;

    public:
        Sala();
        Sala(int id, const char* nombre,int tipo, int capacidad, bool estado);

        //setters
        void setIDSala(int idSala);
        void setTipoSala(int tipoSala);
        void setCapacidadSala(int capacidadSala);
        void setNombreSala(const char *nombreSala);
        void setEstado(bool estado);

        //getters
        int getIDSala();
        int getTipoSala();
        int getCapacidadSala();
        const char* getNombreSala();
        bool getEstado();
};

