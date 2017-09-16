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

private:
    Ui::dlgObispos *ui;

    QSqlQueryModel *obispos_model;

    /*
     * guardamos el SQL que está activo
     */
    QString sqlactivo;

    void cargarModelos();

};

#endif // DLGOBISPOS_H
