#include <iostream>
#include <windows.h>
#include "Headers/Linkedlist.h"
#include "Headers/Usuario.h"
#include "Headers/ListPubliacion.h"
#include <limits>
#include <string>

Linkedlist list;
ListaPublicaciones listP;

using namespace std;

void mostrarMenu() {
    cout << "****************************" << endl;
    cout << "         EDD FASE 1 :(         " << endl;
    cout << "****************************" << endl;
    cout << "1. Iniciar sesión" << endl;
    cout << "2. Registrarse" << endl;
    cout << "3. Información" << endl;
    cout << "4. Salir" << endl;
    cout << "****************************\n" << endl;
    cout << "Seleccione una opción: ";
}

string nombre;
string apellidos;
string mail;
string pass;
string fecha;

int main() {
    SetConsoleOutputCP(CP_UTF8);

    Usuario* prueba = new Usuario(0, "Skibidi", "Toilet", "12/12/2012", "admin@gmail.com", "EDD2S2024");
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
            case 1: {

                cout << "Iniciando sesión..." << endl;
                cout << "Ingrese su Correo" << endl;
                cin >> mail;
                cout << "Ingrese su Contraseña" << endl;
                cin >> pass;
                list.inicioSesion(mail,pass);
            }break;

            case 2:
                cout << "Registrando usuario..." << endl;

            cout << "Ingrese sus nombres: ";
            cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Limpiar el buffer para que no pete
            getline(cin, nombre);
            cout << "Ingrese sus apellidos: " << endl;
            getline(cin, apellidos);
            cout << "Ingrese su fecha de nacimiento; DD/MM/AA: ";
            getline(cin, fecha);
            cout << "Ingrese su correo electrónico: " <<endl;
            getline(cin, mail);
            cout << "Ingrese su contraseña: " << endl;
            getline(cin, pass);
            list.registrarU(nombre, apellidos, fecha, mail, pass);
            break;

            case 3:
                cout << "Mostrando información...\n" << endl;
            cout << "Nombre: Luis Gabriel Lopez Polanco "<< endl;
            cout << "Carnet: 202001523 "<< endl;
            cout << "Carrera: Ingenieria en Ciencias y Sistemas "<< endl;
            cout << "Estructuras de Datos 2024 S2"<< endl;
            cout << " \n"<< endl;
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
