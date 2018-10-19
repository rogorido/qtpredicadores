#ifndef DLGNUEVAPERSONA_H
#define DLGNUEVAPERSONA_H

#include <QWidget>

#include "src/objs/variados.h"

class Persona;
class PersonasModel;
class QJsonModel;
class dlgDetalles;

class QCompleter;
class QSqlQueryModel;

class MyQmdiArea;

namespace Ui {
class dlgNuevaPersona;
}

class dlgNuevaPersona : public QWidget
{
    Q_OBJECT

public:
    explicit dlgNuevaPersona(QWidget *parent = 0, int persona = 0);
    ~dlgNuevaPersona();

private slots:
    void aceptarPersona();

    void on_btDetalles_clicked();
    void on_btOtrosNombres_clicked();    
    void on_btFuente_clicked();

    void recibirFuente(fuente f);

    void cerrar();

signals:

    void personaIntroducida();

private:
    Ui::dlgNuevaPersona *ui;
    MyQmdiArea *mdiarea;

    PersonasModel *m_personas;

    QCompleter *nombres_compl;
    QCompleter *apellidos_compl;
    QCompleter *diocesis_compl;
    QCompleter *tipopersona_compl;

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

    fuente fuente_origen;

    bool modificando = false;
    int persona_modificando = 0;

    void introducirJson(const int id);

    void cargarUI();
    void cargarCompleters();
    void borrarCampos();

    void cargarPersona();

    /*
     * hacemos dos métodos iguales para introducir
     * la obra en la BD... Esto supone repetir el código
     * en parte pero no se ocurre nada mejor
     */
    void introducirPersonaEnBD(Persona *persona); // nueva
    void introducirPersonaEnBD(Persona *persona, bool modificar); // modificando una existente


};

#endif // DLGNUEVAPERSONA_H
