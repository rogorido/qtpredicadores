#ifndef DLGNUEVAREEDICION_H
#define DLGNUEVAREEDICION_H

#include <QWidget>
#include <QJsonObject>

#include "objs/variados.h"
#include "objs/lugar.h"

class MyQmdiArea;
class QCompleter;
class QSqlQueryModel;

namespace Ui {
class dlgNuevaReedicion;
}

class dlgNuevaReedicion : public QWidget
{
    Q_OBJECT

public:
    explicit dlgNuevaReedicion(QWidget *parent = nullptr);
    ~dlgNuevaReedicion();

private slots:
    // GUI
    void on_pbOK_clicked();
    void on_pbCancelar_clicked();

    void recibirLugar(Lugar lugar);

    void aceptadaReedicion();
    void anadirLugar();

    void on_pbQuitarLugar_clicked();

signals:

    void aceptarReedicion(QJsonObject datos);

private:
    Ui::dlgNuevaReedicion *ui;
    MyQmdiArea *mdiarea;

    QSqlQueryModel *m_editores;
    QCompleter *m_editores_completer;
    QSqlQueryModel *m_formatos;
    QCompleter *m_formatos_completer;
    QSqlQueryModel *m_lenguas;
    QCompleter *m_lenguas_completer;

    elementopareado elem_lugar;

    void cargarModelos();

};

#endif // DLGNUEVAREEDICION_H
