#ifndef DLGREFORMA_H
#define DLGREFORMA_H

#include <QDialog>

#include "src/objs/variados.h"
#include "src/objs/lugar.h"

class QCompleter;
class QSqlQueryModel;

namespace Ui {
class dlgReforma;
}

class dlgReforma : public QDialog
{
    Q_OBJECT

public:
    explicit dlgReforma(QWidget *parent = 0);
    ~dlgReforma();

private slots:

    void anadirLugar();
    void quitarLugar();
    void aceptar();

    void recibirLugar(Lugar lugar);

private:
    Ui::dlgReforma *ui;

    elementopareado lugar_struct;

    QSqlQueryModel *m_ordenes;
    QCompleter *m_ordenes_completer;

    void cargarModelos();
    QString crearJsonDatos();
    void borrarCampos();
};

#endif // DLGREFORMA_H
