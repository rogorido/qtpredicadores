#ifndef DLGNUEVOOBISPO_H
#define DLGNUEVOOBISPO_H

#include <QDialog>

#include "objs/persona.h"
#include "objs/diocesis.h"

class QSqlQueryModel;
class QCompleter;

namespace Ui {
class dlgNuevoObispo;
}

class dlgNuevoObispo : public QDialog
{
    Q_OBJECT

public:
    explicit dlgNuevoObispo(QWidget *parent = 0);
    ~dlgNuevoObispo();

private slots:

    void aceptarObispo();
    void anadirPersona();
    void anadirDiocesis();

    void recibirPersona(Persona persona);
    void recibirDiocesis(Diocesis diocesis);

private:
    Ui::dlgNuevoObispo *ui;

    QSqlQueryModel *m_papas;
    QCompleter *m_papas_completer;

    /*
     * esto son los que escogemos con los modelos, dialogs, etc.
     * y los metemos aquí con su id. Lo ponemos como 0 por el lío
     * ese de que luego lo quiero borrar, etc.
     */
    int persona_id = 0;
    int diocesis_id = 0;
    int papa_id = 0;

    void cargarModelos();
    void borrarCampos();
};

#endif // DLGNUEVOOBISPO_H
