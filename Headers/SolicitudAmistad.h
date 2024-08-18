//
// Created by linkm on 19/08/2024.
//

#ifndef SOLICITUDAMISTAS_H
#define SOLICITUDAMISTAS_H
#include "Usuario.h"

class SolicitudAmistad {
public:
    Usuario* emisor;
    Usuario* receptor;

    SolicitudAmistad(Usuario* emisor, Usuario* receptor)
        : emisor(emisor), receptor(receptor) {}
};


#endif //SOLICITUDAMISTAS_H
