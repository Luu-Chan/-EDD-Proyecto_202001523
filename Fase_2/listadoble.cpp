#include "listadoble.h"
#include "QMessageBox"
#include <fstream>
#include <iostream>

ListaDoble::ListaDoble(): cabeza(nullptr), cola(nullptr) {}

void ListaDoble::insertarFinal(std::string correo, std::string contenido, std::string fecha, std::string hora, std::string pathImagen) {
    nodoListadoble* nuevoNodo = new nodoListadoble(correo, contenido, fecha, hora, pathImagen);
    if (cabeza == nullptr) { // Si la lista está vacía
        cabeza = nuevoNodo;
        cola = nuevoNodo;
    } else {
        cola->siguiente = nuevoNodo;
        nuevoNodo->anterior = cola;
        cola = nuevoNodo;
    }
}


// Método para mostrar la lista hacia adelante
std::string ListaDoble::mostrarAdelante() {
    nodoListadoble* temp = cabeza;
    std::string text = "";

    while (temp != nullptr) {
        text +=  "Correo: " + temp->correo + "\n";
        text += "Contenido: " + temp->contenido + "\n";
        text +=  "Fecha: " + temp->fecha + "\n";
        text +=  "Hora: " + temp->hora + "\n";
        text +=  "Imagen: " + temp->imagen + "\n";
        text +=  "-----------------------------\n";
        temp = temp->siguiente;
    }
    return text;
}


std::string ListaDoble::mostrarAtras() {
    nodoListadoble* temp = cola;
    std::string text = "";

    while (temp != nullptr) {
        text +=  "Correo: " + temp->correo + "\n";
        text += "Contenido: " + temp->contenido + "\n";
        text +=  "Fecha: " + temp->fecha + "\n";
        text +=  "Hora: " + temp->hora + "\n";
        text +=  "Imagen: " + temp->imagen + "\n";
        text +=  "-----------------------------\n";
        temp = temp->anterior;
    }
    return text;
}

// Método para buscar publicaciones por fecha
std::string ListaDoble::buscarPorFecha(std::string fecha) {
    std::string text = "";

    nodoListadoble* temp = cabeza;
    bool encontrado = false;
    while (temp != nullptr) {
        if (temp->fecha == fecha) {
            text +=  "Correo: " + temp->correo + "\n";
            text += "Contenido: " + temp->contenido + "\n";
            text +=  "Fecha: " + temp->fecha + "\n";
            text +=  "Hora: " + temp->hora + "\n";
            text +=  "Imagen: " + temp->imagen + "\n";
            text +=  "-----------------------------\n";
            encontrado = true;
        }
        temp = temp->siguiente;
    }
    if (!encontrado) {
        qDebug() << "No se encontraron publicaciones en la fecha: " << fecha << "\n";
    }
    return text;
}


// Método para eliminar una publicación por correo y fecha
void ListaDoble::eliminarPublicacion(std::string correo, std::string fecha) {
    nodoListadoble* temp = cabeza;
    while (temp != nullptr) {
        if (temp->correo == correo && temp->fecha == fecha) {
            if (temp == cabeza) {
                cabeza = temp->siguiente;
                if (cabeza != nullptr) {
                    cabeza->anterior = nullptr;
                }
            } else if (temp == cola) {
                cola = temp->anterior;
                if (cola != nullptr) {
                    cola->siguiente = nullptr;
                }
            } else {
                temp->anterior->siguiente = temp->siguiente;
                temp->siguiente->anterior = temp->anterior;
            }
            delete temp;
            qDebug() << "Publicación eliminada.\n";
            return;
        }
        temp = temp->siguiente;
    }
    qDebug() << "Publicación no encontrada.\n";
}


// Método para eliminar la lista y liberar memoria
ListaDoble::~ListaDoble() {
    while (cabeza != nullptr) {
        nodoListadoble* temp = cabeza;
        cabeza = cabeza->siguiente;
        delete temp;
    }
}


void ListaDoble::agregarComentario(std::string correo, std::string fecha, std::string hora, Comentario comentario) {
    nodoListadoble* temp = cabeza;

    // Buscar la publicación correspondiente
    while (temp != nullptr) {
        if (temp->correo == correo && temp->fecha == fecha && temp->hora == hora) {
            temp->comentarios.insertar(comentario);
            return;
        }
        temp = temp->siguiente;
    }

    // Si la publicación no se encuentra
    qDebug() << "Publicación no encontrada para agregar el comentario.\n";
}

std::string ListaDoble::mostrarComentarios( std::string fecha, std::string hora) {
    nodoListadoble* temp = cabeza;
    std::string text = "";

    // Buscar la publicación correspondiente
    while (temp != nullptr) {
        if ( temp->fecha == fecha && temp->hora == hora) {
            qDebug() << "Comentarios de la publicación:\n";
            text += temp->comentarios.imprimir();
             return text;
        }
        temp = temp->siguiente;

    }

    // Si la publicación no se encuentra
    text += "Publicación no encontrada para mostrar comentarios.\n";
    return text;
}


std::string ListaDoble::mostrarPublicaciones() {
    nodoListadoble* temp = cabeza;
    std::string text = "";

    while (temp != nullptr) {
        text += "Correo: " + temp->correo + "\n";
        text += "Contenido: " + temp->contenido + "\n";
        text += "Fecha: " + temp->fecha + "\n";
        text += "Hora: " + temp->hora + "\n";
        text += "Imagen: " + temp->imagen + "\n";
        text += "-----------------------------\n";
        temp = temp->siguiente;
    }
    return text;
}


std::string ListaDoble::buscarCorreoPorHora(std::string fecha, std::string hora){
    nodoListadoble* temp = cabeza;
    while (temp != nullptr) {
        if (temp->hora == hora) {
            return temp->correo;
        }
        temp = temp->siguiente;
    }
    return "";
}

void ListaDoble::generarGraphviz(std::string nombreArchivo) {
    std::ofstream archivo(nombreArchivo);
    if (!archivo.is_open()) {
        qDebug() << "Error al abrir el archivo para escribir el gráfico.";
        return;
    }

    archivo << "digraph G {\n";
    archivo << "  rankdir=TB;\n"; // Orientación de arriba hacia abajo (vertical)
    archivo << "  node [shape=record];\n";

    nodoListadoble* temp = cabeza;
    int id = 0;

    // Generar nodos y relaciones para la lista
    while (temp != nullptr) {
        archivo << "  nodo" << id << " [label=\"{Correo: " << temp->correo
                << " | Contenido: " << temp->contenido
                << " | Fecha: " << temp->fecha
                << " | Hora: " << temp->hora
                << " | Imagen: " << temp->imagen << "}\"];\n";

        if (temp->siguiente != nullptr) {
            archivo << "  nodo" << id << " -> nodo" << id + 1 << " [dir=both];\n";
        }

        temp = temp->siguiente;
        id++;
    }

    archivo << "}\n";
    archivo.close();

    // Generar la imagen utilizando Graphviz
    std::string comando = "dot -Tpng " + nombreArchivo + " -o " + nombreArchivo + ".png";
    system(comando.c_str());

    qDebug() << "Archivo DOT generado con éxito: "<< nombreArchivo<< ".png" ;
}

int ListaDoble::contarPublicaciones() {
    int contador = 0;
    nodoListadoble* temp = cabeza;
    while (temp != nullptr) {
        contador++;
        temp = temp->siguiente;
    }
    return contador;
}

std::vector<std::pair<nodoListadoble*, int>> ListaDoble::obtenerPublicacionesConComentarios() {
    std::vector<std::pair<nodoListadoble*, int>> publicacionesConComentarios;

    nodoListadoble* temp = cabeza;
    while (temp != nullptr) {
        // Añadir la publicación y el número de comentarios
        publicacionesConComentarios.push_back({temp, temp->comentarios.contarComentarios()});
        temp = temp->siguiente;
    }

    return publicacionesConComentarios;
}

std::string ListaDoble::top3PublicacionesConMasComentarios() {
    std::vector<std::pair<nodoListadoble*, int>> publicacionesConComentarios = obtenerPublicacionesConComentarios();

    // Ordenar las publicaciones por cantidad de comentarios de mayor a menor
    sort(publicacionesConComentarios.begin(), publicacionesConComentarios.end(), [](std::pair<nodoListadoble*, int> a, std::pair<nodoListadoble*, int> b) {
        return a.second > b.second;
    });

    // Construir el string con el top 3 de publicaciones
    std::string resultado = "Top 3 publicaciones con mayor cantidad de comentarios:\n";
    for (int i = 0; i < std::min(3, (int)publicacionesConComentarios.size()); i++) {
        nodoListadoble* publicacion = publicacionesConComentarios[i].first;
        resultado += "Correo: " + publicacion->correo + "\n";
        resultado += "Contenido: " + publicacion->contenido + "\n";
        resultado += "Fecha: " + publicacion->fecha + "\n";
        resultado += "Comentarios: " + std::to_string(publicacionesConComentarios[i].second) + "\n";
        resultado += "-----------------------------\n";
    }

    return resultado;
}

bool ListaDoble::eliminarPublicacionMasReciente(std::string correo) {
    nodoListadoble* temp = cola; // Comenzamos desde la cola, donde está la publicación más reciente

    while (temp != nullptr) {
        if (temp->correo == correo) {
            // Si es el único nodo en la lista
            if (temp == cabeza && temp == cola) {
                delete temp;
                cabeza = cola = nullptr;
            } else if (temp == cabeza) { // Si es el primer nodo
                cabeza = cabeza->siguiente;
                cabeza->anterior = nullptr;
                delete temp;
            } else if (temp == cola) { // Si es el último nodo
                cola = cola->anterior;
                cola->siguiente = nullptr;
                delete temp;
            } else { // nodoListadoble intermedio
                temp->anterior->siguiente = temp->siguiente;
                temp->siguiente->anterior = temp->anterior;
                delete temp;
            }
            return true; // Eliminación exitosa
        }
        temp = temp->anterior; // Moverse al nodo anterior
    }
    return false; // No se encontró la publicación
}

// Eliminar todas las publicaciones de un usuario
void ListaDoble::eliminarPublicacionesPorCorreo(std::string correo) {
    nodoListadoble* temp = cabeza;

    while (temp != nullptr) {
        nodoListadoble* siguiente = temp->siguiente; // Guardar el siguiente nodo

        if (temp->correo == correo) {
            // Eliminar nodo actual
            if (temp == cabeza) { // Si es el primer nodo
                cabeza = cabeza->siguiente;
                if (cabeza != nullptr) {
                    cabeza->anterior = nullptr;
                } else {
                    cola = nullptr; // Lista vacía
                }
            } else if (temp == cola) { // Si es el último nodo
                cola = cola->anterior;
                cola->siguiente = nullptr;
            } else { // nodoListadoble intermedio
                temp->anterior->siguiente = temp->siguiente;
                temp->siguiente->anterior = temp->anterior;
            }

            delete temp; // Liberar memoria
        }

        temp = siguiente; // Moverse al siguiente nodo
    }
}
