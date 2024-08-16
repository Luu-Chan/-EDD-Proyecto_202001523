//
// Created by linkm on 9/08/2024.
//
#include "../Headers/Linkedlist.h"
#include "../Headers/menuUser.h"
#include <iostream>
#include <sstream>
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

void Linkedlist::registrarU(string nombres, string apellidos, string fecha, string mail, string pass) {

    // Verificar si el correo ya existe
    Usuario* usuarioExistente = buscarU(mail, "");
    if (usuarioExistente != nullptr) {
        cout << "El correo electrónico ya está registrado." << endl;
        return;
    }

    // Validar la fecha de nacimiento
    int dia, mes;
    dia = std::stoi(fecha.substr(0, 2));

    mes = std::stoi(fecha.substr(3, 2));

    if (fecha[2] != '/' || fecha[5] != '/') {
        cout << "Fecha no con formato no valido" << endl;
        return ;
    }
    // Verificar validez del mes
    if (mes < 1 || mes > 12) {
        cout << "Mes no valido" << endl;
        return ;
    }
    // Verificar validez del día según el mes
    int diasPorMes[] = { 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };

    if (dia < 1 || dia > diasPorMes[mes - 1]) {
        cout << "Dia no valido" << endl;
        return ;
    }
    if (pass.length() < 5) {
        cout << "La contraseña debe tener al menos 5 caracteres." << endl;
        return;
    }

    int Id = obtenerSize() + 1;

    Usuario* nuevoUsuario = new Usuario(Id, nombres, apellidos, fecha, mail, pass);
    agregar(nuevoUsuario);
    cout << "Usuario registrado exitosamente." << endl;
}

void menuAd() {
    int opcion;
    do {
        cout << "MODULO ADMINISTRADOR" << endl;
        cout << "1. Carga de usuarios" << endl;
        cout << "2. Carga de relaciones" << endl;
        cout << "3. Carga de publicaciones" << endl;
        cout << "4. Gestionar usuarios" << endl;
        cout << "5. Reportes" << endl;
        cout << "6. Salir" << endl;
        cout << "Seleccione una opción: ";
        cin >> opcion;

        switch(opcion) {
            case 1:
                cout << "Carga de usuarios" << endl;
            break;
            case 2:
                cout << "Carga de relaciones" << endl;
            break;
            case 3:
                cout << "Carga de publicaciones" << endl;
            break;
            case 4: {
                cout << "1. Eliminar usuarios" << endl;
                break;
            }
            case 5:
                cout << "Reportes" << endl;
            break;
            case 6:
                cout << "Regresando al menu principal" << endl;
            break;
            default:
                cout << "Opción no válida" << endl;
        }

    } while(opcion != 6);
}


void Linkedlist::inicioSesion(const string& correoE, const string& pass) const {

    Usuario* usuario = buscarU(correoE, pass);
    if (usuario != nullptr) {
        if (usuario->correoE == "admin" && usuario->pass == "edd") {
            cout << "Inicio exitoso...."  << endl;
            menuAd();
        } else {
            cout << "Iniciando sesión"  << endl;
            menuAldo();
        }
    } else {
        cout << "Correo o contraseña incorrectos" << endl;
    }
}

void Linkedlist::imprimirLista() const {
    Usuario* actual = head;
    while (actual != nullptr) {
        cout << "ID: " << actual->id << ", Nombre: " << actual->nombre << " " << actual->apellido << ", Correo: " << actual->correoE << endl;
        actual = actual->siguiente;
    }
}

