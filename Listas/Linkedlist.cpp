//
// Created by linkm on 9/08/2024.
//
#include "../Headers/Linkedlist.h"
#include <iostream>
using namespace std;

Linkedlist::Linkedlist() :  head(nullptr) {}

Linkedlist::~Linkedlist() {
    Usuario* actual = head;
    while (actual != nullptr) {
        Usuario* siguiente = actual->siguiente;
        delete actual;
        actual = siguiente;
    }
}

void Linkedlist::agregar(Usuario* nuevoUsuario) {
    nuevoUsuario->siguiente = head;
    head = nuevoUsuario;
}

void Linkedlist::eliminar(const string& correoE) {
    Usuario* actual = head;
    Usuario* anterior = nullptr;
    while (actual != nullptr && actual->correoE != correoE) {
        anterior = actual;
        actual = actual->siguiente;
    }
    if (actual != nullptr) {
        if (anterior == nullptr) {
            head = actual->siguiente;
        } else {
            anterior->siguiente = actual->siguiente;
        }
        delete actual;
    }
}

void Linkedlist::imprimirLista() const {
    Usuario* actual = head;
    while (actual != nullptr) {
        cout << "ID: " << actual->id << ", Nombre: " << actual->nombre << " " << actual->apellido << ", Correo: " << actual->correoE << endl;
        actual = actual->siguiente;
    }
}

Usuario* Linkedlist::buscarU(const string& correoE, const string& pass) const {
    Usuario* actual = head;
    while (actual != nullptr) {
        if (actual->correoE == correoE && (pass.empty() || actual->pass == pass)) {
            return actual;
        }
        actual = actual->siguiente;
    }
    return nullptr;
}

int Linkedlist::obtenerSize() const {
    int size = 0;
    Usuario* actual = head;
    while (actual != nullptr) {
        size++;
        actual = actual->siguiente;
    }
    return size;

}
