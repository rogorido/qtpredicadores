#ifndef DLGDETALLES_H
#define DLGDETALLES_H

#include <QDialog>

#include "objs/persona.h"
#include "objs/lugar.h"

class JsonGestor;
class QSqlQueryModel;
class QCompleter;

namespace Ui {
class dlgDetalles;
}

class dlgDetalles : public QDialog
{
    Q_OBJECT

public:
    explicit dlgDetalles(JsonGestor *json, QWidget *parent = 0);
    ~dlgDetalles();

private slots:
    void recibirPersona(Persona persona);
    void recibirLugar(Lugar lugar);
    void actualizarCompleterValues(); // cuando cambia el campo key de json libre

    void on_btPersona_clicked();
    void on_btLugar_clicked();
    void on_btJsonAnadirLibre_clicked();
    void on_btJsonAnadirDescripcion_clicked();
    void on_btModificarDetalles_toggled(bool checked);

private:
    Ui::dlgDetalles *ui;

    /* estos son modelos solo de este form */
    QSqlQueryModel *m_keys;
    QSqlQueryModel *m_values;

    QCompleter *keys_completer;
    QCompleter *values_completer;

    JsonGestor *jsondetalles;

    void cargarModelos();
};

#endif // DLGDETALLES_H
