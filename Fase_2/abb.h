#ifndef ABB_H
#define ABB_H

#include "NodoABB.h"
#include "vector"


class ABB
{

private:

    NodoABB* raiz;
    NodoABB* insertarRecursivo(NodoABB* nodo, std::string fecha);
    NodoABB* buscarNodo(NodoABB* nodo, std::string fecha);
    void mostrarPublicacionesPorFecha(NodoABB* nodo, std::string fecha);
    std::string inordenLimitado(NodoABB* nodo, int& contador, int limite);
    std::string preordenLimitado(NodoABB* nodo, int& contador, int limite);
    std::string postordenLimitado(NodoABB* nodo, int& contador, int limite);
    std::vector<std::pair<std::string, int>> contarPublicacionesPorFecha(NodoABB* nodo);
    static bool compararPorCantidad(const std::pair<std::string, int>& a, const std::pair<std::string, int>& b);
    NodoABB* buscarNodoPorFecha(NodoABB* nodo, const std::string& fecha);
    void generarGraphvizRec(NodoABB* nodo, std::ofstream& archivo, std::string fechaEspecifica);
    void eliminarPublicacionesPorCorreoRec(NodoABB* nodo,std::string correo);


public:

    ABB() {
        raiz = nullptr;
    }

    bool eliminarPublicacion(std::string correo);
    void eliminarPublicacionesPorCorreo(std::string correo);

    void insertarPublicacion(std::string correo, std::string contenido, std::string fecha, std::string hora, std::string pathImagen);
    void mostrarPublicacionesPorFecha(std::string fecha);
    std::string mostrarInordenLimitado(int limite);
    std::string mostrarPreordenLimitado(int limite);
    std::string mostrarPostordenLimitado(int limite);
    std::string top3FechasConMasPublicaciones();
    void graficarABBConListaFechaEspecifica(std::string nombreArchivo, std::string fechaEspecifica);

};

#endif // ABB_H
