#ifndef DLGCIUDADES_H
#define DLGCIUDADES_H

#include <QWidget>

class QSqlTableModel;

namespace Ui {
class dlgCiudades;
}

class dlgCiudades : public QWidget
{
    Q_OBJECT

public:
    explicit dlgCiudades(QWidget *parent = 0);
    ~dlgCiudades();

private:
    Ui::dlgCiudades *ui;

    QSqlTableModel *ciudades_model;

    void cargarModelos();
};

#endif // DLGCIUDADES_H
