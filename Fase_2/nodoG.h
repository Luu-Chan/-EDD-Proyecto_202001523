#ifndef NODOG_H
#define NODOG_H

#include <fstream>

// Clase para los vecinos (amistades) de un nodo
class Neighbor {
public:
    int value;  // Índice del usuario en el grafo
    Neighbor *next;

    Neighbor(int val) : value(val), next(nullptr) {}
};

// Clase para los nodos (usuarios) del grafo
class Node {
public:
    int value;  // Índice del usuario
    Node* next;  // Siguiente usuario
    Neighbor* neighbors;  // Lista de amigos (vecinos)

    Node(int val) : value(val), next(nullptr), neighbors(nullptr) {}

    // Insertar un vecino (amistad)
    void insertNeighbor(int destiny) {
        Neighbor* newNeighbor = new Neighbor(destiny);
        newNeighbor->next = neighbors;
        neighbors = newNeighbor;
    }

    // Mostrar los vecinos (amistades)
    void graphNeighbors(std::ofstream &out) {
        Neighbor* current = neighbors;
        while (current != nullptr) {
            out << current->value << " ";
            current = current->next;
        }
    }
};


#endif // NODOG_H
