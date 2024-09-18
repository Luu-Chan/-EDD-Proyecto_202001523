#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include "./Forms/formususario.h"
#include <QDebug>
#include <QMessageBox>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_ingresar_clicked()
{
    QString usuario = ui->textU->text();
    QString pass = ui->textP->text();
    if (usuario == "1" & pass == "1"  ){
    this->close();
    FormUsusario *vuser = new FormUsusario(this);
    vuser->show();
    }
    else{
        QMessageBox::information(this, "Inicio de Sesión", "Icorrecto we");



    }
}

