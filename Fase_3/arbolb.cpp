#include "arbolb.h"


void ArbolB::insertarNoLleno(nodoComentario* nodo, Comentario comentario) {
    int i = nodo->comentarios.size() - 1;

    if (nodo->esHoja) {
        while (i >= 0 && compararFechaHora(nodo->comentarios[i], comentario) > 0) {
            i--;
        }
        nodo->comentarios.insert(nodo->comentarios.begin() + i + 1, comentario);
    } else {
        while (i >= 0 && compararFechaHora(nodo->comentarios[i], comentario) > 0) {
            i--;
        }
        i++;
        if (nodo->hijos[i]->comentarios.size() == 2 * orden - 1) {
            dividirHijo(nodo, i);
            if (compararFechaHora(nodo->comentarios[i], comentario) < 0) {
                i++;
            }
        }
        insertarNoLleno(nodo->hijos[i], comentario);
    }
}

void ArbolB::dividirHijo(nodoComentario* nodoPadre, int indice) {
    nodoComentario* hijoLleno = nodoPadre->hijos[indice];
    nodoComentario* nuevoHijo = new nodoComentario(hijoLleno->esHoja);
    nuevoHijo->comentarios.assign(hijoLleno->comentarios.begin() + orden, hijoLleno->comentarios.end());
    hijoLleno->comentarios.resize(orden - 1);

    if (!hijoLleno->esHoja) {
        nuevoHijo->hijos.assign(hijoLleno->hijos.begin() + orden, hijoLleno->hijos.end());
        hijoLleno->hijos.resize(orden);
    }

    nodoPadre->hijos.insert(nodoPadre->hijos.begin() + indice + 1, nuevoHijo);
    nodoPadre->comentarios.insert(nodoPadre->comentarios.begin() + indice, hijoLleno->comentarios[orden - 1]);
}

int ArbolB::compararFechaHora(const Comentario& c1, const Comentario& c2) {
    std::string fechaHora1 = c1.fecha + c1.hora;
    std::string fechaHora2 = c2.fecha + c2.hora;
    if (fechaHora1 < fechaHora2) return -1;
    if (fechaHora1 > fechaHora2) return 1;
    return 0;
}

void ArbolB::insertar(Comentario comentario) {
    if (raiz == nullptr) {
        raiz = new nodoComentario(true);
        raiz->comentarios.push_back(comentario);
    } else {
        if (raiz->comentarios.size() == 2 * orden - 1) {
            nodoComentario* nuevaRaiz = new nodoComentario(false);
            nuevaRaiz->hijos.push_back(raiz);
            dividirHijo(nuevaRaiz, 0);
            insertarNoLleno(nuevaRaiz, comentario);
            raiz = nuevaRaiz;
        } else {
            insertarNoLleno(raiz, comentario);
        }
    }
}

std::string ArbolB::imprimir() {
    return imprimirInorden(raiz);
}

std::string ArbolB::imprimirInorden(nodoComentario* nodo) {
    std::string text = "";

    if (nodo != nullptr) {
        for (int i = 0; i < nodo->comentarios.size(); i++) {
            if (!nodo->esHoja) {
                text += imprimirInorden(nodo->hijos[i]);
            }
            text += "Autor: " + nodo->comentarios[i].autor + "\n";
            text += "Contenido: " + nodo->comentarios[i].contenido + "\n";
            text += "Fecha: " + nodo->comentarios[i].fecha + "\n";
            text += "Hora: " + nodo->comentarios[i].hora + "\n";
            text += "-----------------------------\n";
        }
        if (!nodo->esHoja) {
            text += imprimirInorden(nodo->hijos[nodo->comentarios.size()]);
        }
    }
    return text;
}


// Función auxiliar para contar los comentarios de un nodo
int ArbolB::contarComentariosRecursivo(nodoComentario* nodo) {
    if (nodo == nullptr) {
        return 0;
    }

    int count = nodo->comentarios.size();

    if (!nodo->esHoja) {
        for (nodoComentario* hijo : nodo->hijos) {
            count += contarComentariosRecursivo(hijo);
        }
    }

    return count;
}

int ArbolB::contarComentarios() {
    return contarComentariosRecursivo(raiz);
}

