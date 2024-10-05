#ifndef LISTADOBLE_H
#define LISTADOBLE_H

#include "nodolistadoble.h"

class ListaDoble
{
private:
    nodoListadoble* cabeza;
    nodoListadoble* cola;

public:
    ListaDoble();
    ~ListaDoble();
    void insertarFinal(std::string correo, std::string contenido, std::string fecha, std::string hora, std::string Imagen);
    std::string mostrarAdelante();
    std::string mostrarAtras();
    std::string buscarPorFecha(std::string fecha);
    void eliminarPublicacion(std::string correo, std::string fecha);
    void agregarComentario(std::string correo, std::string fecha, std::string hora, Comentario comentario);
    std::string mostrarComentarios(std::string fecha, std::string hora);
    std::string mostrarPublicaciones();
    std::string buscarCorreoPorHora(std::string fecha, std::string hora);
    void generarGraphviz(std::string nombreArchivo);
    int contarPublicaciones();
    std::vector<std::pair<nodoListadoble*, int>> obtenerPublicacionesConComentarios();
    std::string top3PublicacionesConMasComentarios();

    bool eliminarPublicacionMasReciente(std::string correo);

    // Eliminar todas las publicaciones de un usuario
    void eliminarPublicacionesPorCorreo(std::string correo);


    nodoListadoble* obtenerCabeza() {
        return cabeza;  // Retornar el puntero al primer nodo
    }
};

#endif // LISTADOBLE_H
