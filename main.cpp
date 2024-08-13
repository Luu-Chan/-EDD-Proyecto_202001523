#include <iostream>
#include <windows.h>

#include "Headers/Linkedlist.h"
#include "Headers/Usuario.h"
using namespace std;

void mostrarMenu() {
    cout << "****************************" << endl;
    cout << "         MENU LOGIN         " << endl;
    cout << "****************************" << endl;
    cout << "1. Iniciar sesión" << endl;
    cout << "2. Registrarse" << endl;
    cout << "3. Información" << endl;
    cout << "4. Salir" << endl;
    cout << "****************************" << endl;
    cout << "Seleccione una opción: ";
}



int main() {
    SetConsoleOutputCP(CP_UTF8);

    Linkedlist list;

    Usuario* prueba = new Usuario(1, "Luis", "Lopez", "1111/11/11", "hotmail", "123");
    list.agregar(prueba);
    list.imprimirLista();


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
            break;
            case 2:
                cout << "Registrando usuario..." << endl;
            break;
            case 3:
                cout << "Mostrando información..." << endl;
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
