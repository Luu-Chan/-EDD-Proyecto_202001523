#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include "./Forms/formususario.h"

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
    this->close();
    FormUsusario *vuser = new FormUsusario(this);
    vuser->show();

}

