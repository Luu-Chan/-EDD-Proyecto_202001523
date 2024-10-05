#include "cargamasiva.h"
#include "arbolavl.h"
#include <nlohmann/json.hpp>
#include <QFile>
#include <QDebug>
#include <QTextStream>

cargaMasiva::cargaMasiva(arbolAVL* tree, ListaDoble *list, ABB *abb) :
    tree(tree)
    , list(list)
    , abb(abb){}

void cargaMasiva::cargarU(const QString& rutaArchivo) {
    QFile archivo(rutaArchivo);
    if (!archivo.open(QIODevice::ReadOnly | QIODevice::Text)) {
        qDebug() << "No se pudo abrir el archivo:" << rutaArchivo;
        return;
    }

    QTextStream in(&archivo);
    QString contenido = in.readAll();
    archivo.close();
    nlohmann::json j = nlohmann::json::parse(contenido.toStdString());


    for (const auto& usuarioJson : j) {
        qDebug() << "inicia carga" ;
        QString nombres = QString::fromStdString(usuarioJson["nombres"]);
        QString apellidos = QString::fromStdString(usuarioJson["apellidos"]);
        QString fechaNacimiento = QString::fromStdString(usuarioJson["fecha_de_nacimiento"]);
        QString correo = QString::fromStdString(usuarioJson["correo"]);
        QString contrasena = QString::fromStdString(usuarioJson["contraseña"]);

        qDebug() << "Se agrega el usuario" << correo;
        user* usuario = new user(nombres.toStdString(), apellidos.toStdString(), fechaNacimiento.toStdString(),
                                 correo.toStdString(), contrasena.toStdString());
        tree->insertU(usuario);
        qDebug() << " se agrego:  "<< correo ;
    }
    qDebug() << "carga completa" ;
}


void cargaMasiva::cargarP(const QString &ruta){

    QFile archivo(ruta);
    if (!archivo.open(QIODevice::ReadOnly | QIODevice::Text)) {
        qDebug() << "No se pudo abrir el archivo:" << ruta;
        return;
    }

    QTextStream in(&archivo);
    QString contenido = in.readAll();
    archivo.close();
    nlohmann::json j = nlohmann::json::parse(contenido.toStdString());


    for (const auto& publicacionJson : j) {
        QString correo = QString::fromStdString(publicacionJson["correo"]);
        QString contenido = QString::fromStdString(publicacionJson["contenido"]);
        QString fecha = QString::fromStdString(publicacionJson["fecha"]);
        QString hora = QString::fromStdString(publicacionJson["hora"]);
        QString pathimagen = "";

        qDebug() << "Insertando publicación - Correo:" << correo << ", Contenido:" << contenido << ", Fecha:" << fecha << ", Hora:" << hora;

        // Insertar la publicación en la lista doblemente enlazada
        abb->insertarPublicacion(correo.toStdString(), contenido.toStdString(), fecha.toStdString(), hora.toStdString(), pathimagen.toStdString());
        list->insertarFinal(correo.toStdString(), contenido.toStdString(), fecha.toStdString(), hora.toStdString(), pathimagen.toStdString());

        qDebug() << "Publicacion agregada";


        for (const auto& comentarioJson : publicacionJson["comentarios"]) {
            QString correoComentario = QString::fromStdString(comentarioJson["correo"]);
            QString comentario = QString::fromStdString(comentarioJson["comentario"]);
            QString fechaComentario = QString::fromStdString(comentarioJson["fecha"]);
            QString horaComentario = QString::fromStdString(comentarioJson["hora"]);

            qDebug() << "Insertando comentario - Correo:" << correoComentario << ", Comentario:" << comentario << ", Fecha:" << fechaComentario << ", Hora:" << horaComentario;

            // Insertar el comentario en el árbol B de comentarios
            list->agregarComentario(correo.toStdString(), fecha.toStdString(), hora.toStdString(),
                                    Comentario(correoComentario.toStdString(), comentario.toStdString(), fechaComentario.toStdString(), horaComentario.toStdString()));
        }


        qDebug() << "Se agrego comentario de" << correo << ":";

    }
}

void cargaMasiva::cargarS(const QString& ruta){


    QFile archivo(ruta);
    if (!archivo.open(QIODevice::ReadOnly | QIODevice::Text)) {
        qDebug() << "No se pudo abrir el archivo:" << ruta;
        return;
    }

    QTextStream in(&archivo);
    QString contenido = in.readAll();
    archivo.close();

    qDebug() << "Contenido del archivo JSON:" << contenido;

    // Parsear el contenido JSON
    nlohmann::json j;
    j = nlohmann::json::parse(contenido.toStdString());


    for (const auto& solicitudJson : j) {
        QString emisor = QString::fromStdString(solicitudJson["emisor"]);
        QString receptor = QString::fromStdString(solicitudJson["receptor"]);
        QString estado = QString::fromStdString(solicitudJson["estado"]);

        user* usuarioE = tree->searchU(emisor.toStdString());
        user* usuarioR = tree->searchU(receptor.toStdString());
        if (usuarioE && usuarioR){
            if (estado == "PENDIENTE"){

                usuarioE->enviarSolicitud(usuarioR);
                usuarioR->recibirSolicitud(emisor.toStdString());
                qDebug() << "Solicitud Envidada";

            }
            else if(estado == "ACEPTADA"){
                qDebug() << "Solicitud Aceptada";
            }

        }

    }

}

