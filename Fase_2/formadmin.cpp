#include "formadmin.h"
#include "mainwindow.h"
#include "ui_formadmin.h"
#include <QFileDialog>
#include "qmessagebox.h"

formAdmin::formAdmin(QWidget *parent, arbolAVL* tree, ListaDoble *list, ABB *abb)
    : QDialog(parent)
    , ui(new Ui::formAdmin)
    , tree(tree)
    ,list(list)
    ,abb(abb)

{
    ui->setupUi(this);
    cargarusuario = new cargaMasiva(tree, list, abb);

}

formAdmin::~formAdmin()
{
    delete ui;
    delete cargarusuario;
}

void formAdmin::on_cargarU_clicked()
{
    QString path = QFileDialog::getOpenFileName(this, "Abrir archivo JSON", "", "Archivos JSON (*.json)");
    if (path.isEmpty()) {
        qDebug() << "No se seleccionó ningún archivo.";
        return;
    }

    qDebug() << "Archivo seleccionado para carga masiva de usuarios:" << path;
    cargarusuario->cargarU(path);

}


void formAdmin::on_salirAdmin_clicked()
{
    this->close();

    qobject_cast<MainWindow*>(parent())->show();
}


void formAdmin::on_buscarA_clicked()
{
    ui->infouser->clear();

    user* found = tree->searchU(ui->correoText->text().toStdString());
    if (found){
        std::string text = found->mostrarInfo();
        QString add = QString::fromStdString(text);
        ui->infouser->append(add);
    }
}


void formAdmin::on_eliminar_clicked()
{

    if(ui->correoText->text() != ""){
    tree->eliminar(ui->correoText->text().toStdString());
    list->eliminarPublicacionesPorCorreo(ui->correoText->text().toStdString());
    abb->eliminarPublicacionesPorCorreo(ui->correoText->text().toStdString());
    QMessageBox::warning(this, "Alerta", "Usuario Eliminado.");
    }
    else {QMessageBox::warning(this, "Error", "Introduzca un Correo.");}
}


void formAdmin::on_in_clicked()
{
    ui->infouser->clear();
    std::string text = tree->mostrarInOrder();
    QString add = QString::fromStdString(text);
    ui->infouser->append(add);
}


void formAdmin::on_pushButton_5_clicked()
{
    ui->infouser->clear();
    std::string text = tree->mostrarPreOrder();
    QString add = QString::fromStdString(text);
    ui->infouser->append(add);
}


void formAdmin::on_post_clicked()
{
    ui->infouser->clear();
    std::string text = tree->mostrarPostOrder();
    QString add = QString::fromStdString(text);
    ui->infouser->append(add);
}


void formAdmin::on_cargarP_clicked()
{
    QString path = QFileDialog::getOpenFileName(this, "Abrir archivo JSON", "", "Archivos JSON (*.json)");
    if (path.isEmpty()) {
        qDebug() << "No se seleccionó ningún archivo.";
        return;
    }
    cargarusuario->cargarP(path);

}


void formAdmin::on_pushButton_clicked()
{

    std::string nombre = "publicaciones";
    list->generarGraphviz(nombre);
    std::string path = "C:\\Users\\linkm\\OneDrive\\Escritorio\\PROYECTOS S2 2024\\ESTRUCTURA DE DATOS\\-EDD-Proyecto_202001523\\Fase_2\\build\\Desktop_Qt_6_7_2_MinGW_64_bit-Release\\publicaciones.png" ;
    QPixmap pixmap(QString::fromStdString(path));
    QPixmap scaledPixmap = pixmap.scaled(600, 600, Qt::KeepAspectRatio, Qt::SmoothTransformation);
    ui->reportes->setPixmap(scaledPixmap);
}


void formAdmin::on_pushButton_2_clicked()
{

    std::string nombre = "usuarios";
    tree->graficar(nombre);
    std::string path = "C:\\Users\\linkm\\OneDrive\\Escritorio\\PROYECTOS S2 2024\\ESTRUCTURA DE DATOS\\-EDD-Proyecto_202001523\\Fase_2\\build\\Desktop_Qt_6_7_2_MinGW_64_bit-Release\\usuarios.png" ;
    QPixmap pixmap(QString::fromStdString(path));
    QPixmap scaledPixmap = pixmap.scaled(352, 352, Qt::KeepAspectRatio, Qt::SmoothTransformation);
    ui->label_3->setPixmap(scaledPixmap);
}


void formAdmin::on_pushButton_3_clicked()
{
    QString path = QFileDialog::getOpenFileName(this, "Abrir archivo JSON", "", "Archivos JSON (*.json)");
    if (path.isEmpty()) {
        qDebug() << "No se seleccionó ningún archivo.";
        return;
    }

    qDebug() << "Archivo seleccionado para carga masiva de solicitudes:" << path;
    cargarusuario->cargarS(path);
}

