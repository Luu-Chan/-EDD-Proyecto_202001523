//
// Created by linkm on 15/08/2024.
//
#include "../Headers/menuUser.h"
#include "../Headers/Linkedlist.h"
#include <iostream>
extern Linkedlist list;
using namespace std;
void menuUser(const string& correoE) {

    int opcion;
    do {
        cout << "\n ******************** BIENVENIDO *******************\n" << endl;
        cout << "1. Perfil" << endl;
        cout << "2. Solicitudes" << endl;
        cout << "3. Publicaciones" << endl;
        cout << "4. Reportes" << endl;
        cout << "5. Salir" << endl;
        cout << "Seleccione una opción: ";
        cin >> opcion;

        switch(opcion) {
            case 1:
                cout << "Seleccione algo" << endl;
            cout << " 1. Ver mi Perfil" << endl;
            cout << " 2. Eliminar mi cuenta" << endl;
            cout << " 3. Regresar" << endl;
            cout << ">>>>>>>>>" << endl;
            int opc ;
            cin >> opc;

                switch (opc) {
                    case 1:
                        cout << "********* Mi perfil ********* \n" << endl;
                    list.perfil(correoE);

                    break;
                    case 2 :
                        cout << "Desea eliminar su cuenta? S/N" << endl;
                    break;
                    case 3:
                        break;
                    default:
                        cout << "Opcion no valida" << endl;
                }

            break;
            case 2:
                cout << "Solicitudes \n" << endl;
            break;
            case 3:
                cout << "Publicaciones \n" << endl;
            break;
            case 4: {
                cout << "Reportes \n" << endl;
                break;
            }
            case 5:
                cout << "Regresando" << endl;
            break;
            default:
                cout << "Opción no válida" << endl;
        }
    } while(opcion != 5);
}
