//
// Created by linkm on 17/08/2024.
//
#include "../Headers/ListaSolicitud.h"
#include "../Headers/SolicitudAmistad.h"
#include "../Headers/NodoS.h"


ListaSolicitud::ListaSolicitud(): cabeza(nullptr) {}

// Metodo para agregar una solicitud al final de la lista
void ListaSolicitud::agregarSolicitud( SolicitudAmistad* solicitud){
    NodoSolicitud* nuevoNodo = new NodoSolicitud(solicitud);
    if (!cabeza) {
        cabeza = nuevoNodo;
    } else {
        NodoSolicitud* actual = cabeza;
        while (actual->siguiente) {
            actual = actual->siguiente;
        }
        actual->siguiente = nuevoNodo;
    }
}

// Metodo para eliminar una solicitud de la lista
void ListaSolicitud::eliminarSolicitud(SolicitudAmistad* solicitud) {
    NodoSolicitud* actual = cabeza;
    NodoSolicitud* anterior = nullptr;

    while (actual && actual->solicitud != solicitud) {
        anterior = actual;
        actual = actual->siguiente;
    }

    if (actual) {
        if (anterior) {
            anterior->siguiente = actual->siguiente;
        } else {
            cabeza = actual->siguiente;
        }
        delete actual;
    }
}

// Metodo para verificar si ya existe una solicitud en la lista
bool ListaSolicitud::existeSolicitud(Usuario* emisor, Usuario* receptor) const {
    NodoSolicitud* actual = cabeza;
    while (actual) {
        if ((actual->solicitud->emisor == emisor && actual->solicitud->receptor == receptor) ||
            (actual->solicitud->emisor == receptor && actual->solicitud->receptor == emisor)) {
            return true;
            }
        actual = actual->siguiente;
    }
    return false;
}
