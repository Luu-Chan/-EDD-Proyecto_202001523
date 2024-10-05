#ifndef FORMREGISTRO_H
#define FORMREGISTRO_H

#include "arbolavl.h"
#include <QDialog>

namespace Ui {
class formregistro;
}

class formregistro : public QDialog
{
    Q_OBJECT

public:
    explicit formregistro(QWidget *parent = nullptr, arbolAVL* tree = nullptr);
    ~formregistro();

private slots:
    void on_pushButton_2_clicked();

    void on_registrar_clicked();

private:
    Ui::formregistro *ui;
    arbolAVL* tree;
};

#endif // FORMREGISTRO_H
