//
// Created by linkm on 15/08/2024.
//
#include "../Headers/menuUser.h"
#include "../Headers/Linkedlist.h"
//#include "../Headers/Usuario.h"

#include <iostream>
extern Linkedlist list;
using namespace std;


void menuUser(const string& correoE) {
    Usuario* logger = list.buscarU(correoE);
    int opcion;
    do {
        cout << "\n ******************** BIENVENIDO *******************\n" << endl;
        cout << "1. Perfil \n" << endl;
        cout << "2. Enviar Solicitud \n" << endl;
        cout << "3. Administrar Solicitudes \n" << endl;
        cout << "4. Publicaciones" << endl;
        cout << "5. Reportes" << endl;
        cout << "6. Salir" << endl;
        cout << "Seleccione una opción: ";
        cin >> opcion;

        switch(opcion) {
            case 1: {
                cout << "Seleccione algo" << endl;
                cout << " 1. Ver mi Perfil" << endl;
                cout << " 2. Eliminar mi cuenta" << endl;
                cout << " 3. Regresar" << endl;
                cout << ">>>>>>>>>" << endl;
                int opc ;
                cin >> opc;

                switch (opc) {
                    case 1: {
                        cout << "********* Mi perfil ********* \n" << endl;
                        list.perfil(correoE);
                    }break;
                    case 2 : {
                        string dell ;
                        cout << "Desea eliminar su cuenta? S/N" << endl;
                        cin >> dell;
                        if (dell == "S") {
                            list.eliminar(correoE);
                            cout << "¡¡¡¡¡SU USUARIO A SIDO BORRADO!!! \n" << endl;
                            return;
                        }
                        cout << "Gracias por seguir en nuestra plataforma\n" << endl;
                    }break;

                    case 3: {
                    }break;
                    default:
                        cout << "Opcion no valida" << endl;
                }
            }break;

            case 2: {
                cout << "Listado de Personas \n" << endl;

                string persona;
                list.imprimirLista();

                cout << "Ingrese Correo de la persona a quien desee agregar: \n" << endl;
                cin >> persona;
                Usuario* receptor = list.buscarU(persona);

                logger->enviarSolicitud(logger,receptor);
                cout << "Ahora espere a que hacepte su solicitud. \n" << endl;
            }break;

            case 3: {
                cout << "Mostrando solicitudes:  \n" << endl;
                logger->mostrarSolicitudMasReciente();
                cout << "1. Aceptar Solicitud "<< endl;
                cout << "2. Rechazar Solicitud "<< endl;
                cout << "3. Regresar "<< endl;
                int selec ;
                cin >> selec;

                switch (selec) {
                    case  1: {
                        logger->aceptarSolicitud();

                    }break;

                    case 2: {
                        logger->rechazarSolicitud();
                    }break;

                    case 3:
                        cout << "Regresando al Menu Principal \n "<< endl;
                    default:
                        cout << " Opcion no valida!"<< endl;
                }
            }break;
            case 4: {
                cout << "Reportes \n" << endl;
                break;
            }
            case 5: {
                cout << "Regresando" << endl;
            }break;
            default:
                cout << "Opción no válida" << endl;
        }
    } while(opcion != 6);
}


void menuAdmin() {
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


