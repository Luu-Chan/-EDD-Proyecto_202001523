//
// Created by linkm on 15/08/2024.
//
#include "../Headers/menuUser.h"
#include <iostream>

using namespace std;
void menuAldo() {
    int opcion;
    do {
        cout << "MODULO Usuario" << endl;
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
