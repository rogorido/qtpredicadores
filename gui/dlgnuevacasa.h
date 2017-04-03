#ifndef DLGNUEVACASA_H
#define DLGNUEVACASA_H

#include <QDialog>

#include "objs/lugar.h"
#include "objs/provincia.h"

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
    void quitarLugar(); // tenemos que quitarlo pq está en el struct
    void recibirLugar(Lugar lugar);

    void anadirProvincia();
    void quitarProvincia();
    void recibirProvincia(Provincia provincia);

private:
    Ui::dlgNuevaCasa *ui;

    LugaresModel *m_lugares;
    CasasModel *m_casas;

    struct elementopareado{
      int id = 0;
      QString elemento = "";
    };

    elementopareado lugar_struct;
    elementopareado provincia_struct;

    void borrarCampos();

};

#endif // DLGNUEVACASA_H
