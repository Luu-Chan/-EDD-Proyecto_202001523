#include "formususario.h"
#include "ui_formususario.h"

FormUsusario::FormUsusario(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::FormUsusario)
{
    ui->setupUi(this);
}

FormUsusario::~FormUsusario()
{
    delete ui;
}
