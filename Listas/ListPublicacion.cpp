//
// Created by linkm on 20/08/2024.
//
#include "../Headers/ListPubliacion.h"
#include <string>
#include <ctime>
#include <iostream>
#include <string>

void ListaPublicaciones::agregarPublicacion(const std::string& correo, const std::string& contenido) {
        // Obtener la fecha y hora actuales
        std::time_t t = std::time(nullptr);
        std::tm* now = std::localtime(&t);
        char fecha[11];
        char hora[6];
        std::strftime(fecha, sizeof(fecha), "%Y-%m-%d", now);
        std::strftime(hora, sizeof(hora), "%H:%M", now);

        Publicacion* nuevaPublicacion = new Publicacion(correo, contenido, fecha, hora);

        if (!cabeza) {
            cabeza = cola = nuevaPublicacion;
        } else {
            cola->siguiente = nuevaPublicacion;
            nuevaPublicacion->anterior = cola;
            cola = nuevaPublicacion;
        }

        std::cout << "Publicación creada por: " << correo << " el " << fecha << " a las " << hora << ".\n";
    }

    void ListaPublicaciones::mostrarPublicaciones() const {
        Publicacion* actual = cabeza;
        while (actual) {
            std::cout << "Correo: " << actual->correo << "\n";
            std::cout << "Contenido: " << actual->contenido << "\n";
            std::cout << "Fecha: " << actual->fecha << "\n";
            std::cout << "Hora: " << actual->hora << "\n";
            std::cout << "-----------------------------\n";
            actual = actual->siguiente;
        }
    }

    void ListaPublicaciones::navegarPublicaciones() const {
        Publicacion* actual = cabeza;
        if (!actual) {
            std::cout << "No hay publicaciones para mostrar.\n";
            return;
        }

        char opcion;
        do {
            std::cout << "Correo: " << actual->correo << "\n";
            std::cout << "Contenido: " << actual->contenido << "\n";
            std::cout << "Fecha: " << actual->fecha << "\n";
            std::cout << "Hora: " << actual->hora << "\n";
            std::cout << "-----------------------------\n";

            std::cout << "Opciones: (A)nterior (S)iguiente (Q)uit: ";
            std::cin >> opcion;

            if (opcion == 'A' || opcion == 'a') {
                if (actual->anterior) {
                    actual = actual->anterior;
                } else {
                    std::cout << "No hay publicaciones anteriores.\n";
                }
            } else if (opcion == 'S' || opcion == 's') {
                if (actual->siguiente) {
                    actual = actual->siguiente;
                } else {
                    std::cout << "No hay más publicaciones.\n";
                }
            }
        } while (opcion != 'Q' && opcion != 'q');
    }

void ListaPublicaciones::eliminarPublicacion(const std::string& correo) {
    Publicacion* actual = cabeza;
    while (actual) {
        if (actual->correo == correo) {
            // Eliminar la publicación
            if (actual->anterior) {
                actual->anterior->siguiente = actual->siguiente;
            } else {
                cabeza = actual->siguiente; // Era la primera
            }

            if (actual->siguiente) {
                actual->siguiente->anterior = actual->anterior;
            } else {
                cola = actual->anterior; // Era la última
            }

            delete actual;
            std::cout << "Publicación eliminada.\n";
            return;
        }
        actual = actual->siguiente;
    }

    std::cout << "Publicación no encontrada o no pertenece a este usuario.\n";
}

void ListaPublicaciones::agregarPublicacionM(const std::string &correo, const std::string &contenido, const std::string &fecha, const std::string &hora) {


    Publicacion* nuevaPublicacion = new Publicacion(correo, contenido, fecha, hora);

    if (!cabeza) {
        cabeza = cola = nuevaPublicacion;
    } else {
        cola->siguiente = nuevaPublicacion;
        nuevaPublicacion->anterior = cola;
        cola = nuevaPublicacion;
    }
    std::cout << "Publicación creada por: " << correo << " el " << fecha << " a las " << hora << ".\n";
}
