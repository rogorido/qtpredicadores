#ifndef PENA_H
#define PENA_H

#include <QString>
#include <QStringList>

class Pena
{
public:
    Pena();

    // setters
    void setPenasTipos(QStringList p);
    void setPenaTexto(QString p);
    void setDuracion(QString d);
    void setRestriccion(QString r);
    void setAbsolucion(QString a);
    void setPenados(QStringList p);
    void setMotivo(QString m);
    void setSeguridad(int s);

    // getters
    QStringList getPenasTipos() const { return penas_tipos; }
    QString getPenaTexto() const { return pena_texto; }
    QString getDuracion() const { return duracion; }
    QString getRestriccion() const { return restriccion; }
    QString getAbsolucion() const { return absolucion; }
    QStringList getPenados() const { return penados; }
    QString getMotivo() const { return motivo; }
    int getSeguridad() const {return seguridad; }

private:

    QStringList penas_tipos;
    QString pena_texto;
    QString duracion;
    QString restriccion;
    QString absolucion; // quién puede absolver
    QStringList penados;
    QString motivo;
    int seguridad;
};

#endif // PENA_H
