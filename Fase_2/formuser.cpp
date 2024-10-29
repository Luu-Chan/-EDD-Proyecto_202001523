#include "formuser.h"
#include "mainwindow.h"
#include "ui_formuser.h"
#include "QMessageBox"
#include "qfiledialog.h"

formUser::formUser(QWidget *parent, arbolAVL *tree, ListaDoble *list, ABB *abb, const QString &correoUser, Graph *g)
    : QDialog(parent)
    , ui(new Ui::formUser)
    , tree(tree)
    , list(list)
    , abb(abb)
    ,correoUser(correoUser)
    ,g(g)

{
    ui->setupUi(this);
}

formUser::~formUser()
{
    delete ui;
}

void formUser::setcorreoUser(const QString& correoE)
{
    correoUser = correoE;
}

void formUser::on_pushButton_2_clicked()
{
    ui->textsolicitudes->clear();
    std::string suger =  g->displayFriends(correoUser.toStdString());
    QString add3 = QString::fromStdString(suger);
    ui->textsolicitudes->append(add3);


}

void formUser::on_salir_clicked()
{
    this->close();
    qobject_cast<MainWindow*>(parent())->show();
}


void formUser::on_pushButton_clicked()
{
    ui->textsolicitudes->clear();
    std::string suger =  g->suggestFriends(correoUser.toStdString());
    QString add3 = QString::fromStdString(suger);
    ui->textsolicitudes->append(add3);

}


void formUser::on_mostrar_clicked()
{
    ui->infousuarioA->clear();
    user* found = tree->searchU(correoUser.toStdString());
    if (found){
        std::string text = found->mostrarInfo();
        QString add = QString::fromStdString(text);
        ui->infousuarioA->append(add);
    }
}


void formUser::on_eliminar_clicked()
{
    tree->eliminar(correoUser.toStdString());
    QMessageBox::warning(this, "Alerta", "Usuario Eliminado.");
    this->close();
    qobject_cast<MainWindow*>(parent())->show();
}


void formUser::on_buscarFe_clicked()
{
    ui->textPubli->clear();

    QString text = ui->textofecha->text();
    QString add = QString::fromStdString(list->buscarPorFecha(text.toStdString()));

    ui->textPubli->append(add);
}


void formUser::on_inlimit_clicked()
{
    ui->textPubli->clear();

    if(ui->limite->text() != ""){

        std::string text = abb->mostrarInordenLimitado(ui->limite->text().toInt());
        QString add = QString::fromStdString(text);
        ui->textPubli->append(add);

    }
    else{

        QMessageBox::warning(this, "Alerta", "Ingrese un Limite.");
    }


}


void formUser::on_poslimit_clicked()
{
    ui->textPubli->clear();

    if(ui->limite->text() != ""){

        std::string text = abb->mostrarPostordenLimitado(ui->limite->text().toInt());
        QString add = QString::fromStdString(text);
        ui->textPubli->append(add);

    }
    else{

        QMessageBox::warning(this, "Alerta", "Ingrese un Limite.");
    }

}


void formUser::on_prelimit_clicked()
{
    ui->textPubli->clear();

    if(ui->limite->text() != ""){

        std::string text = abb->mostrarPreordenLimitado(ui->limite->text().toInt());
        QString add = QString::fromStdString(text);
        ui->textPubli->append(add);

    }
    else{

        QMessageBox::warning(this, "Alerta", "Ingrese un Limite.");
    }

}


void formUser::on_verco_clicked()
{
    ui->textPubli->clear();
    std::string text = list->mostrarComentarios(ui->fechapu->text().toStdString(), ui->horapu->text().toStdString());
    QString add = QString::fromStdString(text);
    ui->textPubli->append(add);
}


void formUser::on_comentarbutton_clicked()
{
    if(ui->fechapu->text().toStdString() != "" && ui->horapu->text().toStdString() != ""){
    time_t tiempoActual = time(nullptr);
    tm* tiempoLocal = localtime(&tiempoActual);

    // Obtener la fecha con formato "DD/MM/AA"
    char fecha[9];  // Formato "DD/MM/AA" (8 caracteres + '\0')
    strftime(fecha, sizeof(fecha), "%d/%m/%y", tiempoLocal);

    // Obtener la hora con formato "HH:MM"
    char hora[6];  // Formato "HH:MM" (5 caracteres + '\0')
    strftime(hora, sizeof(hora), "%H:%M", tiempoLocal);


    ui->textPubli->clear();
    list->agregarComentario(list->buscarCorreoPorHora(ui->fechapu->text().toStdString(), ui->horapu->text().toStdString()),
                                ui->fechapu->text().toStdString(), ui->horapu->text().toStdString(), Comentario(correoUser.toStdString(),
                                ui->textocom->text().toStdString() ,fecha, hora));

    std::string text = list->mostrarComentarios(ui->fechapu->text().toStdString(), ui->horapu->text().toStdString());
    QString add = QString::fromStdString(text);
    ui->textPubli->append(add);
    }
    else{
         QMessageBox::warning(this, "Alerta", "Asegurese de rellenar los campos");

    }
}


void formUser::on_agregarP_clicked()
{
    time_t tiempoActual = time(nullptr);
    tm* tiempoLocal = localtime(&tiempoActual);
    // Obtener la fecha con formato "DD/MM/AA"
    char fecha[9];  // Formato "DD/MM/AA" (8 caracteres + '\0')
    strftime(fecha, sizeof(fecha), "%d/%m/%y", tiempoLocal);

    // Obtener la hora con formato "HH:MM"
    char hora[6];  // Formato "HH:MM" (5 caracteres + '\0')
    strftime(hora, sizeof(hora), "%H:%M", tiempoLocal);

    QString path = QFileDialog::getOpenFileName(this, "Abrir imagen", "");
    if (path.isEmpty()) {
        qDebug() << "No se seleccionó ningún archivo.";
        return;
    }

    list->insertarFinal(correoUser.toStdString(), ui->contenidoP->text().toStdString(), fecha, hora, path.toStdString());
    abb->insertarPublicacion(correoUser.toStdString(), ui->contenidoP->text().toStdString(), fecha, hora, path.toStdString());
    QMessageBox::information(this, "", "Se agrego su publicacion");


}


void formUser::on_buscar_clicked()
{
    ui->encontrado->clear();

    user* found = tree->searchU(ui->correoBuscar->text().toStdString());
    if (found){
        std::string text = found->mostrarInfo();
        QString add = QString::fromStdString(text);
        ui->encontrado->append(add);
    }
}


void formUser::on_toppubli_clicked()
{
    ui->textotops->clear();

    std::string text = abb->top3FechasConMasPublicaciones();
    QString add = QString::fromStdString(text);
    ui->textotops->append(add);
}


void formUser::on_topcomen_clicked()
{
    ui->textotops->clear();

    std::string text = list->top3PublicacionesConMasComentarios();
    QString add = QString::fromStdString(text);
    ui->textotops->append(add);

}


void formUser::on_pushButton_4_clicked()
{
    std::string nombre = "grafico_fechas";
    abb->graficarABBConListaFechaEspecifica(nombre, ui->textgrafico->text().toStdString() );
    std::string path = "C:\\Users\\linkm\\OneDrive\\Escritorio\\PROYECTOS S2 2024\\ESTRUCTURA DE DATOS\\-EDD-Proyecto_202001523\\Fase_2\\build\\Desktop_Qt_6_7_2_MinGW_64_bit-Release\\grafico_fechas.png" ;
    QPixmap pixmap(QString::fromStdString(path));
    QPixmap scaledPixmap = pixmap.scaled(600, 600, Qt::KeepAspectRatio, Qt::SmoothTransformation);
    ui->graficobst->setPixmap(scaledPixmap);
}


void formUser::on_eliminarpubli_clicked()
{
    list->eliminarPublicacionMasReciente(correoUser.toStdString());
    abb->eliminarPublicacion(correoUser.toStdString());
    QMessageBox::information(this, "", "Se elimino su publicacion");

}


void formUser::on_enviarsol_clicked()
{
    if(ui->correoBuscar->text() != ""){
        user* usuarioE = tree->searchU(correoUser.toStdString());
        user* usuarioR = tree->searchU(ui->correoBuscar->text().toStdString());
        std::string rep =  ui->correoBuscar->text().toStdString();

        usuarioE->enviarSolicitud(usuarioR);
        usuarioR->recibirSolicitud(correoUser.toStdString());
        g->addFriendship(correoUser.toStdString(), rep);
        QMessageBox::information(this, "", "Se envio la solicitud" );


    }else{

    QMessageBox::warning(this, "Alerta", "Ingrese un usuario Receptor.");
    }
}


void formUser::on_mostrarsol_clicked()
{
    ui->textsolicitudes->clear();
    user* usuarioE = tree->searchU(correoUser.toStdString());
    std::string texte = usuarioE->mostrarSolicitudesEnviadas();
    std::string textr = usuarioE->mostrarSolicitudesRecibidas();
    QString add = QString::fromStdString(texte);
    QString add2 = QString::fromStdString(textr);
    ui->textsolicitudes->append(add);
    ui->textsolicitudes->append(add2);




}


void formUser::on_aceptars_clicked()
{
    user* usuarioE = tree->searchU(correoUser.toStdString());
    usuarioE->rechazarSolicitud();
    QMessageBox::information(this, "", "Se Acepto la solicitud");

}


void formUser::on_rechazars_clicked()
{
    user* usuarioE = tree->searchU(correoUser.toStdString());
    usuarioE->rechazarSolicitud();
    QMessageBox::information(this, "", "Se Rechazo la solicitud");

}


void formUser::on_pushButton_3_clicked()
{
    std::string nombre = "sugerencias";
    g->generateHighlightedGraph(nombre, correoUser.toStdString());
    std::string path = "C:\\Users\\linkm\\OneDrive\\Escritorio\\PROYECTOS S2 2024\\ESTRUCTURA DE DATOS\\-EDD-Proyecto_202001523\\Fase_2\\build\\Desktop_Qt_6_7_2_MinGW_64_bit-Release\\sugerencias.png" ;
    QPixmap pixmap(QString::fromStdString(path));
    QPixmap scaledPixmap = pixmap.scaled(352, 352, Qt::KeepAspectRatio, Qt::SmoothTransformation);
    ui->label_8->setPixmap(scaledPixmap);
}



void formUser::on_pushButton_5_clicked()
{
    QString nombre = ui->nombres->text();
    QString apellido = ui->apellidos->text();
    QString pass = ui->pass->text();
    QString fecha = ui->dateEdit->date().toString();

    if (nombre.isEmpty() || apellido.isEmpty() || pass.isEmpty() || fecha.isEmpty()) {
        QMessageBox::warning(this, "Error", "Rellene todos los campos.");
        return;
    }

    user* nuevo = new user(nombre.toStdString(), apellido.toStdString(), fecha.toStdString(), correoUser.toStdString(), pass.toStdString());

    tree->editarUsuario(correoUser.toStdString(), *nuevo);
    QMessageBox::warning(this, "Alerta", "Se ha modificado tu Usuario.");

    ui->apellidos->clear();
    ui->nombres->clear();
    ui->pass->clear();
}

