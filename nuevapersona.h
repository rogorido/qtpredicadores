#ifndef NUEVAPERSONA_H
#define NUEVAPERSONA_H

#include <QDialog>

namespace Ui {
class NuevaPersona;
}

class NuevaPersona : public QDialog
{
    Q_OBJECT

public:
    explicit NuevaPersona(QWidget *parent = 0);
    ~NuevaPersona();

private slots:
    void aceptarPersona();

private:
    Ui::NuevaPersona *ui;
};

#endif // NUEVAPERSONA_H
