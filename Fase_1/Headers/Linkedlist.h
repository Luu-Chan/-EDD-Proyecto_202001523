//
// Created by linkm on 9/08/2024.
//

#ifndef LINKEDLIST_H
#define LINKEDLIST_H
#include "Usuario.h"

class Linkedlist {
private:
    Usuario * head;

public:
    //Funciones de la linkedlist
    Linkedlist();
    ~Linkedlist();
    void agregar(Usuario* nuevoUsuario);
    void eliminar(const string& correoE);
    void imprimirLista() const;
    Usuario* buscarU(const string& correoE) const;
    Usuario* validarD(const string& correoE, const string& pass) const;
    int obtenerSize() const;
    void registrarU(string nombres, string apellidos, string fecha, string mail, string pass);
    void inicioSesion(const string& correoE, const string& pass) const;
    void perfil(const string& correoE) const;
    void generarDOT() const;
};

#endif //LINKEDLIST_H
