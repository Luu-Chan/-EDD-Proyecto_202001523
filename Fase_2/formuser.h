#ifndef FORMUSER_H
#define FORMUSER_H

#include "abb.h"
#include "arbolavl.h"
#include "graph.h"
#include "listadoble.h"
#include <QDialog>

namespace Ui {
class formUser;
}

class formUser : public QDialog
{
    Q_OBJECT

public:
    explicit formUser(QWidget *parent = nullptr, arbolAVL *tree = nullptr, ListaDoble *list = nullptr ,
                      ABB *abb = nullptr, const QString& correoUser = nullptr, Graph *g = nullptr);
    ~formUser();
    void setcorreoUser(const QString& correoE);

private slots:
    void on_pushButton_2_clicked();

    void on_salir_clicked();

    void on_pushButton_clicked();

    void on_mostrar_clicked();

    void on_eliminar_clicked();

    void on_buscarFe_clicked();

    void on_inlimit_clicked();

    void on_poslimit_clicked();

    void on_prelimit_clicked();

    void on_verco_clicked();

    void on_comentarbutton_clicked();

    void on_agregarP_clicked();

    void on_buscar_clicked();

    void on_toppubli_clicked();

    void on_topcomen_clicked();

    void on_pushButton_4_clicked();

    void on_eliminarpubli_clicked();

    void on_enviarsol_clicked();

    void on_mostrarsol_clicked();

    void on_aceptars_clicked();

    void on_rechazars_clicked();

    void on_pushButton_3_clicked();

    void on_pushButton_5_clicked();

private:
    Ui::formUser *ui;
    arbolAVL *tree;
    ListaDoble *list;
    ABB *abb;
    QString correoUser;
    Graph *g;
};

#endif // FORMUSER_H
