#ifndef DLGNUEVAOBRA_H
#define DLGNUEVAOBRA_H

#include <QDialog>

#include "objs/persona.h"
#include "objs/lugar.h"

class LugaresModel;
class QCompleter;
class QSqlQueryModel;

namespace Ui {
class dlgNuevaObra;
}

class dlgNuevaObra : public QDialog
{
    Q_OBJECT

public:
    explicit dlgNuevaObra(QWidget *parent = 0);
    ~dlgNuevaObra();

private slots:
    void on_btAnadirLugar_clicked();
    //void on_txtAutor_doubleclicked();
    void on_btSeleccionarAutor_clicked();
    void on_btIntroducirLugar_clicked();
    void on_btQuitarAutor_clicked();
    void on_btQuitarLugar_clicked();
    void on_btOK_clicked();

    void actualizarPersona(Persona autor);
    void actualizarLugar(Lugar lugar);

private:
    Ui::dlgNuevaObra *ui;

    QSqlQueryModel *m_lugaresoriginales;
    QSqlQueryModel *m_idiomas;
    QSqlQueryModel *m_editores;

    QCompleter *c_lugaresoriginales;
    QCompleter *c_idiomas;
    QCompleter *c_editor;

    LugaresModel *m_lugares;

    Persona *autorescogido; // ver abajo lo del elementopareado
    Lugar *lugarescogido;

    /*
     * sinceramente: la idea de usar esto es para aquellos casos
     * en los que borro la persona que he metido. Si lo hago con una Persona
     * sinceramente no sé cómo "vaciarla".
     */
    struct elementopareado{
      int id;
      QString elemento;
    };

    elementopareado autorescogido_struct;
    elementopareado lugarescogido_struct;

    void cargarCompleters();

};

#endif // DLGNUEVAOBRA_H
