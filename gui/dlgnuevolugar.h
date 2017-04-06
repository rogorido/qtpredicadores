#ifndef DLGNUEVOLUGAR_H
#define DLGNUEVOLUGAR_H

#include <QDialog>

class JsonGestor;
class LugaresModel;
class QSqlQueryModel;
class QCompleter;
class dlgDetalles;

namespace Ui {
class dlgNuevoLugar;
}

class dlgNuevoLugar : public QDialog
{
    Q_OBJECT

public:
    explicit dlgNuevoLugar(QWidget *parent = 0);
    ~dlgNuevoLugar();

private slots:

    void aceptar();

private:
    Ui::dlgNuevoLugar *ui;

    dlgDetalles *dlgdetalles;

    JsonGestor *otrosnombres;
    LugaresModel *m_lugares;

    QSqlQueryModel *m_paises;
    QSqlQueryModel *m_tipos;
    QCompleter *m_paises_completer;
    QCompleter *m_tipos_completer;

    void cargarModelos();
    void borrarCampos();
};

#endif // DLGNUEVOLUGAR_H
