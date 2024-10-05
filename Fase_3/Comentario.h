#ifndef COMENTARIO_H
#define COMENTARIO_H
#include <string>


class Comentario {

public:
    std::string autor;
    std::string contenido;
    std::string fecha;
    std::string hora;

    Comentario() : autor(""), contenido(""), fecha(""), hora("") {}
    Comentario(std::string a, std::string c, std::string f, std::string h)
        : autor(a), contenido(c), fecha(f), hora(h) {}
};

#endif // COMENTARIO_H
