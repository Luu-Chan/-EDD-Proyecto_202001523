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

    json entrada = json::parse(archivo);

    int contador = list.obtenerSize() + 1;
    for (const auto& item : entrada) {

        std::string nombres = item["nombres"];
        std::string apellidos = item["apellidos"];
        std::string fechaNacimiento = item["fecha_de_nacimiento"];
        std::string correo = item["correo"];
        std::string contrasena = item["contraseña"];
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

    json entrada = json::parse(archivo);
    std::cout << "Archivo JSON leído correctamente." << std::endl;

    for (const auto& item : entrada) {

        std::string emisor = item["emisor"];
        std::string receptor = item["receptor"];
        std::string estado = item["estado"];

        Usuario* userE = list.buscarU(emisor);
        Usuario* userR = list.buscarU(receptor);
        if (userR != nullptr) {
            if ( estado == "PENDIENTE") {
               userE->enviarSolicitud(userE,userR);
            }
            if(estado == "ACEPTADA") {
                userE->enviarSolicitud(userE,userR);
                userR->aceptarSolicitud();
            }
            if(estado == "RECHAZADA") {
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

    json entrada = json::parse(archivo);

    for (const auto& item : entrada) {

        std::string correo = item["correo"];
        std::string contenido = item["contenido"];
        std::string fecha = item["fecha"];
        std::string hora = item["hora"];
        listP.agregarPublicacionM(correo,contenido,fecha,hora);
    }

    cout << "Publicaciones cargadas correctamente!\n" << endl;
}
