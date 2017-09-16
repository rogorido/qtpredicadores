#ifndef DLGOBISPOS_H
#define DLGOBISPOS_H

#include <QWidget>

class QSqlQueryModel;

namespace Ui {
class dlgObispos;
}

class dlgObispos : public QWidget
{
    Q_OBJECT

public:
    explicit dlgObispos(QWidget *parent = 0);
    ~dlgObispos();

private slots:
    void on_ckVolverAMirar_toggled(bool checked);

private:
    Ui::dlgObispos *ui;

    QSqlQueryModel *obispos_model;

    /*
     * guardamos el SQL que está activo
     */
    QString sqlactivo;

    /*
     * esta variable guarda si estamos viendo los que
     * hay que volver a mirar
     */
    bool volveramirar = false;

    void cargarModelos();
};

#endif // DLGOBISPOS_H
