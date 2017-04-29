#ifndef LICENCIA_H
#define LICENCIA_H

#include <QString>
#include <QStringList>

class Licencia
{
public:
    Licencia();

    // setters
    void setLicenciaTipo(QString l);
    void setOtorgantes(QStringList o);
    void setReceptores(QStringList r);
    void setAsunto(QString a);
    void setSeguridad(int s);

    // getters
    QString getLicenciatipo() const { return licenciatipo; }
    QStringList getOtorgantes() const { return otorgantes; }
    QStringList getReceptores() const { return receptores; }
    QString getAsunto() const { return asunto; }
    int getSeguridad() const { return seguridad; }

private:

    QString licenciatipo;
    QStringList otorgantes;
    QStringList receptores;
    QString asunto;
    int seguridad; // de la interpretación

};

#endif // LICENCIA_H