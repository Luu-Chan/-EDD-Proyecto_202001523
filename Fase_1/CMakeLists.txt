cmake_minimum_required(VERSION 3.28)
project(Fase_1)

set(CMAKE_CXX_STANDARD 17)

add_executable(Fase_1 main.cpp
        Headers/Usuario.h
        Listas/Usuario.cpp
        Listas/Linkedlist.cpp
        Headers/Linkedlist.h
        Listas/menuUser.cpp
        Headers/menuUser.h
        Headers/SolicitudAmistad.h
        Listas/ListaSolicitud.cpp
        Headers/ListaSolicitud.h
        Headers/NodoS.h
        Headers/Publicacion.h
        Headers/ListPubliacion.h
        Listas/ListPublicacion.cpp
        Headers/CargaMasiva.h
        Listas/CargaMasiva.cpp
)
