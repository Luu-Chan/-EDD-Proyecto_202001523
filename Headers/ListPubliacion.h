//
// Created by linkm on 20/08/2024.
//

#ifndef LISTPUBLIACION_H
#define LISTPUBLIACION_H
#include "Publicacion.h"


class ListaPublicaciones {
public:
    Publicacion* cabeza;
    Publicacion* cola;

    ListaPublicaciones() : cabeza(nullptr), cola(nullptr) {}

    void agregarPublicacion(const std::string& correo, const std::string& contenido);
    void mostrarPublicaciones() const;
    void navegarPublicaciones() const;
    void agregarPublicacionM(const std::string& correo, const std::string& contenido, const std::string& fecha, const std::string& hora);
    void eliminarPublicacion(const std::string& correo);
};
#endif //LISTPUBLIACION_H
