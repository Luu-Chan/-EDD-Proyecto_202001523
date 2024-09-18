#include "registrarse.h"
#include "ui_registrarse.h"

registrarse::registrarse(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::registrarse)
{
    ui->setupUi(this);
}

registrarse::~registrarse()
{
    delete ui;
}
