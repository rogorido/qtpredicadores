#ifndef DLGNUEVAPROVINCIA_H
#define DLGNUEVAPROVINCIA_H

#include <QDialog>

class ProvinciasModel;

namespace Ui {
class dlgNuevaProvincia;
}

class dlgNuevaProvincia : public QDialog
{
    Q_OBJECT

public:
    explicit dlgNuevaProvincia(QWidget *parent = 0);
    ~dlgNuevaProvincia();

private slots:

    void aceptarProvincia();
    void borrarCampos();

private:
    Ui::dlgNuevaProvincia *ui;

    ProvinciasModel *m_provincias;
};

#endif // DLGNUEVAPROVINCIA_H
