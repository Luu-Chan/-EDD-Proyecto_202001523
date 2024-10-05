#include "user.h"
#include <string>


user::user(const std::string& nombre, const std::string& apellido, const std::string& fechaN, const std::string& correoE,
           const std::string& pass): nombre(nombre), apellido(apellido), fechaN(fechaN),
    correoE(correoE), pass(pass) {}


    std::string user::getnombre() const {
        return nombre;
    }

    std::string user::getapellido() const {
        return apellido;
    }

    std::string user::getfechaN() const {
        return fechaN;
    }

    std::string user::getcorreoE() const {
        return correoE;
    }

    std::string user::getpass() const {
        return pass;
    }

    void user::setnombre(const std::string& nombre) {
        this->nombre = nombre;
    }

    void user::setapellido(const std::string& apellido) {
        this->apellido = apellido;
    }

    void user::setfechaN(const std::string& fechaN) {
        this->fechaN = fechaN;
    }

    void user::setcorreoE(const std::string& correoE) {
        this->correoE = correoE;
    }

    void user::setpass(const std::string& pass) {
        this->pass = pass;
    }

   std::string user::mostrarInfo(){
        std::string info =  "Nombre: " + nombre + " " + apellido + "\n"
                  + "Fecha de Nacimiento: " + fechaN + "\n"
                  + "Correo Electrónico: " + correoE + "\n";
       return info;
        }

    std::string user::mostrarInfoG(){
       std::string info = "Correo Electrónico: " + correoE + " Nombre: " + nombre + " " + apellido;


       return info;
   }



   // Enviar solicitud de amistad
   void user::enviarSolicitud(user* receptor) {
       if (!enviadas.find(receptor->getcorreoE())) {
           enviadas.add(receptor->getcorreoE());
           receptor->recibirSolicitud(correoE);
       }
   }

   // Recibir solicitud de amistad
   void user::recibirSolicitud(const std::string& email) {
       recibidas.push(email);
   }

   // Rechazar solicitud de amistad
   void user::rechazarSolicitud() {
       if (!recibidas.isEmpty()) {
           recibidas.pop();
       }
   }

   // Mostrar solicitudes enviadas
   std::string user::mostrarSolicitudesEnviadas() {
       return enviadas.display();
   }

   // Mostrar solicitudes recibidas
   std::string user::mostrarSolicitudesRecibidas() {
      return recibidas.display();
   }
