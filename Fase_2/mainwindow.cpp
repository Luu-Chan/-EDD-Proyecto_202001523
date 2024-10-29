#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include <QDebug>
#include <QMessageBox>
#include "formregistro.h"
#include "formuser.h"
#include "formadmin.h"
#include "user.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent),
     ui(new Ui::MainWindow)
    ,vadmin(nullptr)
    ,vuser(nullptr)
    ,registro(nullptr)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_ingresar_clicked()
{

    QString correoE = ui->textU->text();
    QString pass = ui->textP->text();

    if ( tree.credenciales(correoE.toStdString(), pass.toStdString())){
        qDebug() << "ingeso";

        if (!vuser) {
            vuser = new formUser(this, &tree, &list, &abb, correoE, &g);
        }
        else {
            vuser->setcorreoUser(correoE);
        }

        vuser->show();
        vuser->activateWindow();
        ui->textP->clear();
        ui->textU->clear();
        this->hide();
    }
    else if (correoE == "admin@gmail.com" & pass == "EDD2S2024"){
        if (!vadmin) {
            vadmin = new formAdmin(this, &tree, &list, &abb, &g );
        }

        vadmin->setFixedSize(1350, 760);
        vadmin->show();
        vadmin->activateWindow();
        ui->textP->clear();
        ui->textU->clear();
        this->hide();
    }
    else{
        QMessageBox::information(this, "Inicio de Sesión", "Credenciales Incorrectas");

    }
}


void MainWindow::on_pushButton_clicked()
{
}


void MainWindow::on_registrar_clicked()
{
    if (!registro) {
        registro = new formregistro(this, &tree, &g);
    }

    registro->show();
    this->hide();

}

