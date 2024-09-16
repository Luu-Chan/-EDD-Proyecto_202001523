//
// Created by linkm on 20/08/2024.
//
#include "../Headers/ListPubliacion.h"
#include <string>
#include <ctime>
#include <fstream>
#include <iostream>
#include <sstream>
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

void ListaPublicaciones::generarCodigoDot() const {
    std::stringstream archivo;

    archivo << "digraph G {" << std::endl;
    archivo << "  node [shape=record];" << std::endl;

    Publicacion* actual = cabeza;
    int id = 0;

    // Generar nodos y relaciones para cada elemento en la lista
    while (actual != nullptr) {
        archivo << "  nodo" << id << " [label=\"{correo: " << actual->correo
                << "|contenido: " << actual->contenido
                << "|fecha: " << actual->fecha
                << "|hora: " << actual->hora << "}\"];" << std::endl;

        if (actual->siguiente != nullptr) {
            archivo << "  nodo" << id << " -> nodo" << (id + 1) << ";" << std::endl;
            archivo << "  nodo" << (id + 1) << " -> nodo" << id << ";" << std::endl;
        }

        actual = actual->siguiente;
        id++;
    }

    archivo << "}" << std::endl;
    std::fstream dotFiles("publicaciones.dot");
    dotFiles << archivo.str();
    dotFiles.close();
    std::string command = "dot -Tpng publicaciones.dot -o publicaiones.png";
    system(command.c_str());

    std::cout << "Archivo DOT generado con éxito: publicaciones.png" << std::endl;
}


void ListaPublicaciones::generarCodigoDotUser(const std::string &correoE) const {

    std::stringstream archivo;

    archivo << "digraph G {" << std::endl;
    archivo << "  node [shape=record];" << std::endl;

    Publicacion* actual = cabeza;
    int id = 0;

    // Generar nodos y relaciones para cada elemento en la lista
    while (actual != nullptr && actual->correo == correoE) {
        archivo << "  nodo" << id << " [label=\"{correo: " << actual->correo
                << "|contenido: " << actual->contenido
                << "|fecha: " << actual->fecha
                << "|hora: " << actual->hora << "}\"];" << std::endl;
        actual = actual->siguiente;
        id++;
    }
    archivo << "}" << std::endl;
    std::fstream dotFiles("publicacionesUser.dot");
    dotFiles << archivo.str();
    dotFiles.close();
    std::string command = "dot -Tpng publicacionesUser.dot -o publicaionesUser.png";
    system(command.c_str());

    std::cout << "Archivo DOT generado con éxito: publicacionesUser.png" << std::endl;
}