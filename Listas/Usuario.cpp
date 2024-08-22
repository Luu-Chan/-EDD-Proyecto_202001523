//
// Created by linkm on 9/08/2024.
//

#include "../Headers/Usuario.h"
#include "../Headers/ListaSolicitud.h"

#include <iostream>

using namespace std;

Usuario::Usuario(int id, string name, string apelli, string fechaNa, string mail, string pass )
    : id(id), nombre(name), apellido(apelli), fechaN(fechaNa), correoE(mail), pass(pass), siguiente(nullptr) {}


bool Usuario::enviarSolicitud(Usuario* emisor ,Usuario* receptor) {
    // Verificar si ya existe una solicitud pendiente o enviada
    if (solicitudesEnviadas.existeSolicitud(emisor, receptor) ||
        receptor->solicitudesRecibidas.existeSolicitud(emisor, receptor)) {
        std::cout << "Ya existe una solicitud pendiente o enviada a " << receptor->nombre << ".\n";
        return false;
        }

    // Crear nueva solicitud de amistad
    SolicitudAmistad* nuevaSolicitud = new SolicitudAmistad(emisor, receptor);
    solicitudesEnviadas.agregarSolicitud(nuevaSolicitud);
    receptor->solicitudesRecibidas.agregarSolicitud(nuevaSolicitud);
    std::cout << "Solicitud de amistad enviada a " << receptor->nombre << ".\n";
    return true;
}

// Metodo para mostrar la solicitud de amistad más reciente
void Usuario::mostrarSolicitudMasReciente() const {
    cout << "Cargando " << endl;
    if (!solicitudesRecibidas.cabeza) {
        std::cout << "No hay solicitudes de amistad.\n";
        return;
    }>

    // Obtener la solicitud más reciente (al inicio de la lista)
    NodoSolicitud* solicitudMasReciente = solicitudesRecibidas.cabeza;

    // Imprimir el nombre del usuario que envió la solicitud
    std::cout << "Solicitud de amistad más reciente de: " << solicitudMasReciente->solicitud->emisor->nombre << ".\n";
}

// Metodo para aceptar la solicitud de amistad más reciente
void Usuario::aceptarSolicitud() {
    if (!solicitudesRecibidas.cabeza) {
        std::cout << "No hay solicitudes de amistad para aceptar.\n";
        return;
    }

    // Aceptar la solicitud más reciente (al inicio de la lista)
    NodoSolicitud* solicitudAAceptar = solicitudesRecibidas.cabeza;
    solicitudesRecibidas.cabeza = solicitudesRecibidas.cabeza->siguiente;

    // Eliminar la solicitud de la lista del emisor
    solicitudAAceptar->solicitud->emisor->solicitudesEnviadas.eliminarSolicitud(solicitudAAceptar->solicitud);

    std::cout << "Solicitud de amistad aceptada.\n";

    delete solicitudAAceptar->solicitud; // Liberar memoria de la solicitud
    delete solicitudAAceptar; // Liberar memoria del nodo
}

// Metodo para rechazar la solicitud de amistad más reciente
void Usuario::rechazarSolicitud() {
    if (!solicitudesRecibidas.cabeza) {
        std::cout << "No hay solicitudes de amistad para rechazar.\n";
        return;
    }

    // Rechazar la solicitud más reciente (al inicio de la lista)
    NodoSolicitud* solicitudARechazar = solicitudesRecibidas.cabeza;
    solicitudesRecibidas.cabeza = solicitudesRecibidas.cabeza->siguiente;

    // Eliminar la solicitud de la lista del emisor
    solicitudARechazar->solicitud->emisor->solicitudesEnviadas.eliminarSolicitud(solicitudARechazar->solicitud);

    delete solicitudARechazar->solicitud; // Liberar memoria de la solicitud
    delete solicitudARechazar; // Liberar memoria del nodo
    std::cout << "Solicitud de amistad rechazada.\n";
}