#include "abb.h"
#include "NodoABB.h"
#include <algorithm>
#include <qlogging.h>
#include <fstream>
#include "QDebug"

NodoABB* ABB::insertarRecursivo(NodoABB* nodo, std::string fecha) {
    if (nodo == nullptr) {
        return new NodoABB(fecha);
    }
    if (fecha < nodo->fecha) {
        nodo->izquierdo = insertarRecursivo(nodo->izquierdo, fecha);
    } else if (fecha > nodo->fecha) {
        nodo->derecho = insertarRecursivo(nodo->derecho, fecha);
    }
    return nodo;
}

std::string ABB::inordenLimitado(NodoABB* nodo, int& contador, int limite) {
    std::string text = "";

    if (nodo == nullptr || contador >= limite) {
        return text;
    }
    inordenLimitado(nodo->izquierdo, contador, limite);
    if (contador < limite) {
        text += "Fecha: " + nodo->fecha + "\n";
        text += nodo->publicaciones.mostrarPublicaciones();
        contador++;
    }
    text += inordenLimitado(nodo->derecho, contador, limite);
    return text;
}

std::string ABB::preordenLimitado(NodoABB* nodo, int& contador, int limite) {
    std::string text = "";

    if (nodo == nullptr || contador >= limite) {
        return text;
    }
    if (contador < limite) {
        text += + "Fecha: " + nodo->fecha + "\n";
        text += nodo->publicaciones.mostrarPublicaciones();
        contador++;
    }
    text += preordenLimitado(nodo->izquierdo, contador, limite);
    text += preordenLimitado(nodo->derecho, contador, limite);
    return text;
}

std::string ABB::postordenLimitado(NodoABB* nodo, int& contador, int limite) {
     std::string text = "";

    if (nodo == nullptr || contador >= limite) {
        return text;
    }
    text += postordenLimitado(nodo->izquierdo, contador, limite);
    text += postordenLimitado(nodo->derecho, contador, limite);
    if (contador < limite) {
        text += "Fecha: " + nodo->fecha + "\n";
        text += nodo->publicaciones.mostrarPublicaciones();
        contador++;
    }
    return text;
}


void ABB::insertarPublicacion(std::string correo, std::string contenido, std::string fecha, std::string hora, std::string pathImagen) {
    // Insertar nodo de fecha si no existe
    raiz = insertarRecursivo(raiz, fecha);

    // Buscar el nodo de la fecha e insertar la publicación en la lista doblemente enlazada
    NodoABB* nodoFecha = buscarNodo(raiz, fecha);
    if (nodoFecha != nullptr) {
        nodoFecha->publicaciones.insertarFinal(correo, contenido, fecha, hora, pathImagen);
    }
}

NodoABB* ABB::buscarNodo(NodoABB* nodo, std::string fecha) {
    if (nodo == nullptr || nodo->fecha == fecha) {
        return nodo;
    }
    if (fecha < nodo->fecha) {
        return buscarNodo(nodo->izquierdo, fecha);
    }
    return buscarNodo(nodo->derecho, fecha);
}

std::string ABB::mostrarInordenLimitado(int limite) {
    int contador = 0;
    return inordenLimitado(raiz, contador, limite);
}

std::string ABB::mostrarPreordenLimitado(int limite) {
    int contador = 0;
    return preordenLimitado(raiz, contador, limite);
}

std::string ABB::mostrarPostordenLimitado(int limite) {
    int contador = 0;
    return postordenLimitado(raiz, contador, limite);
}



std::vector<std::pair<std::string, int>> ABB::contarPublicacionesPorFecha(NodoABB* nodo) {
    std::vector<std::pair<std::string, int>> fechasConCantidad;

    if (nodo == nullptr) {
        return fechasConCantidad;
    }

    // Recorrido inorden para obtener todas las fechas
    std::vector<std::pair<std::string, int>> izq = contarPublicacionesPorFecha(nodo->izquierdo);
    std::vector<std::pair<std::string, int>> der = contarPublicacionesPorFecha(nodo->derecho);

    // Agregar fechas del subárbol izquierdo
    fechasConCantidad.insert(fechasConCantidad.end(), izq.begin(), izq.end());

    // Añadir la fecha actual con la cantidad de publicaciones en la lista doble
    fechasConCantidad.push_back({nodo->fecha, nodo->publicaciones.contarPublicaciones()});

    // Agregar fechas del subárbol derecho
    fechasConCantidad.insert(fechasConCantidad.end(), der.begin(), der.end());

    return fechasConCantidad;
}

bool ABB::compararPorCantidad(const std::pair<std::string, int>& a, const std::pair<std::string, int>& b) {
    return a.second > b.second;
}

std::string ABB::top3FechasConMasPublicaciones() {
    std::vector<std::pair<std::string, int>> todasFechas = contarPublicacionesPorFecha(raiz);
    std::string text = "";

    sort(todasFechas.begin(), todasFechas.end(), compararPorCantidad);

    // Mostrar el top 3 de fechas
    text += "Top 3 fechas con mayor cantidad de publicaciones:\n";
    for (int i = 0; i < std::min(3, (int)todasFechas.size()); i++) {
        text +=  "Fecha: " + todasFechas[i].first + " - Publicaciones: " + std::to_string( todasFechas[i].second) + "\n";
    }
    return text;
}


void ABB::generarGraphvizRec(NodoABB* nodo, std::ofstream& archivo, std::string fechaEspecifica) {
    if (nodo == nullptr) {
        return;
    }

    // Etiqueta para el nodo actual del ABB
    archivo << "  \"" << reinterpret_cast<uintptr_t>(nodo) << "\" [label=\"Fecha: " << nodo->fecha << "\"];\n";

    // Si el nodo tiene hijo izquierdo, se genera el enlace
    if (nodo->izquierdo != nullptr) {
        archivo << "  \"" << reinterpret_cast<uintptr_t>(nodo) << "\" -> \"" << reinterpret_cast<uintptr_t>(nodo->izquierdo) << "\";\n";
        generarGraphvizRec(nodo->izquierdo, archivo, fechaEspecifica);
    }

    // Si el nodo tiene hijo derecho, se genera el enlace
    if (nodo->derecho != nullptr) {
        archivo << "  \"" << reinterpret_cast<uintptr_t>(nodo) << "\" -> \"" << reinterpret_cast<uintptr_t>(nodo->derecho) << "\";\n";
        generarGraphvizRec(nodo->derecho, archivo, fechaEspecifica);
    }

    // Si la fecha del nodo coincide con la fecha especificada, graficar la lista de publicaciones
    if (nodo->fecha == fechaEspecifica) {
        nodoListadoble* temp = nodo->publicaciones.obtenerCabeza();
        int id = 0;
        std::string nodoPadre = "\"" + std::to_string(reinterpret_cast<uintptr_t>(nodo)) + "\"";

        // Asegurarse de que la lista de publicaciones se grafique correctamente
        while (temp != nullptr) {
            // Etiqueta para cada publicación de la lista
            std::string nodoPublicacion = nodoPadre + "_pub" + std::to_string(id);
            archivo << "  \"" << nodoPublicacion << "\" [label=\"{Correo: " << temp->correo
                    << " | Contenido: " << temp->contenido
                    << " | Hora: " << temp->hora
                    << " | Imagen: " << temp->imagen << "}\"];\n";

            // Enlace entre el nodo del ABB y la publicación
            archivo << "  \"" << nodoPadre << "\" -> \"" << nodoPublicacion << "\" [style=dotted];\n";

            // Enlace entre las publicaciones de la lista
            if (temp->siguiente != nullptr) {
                std::string siguientePublicacion = nodoPadre + "_pub" + std::to_string(id + 1);
                archivo << "  \"" << nodoPublicacion << "\" -> \"" << siguientePublicacion << "\";\n";
            }

            temp = temp->siguiente;
            id++;
        }
    }

}


void ABB::graficarABBConListaFechaEspecifica(std::string nombreArchivo, std::string fechaEspecifica) {
    std::ofstream archivo(nombreArchivo);
    if (!archivo.is_open()) {
        qDebug() << "Error al abrir el archivo para escribir el gráfico." ;
        return;
    }

    archivo << "digraph G {\n";
    archivo << "  node [shape=record];\n";

    generarGraphvizRec(raiz, archivo, fechaEspecifica);

    archivo << "}\n";
    archivo.close();

    std::string comando = "dot -Tpng " + nombreArchivo + " -o " + nombreArchivo + ".png";
    system(comando.c_str());

    qDebug() << "Archivo DOT generado con éxito: "<< nombreArchivo<< ".png" ;

}


NodoABB* ABB::buscarNodoPorFecha(NodoABB* nodo, const std::string& fecha) {
    // Base case: Si el nodo es nulo, no se encontró
    if (nodo == nullptr) {
        return nullptr;
    }

    // Comparar la fecha buscada con la fecha del nodo actual
    if (fecha < nodo->fecha) {
        // Si la fecha buscada es menor, buscar en el subárbol izquierdo
        return buscarNodoPorFecha(nodo->izquierdo, fecha);
    } else if (fecha > nodo->fecha) {
        // Si la fecha buscada es mayor, buscar en el subárbol derecho
        return buscarNodoPorFecha(nodo->derecho, fecha);
    } else {
        // Si se encuentra la fecha, retornar el nodo actual
        return nodo;
    }
}

// Función para eliminar la publicación más reciente de un usuario dado un correo
bool ABB::eliminarPublicacion(std::string correo) {
    NodoABB* nodoFecha = buscarNodoPorFecha(raiz, correo);
    if (nodoFecha != nullptr) {
        return nodoFecha->publicaciones.eliminarPublicacionMasReciente(correo);
    }
    return false; // No se encontró el nodo para la fecha
}

// Función para eliminar todas las publicaciones de un usuario dado un correo
void ABB::eliminarPublicacionesPorCorreo(std::string correo) {
    eliminarPublicacionesPorCorreoRec(raiz, correo);
}


// Método recursivo para eliminar publicaciones por correo
void ABB::eliminarPublicacionesPorCorreoRec(NodoABB* nodo, std::string correo) {
    if (nodo == nullptr) {
        return; // Base case: Si el nodo es nulo, retornamos
    }

    // Llamar recursivamente en el subárbol izquierdo
    eliminarPublicacionesPorCorreoRec(nodo->izquierdo, correo);

    // Llamar recursivamente en el subárbol derecho
    eliminarPublicacionesPorCorreoRec(nodo->derecho, correo);

    // Eliminar las publicaciones del nodo actual
    nodo->publicaciones.eliminarPublicacionesPorCorreo(correo);
}



