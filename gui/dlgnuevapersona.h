#ifndef DLGNUEVAPERSONA_H
#define DLGNUEVAPERSONA_H

#include <QDialog>

class PersonasModel;
class QJsonModel;
class dlgDetalles;

class QCompleter;
class QSqlQueryModel;

namespace Ui {
class dlgNuevaPersona;
}

class dlgNuevaPersona : public QDialog
{
    Q_OBJECT

public:
    explicit dlgNuevaPersona(QWidget *parent = 0);
    ~dlgNuevaPersona();

private slots:
    void aceptarPersona();

    void on_btDetalles_clicked();
    void on_btOtrosNombres_clicked();

private:
    Ui::dlgNuevaPersona *ui;

    PersonasModel *m_personas;

    QCompleter *nombres_compl;
    QCompleter *apellidos_compl;
    QCompleter *diocesis_compl;

    /* Esto sincermnete no se por que hay
     * que ponerlo asi aqui. Lo logico seria ponerlo
     * como variable local y luego pasarlo como referencia
     * al Qcompleter; pero no funciona... ¿sera porque se pierde
     * el modelo al salir?
     */
    QSqlQueryModel *nombres_query;
    QSqlQueryModel *apellidos_query;
    QSqlQueryModel *diocesis_query;

    QJsonModel *jsongestor;
    QJsonModel *otrosnombres_json;
    dlgDetalles *dlgdetalles;
    dlgDetalles *dlgotrosnombres;

    void introducirJson(const int id);

    void cargarCompleters();
    void borrarCampos();
    void cargarJsonEstructuras();

};

#endif // DLGNUEVAPERSONA_H
