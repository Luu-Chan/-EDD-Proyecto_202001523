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

void Linkedlist::agregar(Usuario* nuevoUsuario) { //Agrega nuevo usuario directamente sin validar nada
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

Usuario* Linkedlist::buscarU(const string& correoE) const {
    Usuario* actual = head;
    while (actual != nullptr) {
        //Buscar usuario mediante su correo
        if (actual->correoE == correoE) {
            return actual;
        }
        actual = actual->siguiente;
    }
    return nullptr;
}

void Linkedlist::perfil(const string& correoE) const{
    Usuario* actual = head;
    while (actual != nullptr) {
        if (actual->correoE == correoE) { //Muestra el perfil del usuario actual
            cout << "Mis Datos: \n" " Nombre: " << actual->nombre << " " << actual->apellido << " Correo: " << actual->correoE << endl;
        }
        actual = nullptr;
    }
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
    Usuario* usuarioExistente = buscarU(mail);
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

Usuario *Linkedlist::validarD(const string &correoE, const string &pass) const {
    Usuario* actual = head;
    while (actual != nullptr) {
        //Validar credenciales
        if (actual->correoE == correoE && actual->pass == pass) {
            return actual;
        }
        actual = actual->siguiente;
    }
    return nullptr;
}

void Linkedlist::inicioSesion(const string& correoE, const string& pass) const {

    Usuario* usuario = validarD(correoE, pass);
    if (usuario != nullptr) {
        if (usuario->correoE == "admin" && usuario->pass == "edd") {
            cout << "Inicio administrador...\n"  << endl;
            menuAdmin();
        } else {
            cout << "*********** Iniciando sesión ****************\n"  << endl;
            menuUser(correoE); //Se utiliza el correo como su clave de inicio de sesion
        }
    } else {
        cout << "Correo o contraseña incorrectos" << endl;
    }
}

void Linkedlist::imprimirLista() const {
    Usuario* actual = head;
    while (actual != nullptr) {
        cout << "ID: " << actual->id << " Nombre: " << actual->nombre << " " << actual->apellido << " Correo: " << actual->correoE << endl;
        actual = actual->siguiente;
    }
}


