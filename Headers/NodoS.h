//
// Created by linkm on 19/08/2024.
//

#ifndef NODOS_H
#define NODOS_H

#include "SolicitudAmistad.h"

class NodoSolicitud {
public:
    SolicitudAmistad* solicitud;
    NodoSolicitud* siguiente;

    NodoSolicitud(SolicitudAmistad* solicitud)
        : solicitud(solicitud), siguiente(nullptr) {}

};

#endif //NODOS_H
