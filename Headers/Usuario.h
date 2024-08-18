//
// Created by linkm on 11/08/2024.
//

#ifndef USUARIOS_H
#define USUARIOS_H

#include <string>
#include "ListaSolicitud.h"

using namespace std;

struct Usuario {
    int id;
    string nombre;
    string apellido;
    string fechaN;
    string correoE;
    string pass;
    Usuario* siguiente;
    ListaSolicitud solicitudesRecibidas;
    ListaSolicitud solicitudesEnviadas;

    // Constructor para inicializar
    Usuario(int id, string name, string apelli, string fechaNa, string mail, string pass);



};


#endif //USUARIOS_H
