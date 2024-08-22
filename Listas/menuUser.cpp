//
// Created by linkm on 15/08/2024.
//
#include "../Headers/menuUser.h"
#include "../Headers/Linkedlist.h"
#include "../Headers/ListPubliacion.h"
#include "../Headers/CargaMasiva.h"
#include <iostream>
#include <limits>

extern ListaPublicaciones listP;
extern Linkedlist list;
using namespace std;


void menuUser(const string& correoE) {
    Usuario* logger = list.buscarU(correoE);
    int opcion;
    do {
        cout << "\n ******************** BIENVENIDO *******************\n" << endl;
        cout << "1. Perfil " << endl;
        cout << "2. Enviar Solicitud " << endl;
        cout << "3. Administrar Solicitudes " << endl;
        cout << "4. Publicaciones" << endl;
        cout << "5. Reportes" << endl;
        cout << "6. Salir" << endl;
        cout << "Seleccione una opción: ";
        cin >> opcion;

        switch(opcion) {
            case 1: {
                cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Limpiar el buffer para que no pete
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
                        cin.ignore(numeric_limits<streamsize>::max(), '\n');
                    }break;
                    case 2 : {
                        string dell ;
                        cout << "Desea eliminar su cuenta? S/N" << endl;
                        cin >> dell;
                        if (dell == "S") {
                            list.eliminar(correoE);
                            cout << "¡¡¡¡¡SU USUARIO A SIDO BORRADO!!! \n" << endl;
                            cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Limpiar el buffer para que no pete
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
                cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Limpiar el buffer para que no pete

            }break;

            case 3: {
                cout << "********** Mostrando solicitudes:  ********\n" << endl;
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
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                int publi;
                cout << "************ Publicaciones ***************\n" << endl;
                cout << "1. Agregar Publicacion "<< endl;
                cout << "2. Eliminar Publicacion "<< endl;
                cout << "3. Ver Publicaciones "<< endl;
                cout << "4. Regresar "<< endl;
                cin >> publi;

                switch (publi) {
                    case 1: {
                        string contenido;
                        // Vaciamos el buffer de entrada
                        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                        cout << "Ingrese su texto "<< endl;
                        getline(cin,contenido);
                        listP.agregarPublicacion(correoE,contenido);
                        // Vaciamos el buffer de entrada porque el texto llena el buffer
                        std::cin.ignore(numeric_limits<std::streamsize>::max(), '\n');
                    }break;

                    case 2: {
                        cout << "Eliminando publicaciones.... "<< endl;
                    }break;

                    case 3: {
                        cout << "Cargando publicaciones.... \n "<< endl;
                        std::cin.ignore(numeric_limits<std::streamsize>::max(), '\n');
                        listP.navegarPublicaciones();
                    }break;

                    case 4:{}
                        break;
                    default: {
                        cout << "Opcion no valida... "<< endl;
                    }
                }
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
        cout << "************ MODULO ADMINISTRADOR *************\n" << endl;
        cout << "1. Carga de usuarios" << endl;
        cout << "2. Carga de relaciones" << endl;
        cout << "3. Carga de publicaciones" << endl;
        cout << "4. Gestionar usuarios" << endl;
        cout << "5. Reportes" << endl;
        cout << "6. Salir" << endl;
        cout << "Seleccione una opción: ";
        cin >> opcion;

        switch(opcion) {
            case 1: {
                std::cin.ignore(numeric_limits<std::streamsize>::max(), '\n');
                cout << "Carga de usuarios\n" << endl;
                string ruta;
                cout << "Ingrese la ruta del Archivo" << endl;
                getline(cin,ruta );
                cargaUsuarios(ruta);
            }break;
            case 2: {
                cout << "Carga de Solicitudes" << endl;
                std::cin.ignore(numeric_limits<std::streamsize>::max(), '\n');
                string ruta;
                cout << "Ingrese la ruta del Archivo" << endl;
                getline(cin,ruta);
                cargaSolicitud(ruta);
            }break;
            case 3: {
                cout << "Carga de publicaciones \n" << endl;
                std::cin.ignore(numeric_limits<std::streamsize>::max(), '\n');
                string ruta;
                cout << "Ingrese la ruta del Archivo" << endl;
                getline(cin,ruta);
                cargaPubli(ruta);
            }break;
            case 4: {
                std::cin.ignore(numeric_limits<std::streamsize>::max(), '\n');
                string user;
                cout << "1. Eliminar usuarios" << endl;
                list.imprimirLista();
                cout << "Ingrese el correo del usuario a Eliminar" << endl;
                getline(cin, user);
                list.eliminar(user);
                cout << "Usuario eliminado!!\n"<< endl;
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