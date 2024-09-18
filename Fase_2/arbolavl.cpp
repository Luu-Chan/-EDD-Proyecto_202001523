#include "arbolavl.h"
#include <string>
#include "user.h"
#include "nodoavl.h"


    // Obtener la altura del nodo
    int arbolAVL::height(NodoAVL* node) {
        return node == nullptr ? 0 : node->height;
    }

    // Obtener el factor de balance del nodo
    int arbolAVL::getBalance(NodoAVL* node) {
          return node == nullptr ? 0 : height(node->left) - height(node->right);
    }

    // Rotación simple a la derecha
    NodoAVL* arbolAVL::rotateRight(NodoAVL* y) {
        NodoAVL* x = y->left;
        NodoAVL* x1 = x->right;

        x->right = y;
        y->left = x1;

        // Actualizar alturas
        y->height = std::max(height(y->left), height(y->right)) + 1;
        x->height = std::max(height(x->left), height(x->right)) + 1;

        return x;
    }

    // Rotación simple a la izquierda
    NodoAVL* arbolAVL::rotateLeft(NodoAVL* x) {
        NodoAVL* y = x->right;
        NodoAVL* y1 = y->left;

        // Rotación
        y->left = x;
         x->right = y1;

        // Actualizar alturas
        x->height = std::max(height(x->left), height(x->right)) + 1;
        y->height = std::max(height(y->left), height(y->right)) + 1;

        return y;
    }

    // Insertar un nodo en el árbol AVL
    NodoAVL* arbolAVL::insert(NodoAVL* node, user* u) {
        // 1. Realizar la inserción normal en el avl
        if (node == nullptr) {
            return new NodoAVL(u);
        }

        // Comparar los correos electrónicos para ordenar
        if (u->getcorreoE() < node->usuario->getcorreoE()) {
            node->left = insert(node->left, u);
        } else if (u->getcorreoE() > node->usuario->getcorreoE()) {
            node->right = insert(node->right, u);

        } else {
            return node; // No se permiten usuarios con el mismo correo
        }

        // 2. Actualizar la altura del ancestro actual
        node->height = std::max(height(node->left), height(node->right)) + 1;

        // 3. Obtener el factor de balance del ancestro actual para comprobar si está desbalanceado
        int balance = getBalance(node);

        // Si el nodo está desbalanceado, hay 4 casos a considerar:

        // Caso Izquierda-Izquierda
        if (balance > 1 && u->getcorreoE() < node->left->usuario->getcorreoE()) {
            return rotateRight(node);
        }

        // Caso Derecha-Derecha
        if (balance < -1 && u->getcorreoE() > node->right->usuario->getcorreoE()) {
            return rotateLeft(node);
        }

        // Caso Izquierda-Derecha
        if (balance > 1 && u->getcorreoE() > node->left->usuario->getcorreoE()) {
            node->left = rotateLeft(node->left);
            return rotateRight(node);
        }

        // Caso Derecha-Izquierda
        if (balance < -1 && u->getcorreoE() < node->right->usuario->getcorreoE()) {
            node->right = rotateRight(node->right);
            return rotateLeft(node);
        }

        // Retornar el nodo (sin cambios si está balanceado)
            return node;
    }

    // Buscar un usuario por correo
    NodoAVL* arbolAVL::searchNode(NodoAVL* node, const std::string& correoE) {
        if (node == nullptr || node->usuario->getcorreoE() == correoE)
            return node;

        if (correoE < node->usuario->getcorreoE())
            return searchNode(node->left, correoE);

        return searchNode(node->right, correoE);
    }

    // Método público para insertar un usuario
    void arbolAVL::insertU(user* u) {
        raiz = insert(raiz, u);
    }

    // Método público para buscar un usuario por correo
    bool arbolAVL::search(const std::string& correoE) {
        return searchNode(raiz, correoE) != nullptr;
    }

    //Metodo para verificar las credenciales de un usuario
    bool arbolAVL::credenciales(const std::string& correoE, const std::string& pass) {
        NodoAVL* nodo = searchNode(raiz, correoE);
        if (nodo != nullptr && nodo->usuario->getpass() == pass) {
            return true;
        }
        return false;
    }

