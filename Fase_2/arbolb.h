#ifndef ARBOLB_H
#define ARBOLB_H
#include "nodocomentario.h"
#include "Comentario.h"



class ArbolB
{

private:
    nodoComentario* raiz;
    int orden;

    void insertarNoLleno(nodoComentario* nodo, Comentario comentario);
    void dividirHijo(nodoComentario* nodoPadre, int indice);
    int compararFechaHora(const Comentario& c1, const Comentario& c2);
    std::string imprimirInorden(nodoComentario* nodo);
    int contarComentariosRecursivo(nodoComentario* nodo);

public:
    ArbolB(int _orden) {
        raiz = nullptr;
        orden = _orden;
    }

    void insertar(Comentario comentario);
    std::string imprimir();
    int contarComentarios();

};

#endif // ARBOLB_H
