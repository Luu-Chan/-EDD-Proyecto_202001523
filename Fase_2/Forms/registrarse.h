#ifndef REGISTRARSE_H
#define REGISTRARSE_H

#include <QDialog>

namespace Ui {
class registrarse;
}

class registrarse : public QDialog
{
    Q_OBJECT

public:
    explicit registrarse(QWidget *parent = nullptr);
    ~registrarse();

private:
    Ui::registrarse *ui;
};

#endif // REGISTRARSE_H
