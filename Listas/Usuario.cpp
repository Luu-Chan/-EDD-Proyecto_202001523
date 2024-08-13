//
// Created by linkm on 9/08/2024.
//

#include "../Headers/Usuario.h"
#include <iostream>

using namespace std;

Usuario::Usuario(int id, string name, string apelli, string fechaNa, string mail, string pass )
    : id(id), nombre(name), apellido(apelli), fechaN(fechaNa), correoE(mail), pass(pass), siguiente(nullptr) {}
