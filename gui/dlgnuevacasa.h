#ifndef DLGNUEVACASA_H
#define DLGNUEVACASA_H

#include <QDialog>

class LugaresModel;
class CasasModel;

namespace Ui {
class dlgNuevaCasa;
}

class dlgNuevaCasa : public QDialog
{
    Q_OBJECT

public:
    explicit dlgNuevaCasa(QWidget *parent = 0);
    ~dlgNuevaCasa();

private slots:

    void aceptarCasa();
    void anadirLugar();

private:
    Ui::dlgNuevaCasa *ui;

    LugaresModel *m_lugares;
    CasasModel *m_casas;
};

#endif // DLGNUEVACASA_H
