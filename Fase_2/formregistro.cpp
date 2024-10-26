#include "formregistro.h"
#include "mainwindow.h"
#include "ui_formregistro.h"
#include "QMessageBox"

formregistro::formregistro(QWidget *parent, arbolAVL *tree, Graph *g)
    : QDialog(parent)
    , ui(new Ui::formregistro)
    ,tree(tree)
    ,g(g)
{
    ui->setupUi(this);
}

formregistro::~formregistro()
{
    delete ui;
}

void formregistro::on_pushButton_2_clicked()
{
    this->close();

    qobject_cast<MainWindow*>(parent())->show();
}

void formregistro::on_registrar_clicked()
{
    QString correo = ui->correo->text();
    QString nombre = ui->nombres->text();
    QString apellido = ui->apellidos->text();
    QString pass = ui->pass->text();
    QString fecha = ui->dateEdit->date().toString();

    if (nombre.isEmpty() || apellido.isEmpty() || correo.isEmpty() || pass.isEmpty() || fecha.isEmpty()) {
        QMessageBox::warning(this, "Error", "Rellene todos los campos.");
        return;
    }

    if (tree->search(correo.toStdString())) {
        QMessageBox::warning(this, "Error", "El correo ya está registrado.");
        return;
    }

    user* nuevo = new user(nombre.toStdString(), apellido.toStdString(), fecha.toStdString(), correo.toStdString(), pass.toStdString());

    tree->insertU(nuevo);
    QMessageBox::warning(this, "Registro", "Se ha registrado correctamente.");
    g->addUser(correo.toStdString());
    ui->apellidos->clear();
    ui->nombres->clear();
    ui->correo->clear();
    ui->pass->clear();
}

