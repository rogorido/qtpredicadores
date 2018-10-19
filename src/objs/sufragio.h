#ifndef SUFRAGIO_H
#define SUFRAGIO_H

#include <QString>
#include <QStringList>
#include <QJsonObject>
#include <QJsonArray>

#include "variados.h"
#include "notas.h"

class Sufragio
{
public:
    Sufragio();

    // setters
    void setTipo(const QString t);
    void setMisas(const int m);
    void setMotivo(const QString m);
    void setDestinatarios(const QStringList d);
    void setExtraInfos(const ExtraInfos e);
    void setNota(const Notas n);

    // getters
    QString getTipo() const {return tipo;}
    int getMisas() const {return misas;}
    QString getMotivo() const {return motivo;}
    QStringList getDestinatarios() const {return destinatarios;}
    ExtraInfos getExtraInfos() const {return extras;}
    Notas getNotas() const {return nota;}

    QJsonObject getSufragioJson();

private:

    QString tipo;
    int misas;
    QString motivo;
    QStringList destinatarios;
    ExtraInfos extras;
    Notas nota;
};

#endif // SUFRAGIO_H
