//
// Created by linkm on 20/08/2024.
//

#ifndef PUBLICACION_H
#define PUBLICACION_H
#include <string>


class Publicacion {
public:
    std::string correo;
    std::string contenido;
    std::string fecha;
    std::string hora;
    Publicacion* anterior;
    Publicacion* siguiente;

    Publicacion(const std::string& correo, const std::string& contenido, const std::string& fecha, const std::string& hora)
        : correo(correo), contenido(contenido), fecha(fecha), hora(hora), anterior(nullptr), siguiente(nullptr) {}
};


#endif //PUBLICACION_H
