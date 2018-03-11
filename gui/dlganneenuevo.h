#ifndef DLGANNEENUEVO_H
#define DLGANNEENUEVO_H

#include <QWidget>

#include "objs/persona.h"
#include "objs/tema.h"

class QCompleter;
class QSqlQueryModel;

class MyQmdiArea;

namespace Ui {
class dlgAnneeNuevo;
}

class dlgAnneeNuevo : public QWidget
{
    Q_OBJECT

public:
    explicit dlgAnneeNuevo(QWidget *parent = 0);
    ~dlgAnneeNuevo();

private slots:

    void cerrar();
    void aceptarAnnee();

    void anadirPersona();
    void anadirPersonaAdicional();
    void quitarPersonaAdicional();
    void anadirMeditacion();
    void quitarMeditacion();
    void anadirCategoriasMeditacion();

    void recibirPersonaPrincipal(Persona persona);
    void recibirPersonaAdicional(Persona persona);
    void recibirTema(Tema tema);

private:
    Ui::dlgAnneeNuevo *ui;
    MyQmdiArea *mdiarea;

    QSqlQueryModel *m_autores;
    QCompleter *m_autores_completer;
    QSqlQueryModel *m_temasprincipales;
    QCompleter *m_temasprincipales_completer;

    /*
     * aquí vienen las variables donde vamos a guardar los datos
     * pq por ahroa no hago una clase extra para esto
     */
    int persona_id = 0;

    struct m_meditacion {
        int numeracion;
        QString pensamiento;
        QHash<int, QString> categorias;
    };

    QList<m_meditacion> meditaciones;

    /*
     * aquí metemos las categorías que vamos escogiendo
     * con dlgseleccionar y que luego asociaremos en el struct
     * m_meditacion...
     */

    QHash<int, QString> categorias_seleccionadas;

    /*
     *  aquí metemos las personas, realmetne con los ids sería
     * suficiente, pero para que lo muestre en la tabla hago esto...
     */
    struct otrapersona {
        int id;
        QString nombre;
    };

    QList<otrapersona> personas_adicionales;

    void cargarModelos();
};

#endif // DLGANNEENUEVO_H
