#ifndef NUEVACASA_H
#define NUEVACASA_H

#include <QDialog>

class LugaresModel;
class CasasModel;

namespace Ui {
class NuevaCasa;
}

class NuevaCasa : public QDialog
{
    Q_OBJECT

public:
    explicit NuevaCasa(QWidget *parent = 0);
    ~NuevaCasa();

private slots:

    void aceptarCasa();
    void anadirLugar();

private:
    Ui::NuevaCasa *ui;

    LugaresModel *m_lugares;
    CasasModel *m_casas;
};

#endif // NUEVACASA_H
