#ifndef NODOLISTADOBLE_H
#define NODOLISTADOBLE_H
#include "arbolb.h"
#include <string>

class nodoListadoble
{

public:

    nodoListadoble(const std::string& correo,
                   const std::string& contenido,
                   const std::string& fecha,
                   const std::string& hora,
                   const std::string& imagen);

    std::string correo;
    std::string contenido;
    std::string fecha;
    std::string hora;
    std::string imagen;

    nodoListadoble* siguiente;
    nodoListadoble* anterior;
    ArbolB comentarios;
};

#endif // NODOLISTADOBLE_H
