#ifndef DLGNUEVAPERSONA_H
#define DLGNUEVAPERSONA_H

#include <QDialog>

class PersonasModel;
class JsonGestor;
class dlgDetalles;

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

    JsonGestor *jsongestor;
    JsonGestor *otrosnombres_json;
    dlgDetalles *dlgdetalles;
    dlgDetalles *dlgotrosnombres;

    void introducirJson(const int id);

};

#endif // DLGNUEVAPERSONA_H
