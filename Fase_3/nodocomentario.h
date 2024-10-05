#ifndef NODOCOMENTARIO_H
#define NODOCOMENTARIO_H
#include "vector"
#include "Comentario.h"

class nodoComentario
{
public:
    bool esHoja;

    nodoComentario(bool hoja) {esHoja = hoja; }
    std::vector<Comentario> comentarios;
    std::vector<nodoComentario*> hijos;
};

#endif // NODOCOMENTARIO_H
