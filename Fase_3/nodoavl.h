#ifndef NODOAVL_H
#define NODOAVL_H
#include "user.h"

class NodoAVL
{
public:

    NodoAVL(user* usuario);

    user* usuario;
    NodoAVL* left;
    NodoAVL* right;
    int height;


};

#endif // NODOAVL_H
