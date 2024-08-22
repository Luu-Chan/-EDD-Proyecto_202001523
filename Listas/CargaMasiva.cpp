//
// Created by linkm on 21/08/2024.
//
#include "../Headers/CargaMasiva.h"
#include "../Headers/Linkedlist.h"
#include "../Headers/ListPubliacion.h"
#include "../Headers/Usuario.h"
extern Linkedlist list;
extern ListaPublicaciones listP;
#include "../Headers/nlohmann/json.hpp"
#include <string>
#include <fstream>
#include <iostream>

using namespace std;
using json = nlohmann::json;

void cargaUsuarios(const string& path) {

    std::ifstream archivo(path);
    if (!archivo.is_open()) {
        cout << "No se pudo abrir el archivo: " << path << endl;
        return;
    }

    json entrada;
    archivo >> entrada;

    if (!entrada.contains("usuarios") || !entrada["usuarios"].is_array()) {
        cout << "El archivo Json no es valido!!!" << endl;
        return;
    }

    int contador = list.obtenerSize() + 1;
    for (const auto& usuario : entrada["usuarios"]) {
        if (!usuario.contains("nombres") || !usuario.contains("apellidos") ||
            !usuario.contains("fecha_de_nacimiento") || !usuario.contains("correo") || !usuario.contains("contraseña")) {
             cout << "El usuario no puede ser agregado." << endl;
            continue;
            }
        std::string nombres = usuario["nombres"];
        std::string apellidos = usuario["apellidos"];
        std::string fechaNacimiento = usuario["fecha_de_nacimiento"];
        std::string correo = usuario["correo"];
        std::string contrasena = usuario["contraseña"];
        int idactual = contador++; //Para incrementar el id conforme se van agregando
        Usuario* user = new Usuario(idactual, nombres, apellidos, fechaNacimiento, correo, contrasena);
        list.agregar(user);
    }

    cout << "Usuarios cargados correctamente!\n" << endl;
}

void cargaSolicitud(const string& path) {

    std::ifstream archivo(path);
    if (!archivo.is_open()) {
        std::cerr << "No se pudo abrir el archivo: " << path << std::endl;
        return;
    }

    json entrada;
    archivo >> entrada;

    std::cout << "Archivo JSON leído correctamente." << std::endl;

    if (!entrada.contains("solicitudes") || !entrada["solicitudes"].is_array()) {
        std::cerr << "El archivo Json no es valido!!." << std::endl;
        return;
    }

    for (const auto& solicitud : entrada["solicitudes"]) {
        if (!solicitud.contains("emisor") || !solicitud.contains("receptor") || !solicitud.contains("estado")) {
            std::cerr << "La solicitud no puede ser realizada." << std::endl;
            continue;
        }

        std::string emisor = solicitud["emisor"];
        std::string receptor = solicitud["receptor"];
        std::string estado = solicitud["estado"];

        Usuario* userE = list.buscarU(emisor);
        Usuario* userR = list.buscarU(receptor);
        if (userR != nullptr) {
            if ( estado == "Pendiente") {
               userE->enviarSolicitud(userE,userR);
            }
            if(estado == "Aceptada") {
                userE->enviarSolicitud(userE,userR);
                userR->aceptarSolicitud();
            }
            if(estado == "Rechazada") {
                userE->enviarSolicitud(userE,userR);
                userR->rechazarSolicitud();
            }
        } else {
            std::cerr << "Usuario receptor no encontrado: " << receptor << std::endl;
        }
    }

    cout << "Solicitudes cargadas correctamente! \n" << endl;
}

void cargaPubli(const string& path) {

    std::ifstream archivo(path);
    if (!archivo.is_open()) {
        cout << "No se pudo abrir el archivo: " << path << endl;
        return;
    }

    json entrada;
    archivo >> entrada;

    if (!entrada.contains("publicaciones") || !entrada["publicaciones"].is_array()) {
        cout << "El archivo Json no es valido!!!" << endl;
        return;
    }
    for (const auto& publicacion : entrada["publicaciones"]) {
        if (!publicacion.contains("correo") || !publicacion.contains("contenido") ||
            !publicacion.contains("fecha") || !publicacion.contains("hora")) {
            cout << "La publicacion no puede ser realizada." << endl;
            continue;
            }
        std::string correo = publicacion["correo"];
        std::string contenido = publicacion["contenido"];
        std::string fecha = publicacion["fecha"];
        std::string hora = publicacion["hora"];
        listP.agregarPublicacionM(correo,contenido,fecha,hora);
    }

    cout << "Publicaciones cargadas correctamente!\n" << endl;
}
