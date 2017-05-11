#ifndef DIOCESIS_H
#define DIOCESIS_H

#include <QString>
#include <QJsonObject>

class Diocesis
{
public:
    Diocesis();

private:

    int id;
    QString nombre;
    QString nombre_latin;
    bool archidiocesis;
    int sufraganeade;
    int lugar;
    bool existe_hoy;
    QJsonObject otros_datos;


};

#endif // DIOCESIS_H
