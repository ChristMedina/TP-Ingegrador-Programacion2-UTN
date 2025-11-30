#pragma once

class Cliente{
    private:
        char _dni[9];
        char _nombre[30];
        char _apellido[30];
        char _email[30];
        char _telefono[12];
        bool _estado;

    public:
        Cliente ();

        //setters
        void setDNI(const char *dni);
        void setNombre(const char *nombre);
        void setApellido(const char *apellido);
        void setEmail(const char *mail);
        void setTelefono(const char *telefono);
        void setEstado(bool estado);

        //getters
        const char* getDNI();
        const char* getNombre();
        const char* getApellido();
        const char* getEmail();
        const char* getTelefono();
        bool getEstado();
};
