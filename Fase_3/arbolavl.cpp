#include "arbolavl.h"
#include <qdebug.h>
#include <qlogging.h>
#include <string>
#include "user.h"
#include "nodoavl.h"
#include <fstream>


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


user* arbolAVL::searchU(const std::string& correoE){

    NodoAVL* result = searchNode(raiz, correoE);

    return result->usuario;

}



NodoAVL* arbolAVL::minValueNode(NodoAVL* node) {
    NodoAVL* current = node;

    // El valor mínimo está en el subárbol más a la izquierda
    while (current->left != nullptr)
        current = current->left;

    return current;
}

// Eliminar un nodo del árbol AVL
NodoAVL* arbolAVL::deleteNode(NodoAVL* raiz, const std::string& correo) {
    // Paso 1: Realizar la eliminación normal de BST
    if (raiz == nullptr)
        return raiz;

    // Si el correo a eliminar es menor que el correo del nodo actual, entonces está en el subárbol izquierdo
    if (correo < raiz->usuario->getcorreoE())
        raiz->left = deleteNode(raiz->left, correo);

    // Si el correo a eliminar es mayor que el correo del nodo actual, entonces está en el subárbol derecho
    else if (correo > raiz->usuario->getcorreoE())
        raiz->right = deleteNode(raiz->right, correo);

    // Si el correo es el mismo que el correo del nodo actual, este es el nodo a eliminar
    else {
        // Nodo con solo un hijo o sin hijos
        if ((raiz->left == nullptr) || (raiz->right == nullptr)) {
            NodoAVL* temp = raiz->left ? raiz->left : raiz->right;

            // Caso 1: Sin hijos
            if (temp == nullptr) {
                temp = raiz;
                raiz = nullptr;
            }
            // Caso 2: Un solo hijo
            else {
                *raiz = *temp; // Copia los contenidos del hijo no vacío
            }

            delete temp;
        }
        // Nodo con dos hijos
        else {
            // Obtener el sucesor en el subárbol derecho (el menor en el subárbol derecho)
            NodoAVL* temp = minValueNode(raiz->right);

            // Copiar los datos del sucesor al nodo actual
            raiz->usuario = temp->usuario;

            // Eliminar el sucesor
            raiz->right = deleteNode(raiz->right, temp->usuario->getcorreoE());
        }
    }

    // Si el árbol tenía solo un nodo, simplemente retorna
    if (raiz == nullptr)
        return raiz;

    // Paso 2: Actualizar la altura del nodo actual
    raiz->height = std::max(height(raiz->left), height(raiz->right)) + 1;

    // Paso 3: Obtener el factor de balance del nodo actual
    int balance = getBalance(raiz);

    // Caso 1: Izquierda Izquierda
    if (balance > 1 && getBalance(raiz->left) >= 0)
        return rotateRight(raiz);

    // Caso 2: Izquierda Derecha
    if (balance > 1 && getBalance(raiz->left) < 0) {
        raiz->left = rotateLeft(raiz->left);
        return rotateRight(raiz);
    }

    // Caso 3: Derecha Derecha
    if (balance < -1 && getBalance(raiz->right) <= 0)
        return rotateLeft(raiz);

    // Caso 4: Derecha Izquierda
    if (balance < -1 && getBalance(raiz->right) > 0) {
        raiz->right = rotateRight(raiz->right);
        return rotateLeft(raiz);
    }

    return raiz;
}


void arbolAVL::eliminar(const std::string& correoE){
     raiz = deleteNode(raiz, correoE);

}


std::string arbolAVL::preOrder(NodoAVL* node){

    if (node == nullptr) {
        return "";  // Si el nodo es nulo, retorna una cadena vacía
    }

    // Concatenar la información del nodo actual
    std::string text = node->usuario->mostrarInfo() + "\n";

    // Concatenar el resultado del recorrido del subárbol izquierdo
    text += preOrder(node->left);

    // Concatenar el resultado del recorrido del subárbol derecho
    text += preOrder(node->right);

    return text;
}


// Recorrido en Inorden (LNR): Izquierda, Nodo, Derecha
std::string arbolAVL::inOrder(NodoAVL* node) {
    std::string text ="";

    if (node != nullptr) {
        text.append(inOrder(node->left));       // Recorrer el subárbol izquierdo
        text.append(node->usuario->mostrarInfo() + "\n");  // Mostrar la información del usuario
        text.append(inOrder(node->right));      // Recorrer el subárbol derecho
    }
    return text;
}


// Recorrido en Postorden (LRN): Izquierda, Derecha, Nodo
std::string arbolAVL::postOrder(NodoAVL* node){
    std::string text ="";

    if (node != nullptr) {
        text.append(postOrder(node->left));     // Recorrer el subárbol izquierdo
        text.append(postOrder(node->right));    // Recorrer el subárbol derecho
        text.append(text += node->usuario->mostrarInfo() + "\n");
    }
    return text;
}

std::string arbolAVL::mostrarPreOrder() {
    return preOrder(raiz);
}

std::string arbolAVL::mostrarInOrder() {
    return inOrder(raiz);
}

std::string arbolAVL::mostrarPostOrder() {
    return postOrder(raiz);
}


// Función auxiliar para generar el contenido DOT
void arbolAVL::generarDot(NodoAVL* node, std::ofstream& out) {
    if (node != nullptr) {
        // Crear el nodo
        out << "    \"" << node->usuario->getcorreoE() << "\" [label=\"" << node->usuario->mostrarInfoG() << "\"];\n";

        // Si hay hijo izquierdo, conectar
        if (node->left != nullptr) {
            out << "    \"" << node->usuario->getcorreoE() << "\" -> \"" << node->left->usuario->getcorreoE() << "\";\n";
            generarDot(node->left, out);  // Llamar recursivamente para el hijo izquierdo
        }

        // Si hay hijo derecho, conectar
        if (node->right != nullptr) {
            out << "    \"" << node->usuario->getcorreoE() << "\" -> \"" << node->right->usuario->getcorreoE() << "\";\n";
            generarDot(node->right, out); // Llamar recursivamente para el hijo derecho
        }
    }
}

// Función para graficar el árbol
void arbolAVL::graficar(const std::string& nombreArchivo) {
    std::ofstream out(nombreArchivo);
    if (out.is_open()) {
        out << "digraph AVLTree {\n";
        out << "    node [shape=record];\n";
        generarDot(raiz, out);  // Llamar a la función auxiliar para generar el contenido
        out << "}\n";
        out.close();
        // Generar la imagen utilizando Graphviz
        std::string comando = "dot -Tpng " + nombreArchivo + " -o " + nombreArchivo + ".png";
        system(comando.c_str());

        qDebug() << "Archivo DOT generado con éxito: "<< nombreArchivo<< ".png" ;


    }
}
