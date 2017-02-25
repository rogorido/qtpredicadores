#ifndef DLGNUEVAPERSONA_H
#define DLGNUEVAPERSONA_H

#include <QDialog>

class PersonasModel;

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

private:
    Ui::dlgNuevaPersona *ui;

    PersonasModel *m_personas;
};

#endif // DLGNUEVAPERSONA_H
