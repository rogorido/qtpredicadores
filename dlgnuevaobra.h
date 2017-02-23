#ifndef DLGNUEVAOBRA_H
#define DLGNUEVAOBRA_H

#include <QDialog>

#include "persona.h"

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

    void on_pushButton_clicked();

    void actualizarPersona(Persona autor);

private:
    Ui::dlgNuevaObra *ui;

    QSqlQueryModel *m_lugaresoriginales;
    QSqlQueryModel *m_idiomas;
    QSqlQueryModel *m_editores;

    QCompleter *c_lugaresoriginales;
    QCompleter *c_idiomas;
    QCompleter *c_editor;

    LugaresModel *m_lugares;

    /*
     * no sé por qué cojones esto da un error, o un crash
     * o todo tipo de cosas... he probado todo: declararlo como pointer
     * normal, etc. etc. y nada, no hay manera...
     */
    //AutorStruct autorescogido;
    /*
     * conclusión: al final meto el valor en una int normal
     */
    //int autorescogido;
    Persona *autorescogido;

    void cargarCompleters();
    void cargarCombos();

};

#endif // DLGNUEVAOBRA_H
