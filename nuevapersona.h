#ifndef NUEVAPERSONA_H
#define NUEVAPERSONA_H

#include <QDialog>

class Personas;

namespace Ui {
class NuevaPersona;
}

class NuevaPersona : public QDialog
{
    Q_OBJECT

public:
    explicit NuevaPersona(Personas *m_personas, QWidget *parent = 0);
    ~NuevaPersona();

private slots:
    void aceptarPersona();

private:
    Ui::NuevaPersona *ui;

    Personas *m_personas;
};

#endif // NUEVAPERSONA_H
