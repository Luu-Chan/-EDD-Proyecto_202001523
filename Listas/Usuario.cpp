//
// Created by linkm on 9/08/2024.
//

#include "../Headers/Usuario.h"
#include "../Headers/ListaSolicitud.h"

#include <iostream>

using namespace std;

Usuario::Usuario(int id, string name, string apelli, string fechaNa, string mail, string pass, ListaSolicitud )
    : id(id), nombre(name), apellido(apelli), fechaN(fechaNa), correoE(mail), pass(pass), siguiente(nullptr) {}


bool enviarSolicitud(Usuario* receptor) {
    // Verificar si ya existe una solicitud pendiente o enviada
    if (solicitudesEnviadas.existeSolicitud(this, receptor) ||
        receptor->solicitudesRecibidas.existeSolicitud(this, receptor)) {
        std::cout << "Ya existe una solicitud pendiente o enviada a " << receptor->nombre << ".\n";
        return false;
        }

    // Crear nueva solicitud de amistad
    SolicitudAmistad* nuevaSolicitud = new SolicitudAmistad(this, receptor);
    solicitudesEnviadas.agregarSolicitud(nuevaSolicitud);
    receptor->solicitudesRecibidas.agregarSolicitud(nuevaSolicitud);
    std::cout << "Solicitud de amistad enviada a " << receptor->nombre << ".\n";
    return true;
}