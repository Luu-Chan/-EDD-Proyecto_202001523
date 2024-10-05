#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "abb.h"
#include "arbolavl.h"
#include "formadmin.h"
#include "formregistro.h"
#include "formuser.h"
#include "listadoble.h"
#include <QMainWindow>


QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_ingresar_clicked();

    void on_pushButton_clicked();

    void on_registrar_clicked();

private:
    Ui::MainWindow *ui;
    arbolAVL tree;
    ListaDoble list;
    ABB abb;
    formAdmin *vadmin;
    formUser *vuser;
    formregistro *registro;
};
#endif // MAINWINDOW_H
