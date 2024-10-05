#ifndef ARBOLAVL_H
#define ARBOLAVL_H
#include "nodoavl.h"

class arbolAVL
{
private:

    NodoAVL* raiz;
    int height(NodoAVL* node);
    NodoAVL* insert(NodoAVL* node, user* u);
    int getBalance(NodoAVL* node);
    NodoAVL* rotateRight(NodoAVL* y);
    NodoAVL* rotateLeft(NodoAVL* x);
    NodoAVL* minValueNode(NodoAVL* node);
    NodoAVL* deleteNode(NodoAVL* root, const std::string& correoE);
    std::string preOrder(NodoAVL* node);
    std::string inOrder(NodoAVL* node);
    std::string postOrder(NodoAVL* node);
    void generarDot(NodoAVL* node, std::ofstream& out);


public:
    arbolAVL() : raiz(nullptr) {}
    void insertU(user* usuario);
    bool search(const std::string& correoE);
    NodoAVL* searchNode(NodoAVL* node, const std::string& correoE);
    bool credenciales(const std::string& correoE, const std::string& contrasena);
    std::string mostrarInfo(const std::string& correoE);
    user* searchU(const std::string& correoE);
    void eliminar(const std::string& correoE);
    std::string mostrarPreOrder();
    std::string mostrarInOrder();
    std::string mostrarPostOrder();
    void graficar(const std::string& nombreArchivo);
};

#endif // ARBOLAVL_H
