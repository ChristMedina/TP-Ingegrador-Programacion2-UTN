#pragma once

class Sala {
    private:
        int _idSala;
        int _tipoSala;
        int _capacidadSala;
        char _nombreSala[30];
        bool _estado;

    public:
        Sala();

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
