#ifndef DLGNUEVOLUGAR_H
#define DLGNUEVOLUGAR_H

#include <QDialog>

class JsonGestor;
class LugaresModel;


namespace Ui {
class dlgNuevoLugar;
}

class dlgNuevoLugar : public QDialog
{
    Q_OBJECT

public:
    explicit dlgNuevoLugar(QWidget *parent = 0);
    ~dlgNuevoLugar();

private slots:

    void aceptar();

private:
    Ui::dlgNuevoLugar *ui;

    JsonGestor *otrosnombres;
    LugaresModel *m_lugares;
};

#endif // DLGNUEVOLUGAR_H
