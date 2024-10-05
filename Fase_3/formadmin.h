#ifndef FORMADMIN_H
#define FORMADMIN_H
#include "abb.h"
#include "cargamasiva.h"
#include "listadoble.h"
#include <QDialog>

namespace Ui {
class formAdmin;
}

class formAdmin : public QDialog
{
    Q_OBJECT

public:
    explicit formAdmin(QWidget *parent = nullptr, arbolAVL* tree = nullptr, ListaDoble *list = nullptr, ABB *abb = nullptr ) ;
    ~formAdmin();

private slots:
    void on_cargarU_clicked();

    void on_salirAdmin_clicked();

    void on_buscarA_clicked();

    void on_eliminar_clicked();

    void on_in_clicked();

    void on_pushButton_5_clicked();

    void on_post_clicked();

    void on_cargarP_clicked();

    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

    void on_pushButton_3_clicked();

private:
    Ui::formAdmin *ui;
    arbolAVL* tree;
    ListaDoble *list;
    ABB *abb;
    cargaMasiva* cargarusuario;

};

#endif // FORMADMIN_H
