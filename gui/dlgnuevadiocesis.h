#ifndef DLGNUEVADIOCESIS_H
#define DLGNUEVADIOCESIS_H

#include <QDialog>

class DiocesisModel;

namespace Ui {
class dlgNuevaDiocesis;
}

class dlgNuevaDiocesis : public QDialog
{
    Q_OBJECT

public:
    explicit dlgNuevaDiocesis(QWidget *parent = 0);
    ~dlgNuevaDiocesis();

private slots:

    void aceptarDiocesis();
    void borrarCampos();

private:
    Ui::dlgNuevaDiocesis *ui;

    DiocesisModel *m_diocesis;

    /*
     * aquí metemos esos valores que vendrían del
     * formulario seleccionar
     */

    int sufraganea;
    int lugar;
};

#endif // DLGNUEVADIOCESIS_H
