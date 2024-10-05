#ifndef NODOABB_H
#define NODOABB_H


#include <string>
#include "listadoble.h"

class NodoABB {

public:

    std::string fecha;
    ListaDoble publicaciones;
    NodoABB* izquierdo;
    NodoABB* derecho;

    NodoABB(std::string f) : fecha(f), izquierdo(nullptr), derecho(nullptr) {}
};


#endif // NODOABB_H
