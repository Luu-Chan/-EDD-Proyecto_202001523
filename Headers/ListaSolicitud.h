//
// Created by linkm on 17/08/2024.
//

#ifndef LISTASOLICITUD_H
#define LISTASOLICITUD_H
#include "NodoS.h"


class ListaSolicitud {

public:
    NodoSolicitud* cabeza;
    ListaSolicitud();
    void agregarSolicitud( SolicitudAmistad* solicitud);
    void eliminarSolicitud(SolicitudAmistad* solicitud);
    bool existeSolicitud(Usuario* emisor, Usuario* receptor) const;
};

#endif //LISTASOLICITUD_H
