#ifndef CARGAMASIVA_H
#define CARGAMASIVA_H
#include "arbolavl.h"
#include <QString>
#include "listadoble.h"
#include "abb.h"

class cargaMasiva
{
public:
    cargaMasiva(arbolAVL* tree, ListaDoble *list, ABB *abb);
    void cargarU(const QString& rutaArchivo);
    void cargarP(const QString& ruta);
    void cargarS(const QString& ruta);


private:
    arbolAVL* tree;
    ListaDoble *list;
    ABB *abb;
};

#endif // CARGAMASIVA_H
