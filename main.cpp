#include <iostream>
#include <windows.h>
#include "Headers/Linkedlist.h"
#include "Headers/Usuario.h"
#include <limits>
#include <string>

using namespace std;

void mostrarMenu() {
    cout << "****************************" << endl;
    cout << "         EDD FASE 1 :(         " << endl;
    cout << "****************************" << endl;
    cout << "1. Iniciar sesión" << endl;
    cout << "2. Registrarse" << endl;
    cout << "3. Información" << endl;
    cout << "4. Salir" << endl;
    cout << "****************************" << endl;
    cout << "Seleccione una opción: ";
}

Linkedlist list;
string nombre;
string apellidos;
string mail;
string pass;
string fecha;

int main() {
    SetConsoleOutputCP(CP_UTF8);


    Usuario* prueba = new Usuario(1, "Skibidi", "Toilet", "1111/11/11", "admin", "edd");
    list.agregar(prueba);


    int opcion;
    do {
        mostrarMenu();
        cin >> opcion;

        if (cin.fail()) {
            cin.clear(); // Limpia el estado del flujo
            cin.ignore(1000, '\n'); // Ignora los caracteres hasta la nueva línea
            opcion = 0; // Asigna un valor fuera del rango válido
        }

        switch(opcion) {
            case 1:
                cout << "Iniciando sesión..." << endl;
                cout << "Ingrese su Correo" << endl;
                cin >> mail;
                cout << "Ingrese su Contraseña" << endl;
                cin >> pass;
                list.inicioSesion(mail,pass);
            break;

            case 2:
                cout << "Registrando usuario..." << endl;

            cout << "Ingrese sus nombres: ";
            cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Limpiar el buffer
            getline(cin, nombre);
            cout << "Ingrese sus apellidos: ";
            getline(cin, apellidos);
            cout << "Ingrese su fecha de nacimiento; DD/MM/AA: ";
            getline(cin, fecha);
            cout << "Ingrese su correo electrónico: ";
            getline(cin, mail);
            cout << "Ingrese su contraseña: ";
            getline(cin, pass);
            list.registrarU(nombre, apellidos, fecha, mail, pass);
            break;

            case 3:
                cout << "Mostrando información..." << endl;
                list.imprimirLista();
            break;
            case 4:
                cout << "Saliendo del programa..." << endl;
            break;
            default:
                cout << "Opción no válida." << endl;
        }

        cout << endl;

    } while(opcion != 4);

    return 0;
}
