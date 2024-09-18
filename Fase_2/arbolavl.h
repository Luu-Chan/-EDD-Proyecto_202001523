#ifndef ARBOLAVL_H
#define ARBOLAVL_H
#include "nodoavl.h"

class arbolAVL
{
private:

    NodoAVL* raiz;
    int height(NodoAVL* node);
    NodoAVL* insert(NodoAVL* node, user* u);
    int getBalance(NodoAVL* node);
    NodoAVL* rotateRight(NodoAVL* y);
    NodoAVL* rotateLeft(NodoAVL* x);


public:
    arbolAVL() : raiz(nullptr) {}
    void insertU(user* usuario);
    bool search(const std::string& correoE);
    NodoAVL* searchNode(NodoAVL* node, const std::string& correoE);
    bool credenciales(const std::string& correoE, const std::string& contrasena);


};

#endif // ARBOLAVL_H
