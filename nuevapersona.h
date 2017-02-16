#ifndef NUEVAPERSONA_H
#define NUEVAPERSONA_H

#include <QDialog>

class PersonasModel;

namespace Ui {
class NuevaPersona;
}

class NuevaPersona : public QDialog
{
    Q_OBJECT

public:
    explicit NuevaPersona(PersonasModel *m_personas, QWidget *parent = 0);
    ~NuevaPersona();

private slots:
    void aceptarPersona();

private:
    Ui::NuevaPersona *ui;

    PersonasModel *m_personas;
};

#endif // NUEVAPERSONA_H
