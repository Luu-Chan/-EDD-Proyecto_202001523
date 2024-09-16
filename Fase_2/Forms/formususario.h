#ifndef FORMUSUSARIO_H
#define FORMUSUSARIO_H

#include <QDialog>

namespace Ui {
class FormUsusario;
}

class FormUsusario : public QDialog
{
    Q_OBJECT

public:
    explicit FormUsusario(QWidget *parent = nullptr);
    ~FormUsusario();

private:
    Ui::FormUsusario *ui;
};

#endif // FORMUSUSARIO_H
