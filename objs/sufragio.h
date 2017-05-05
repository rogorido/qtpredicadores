#ifndef SUFRAGIO_H
#define SUFRAGIO_H

#include <QString>
#include <QStringList>
#include <QJsonObject>

#include "objs/variados.h"

class Sufragio
{
public:
    Sufragio();

    // setters
    void setTipo(QString t);
    void setMisas(int m);
    void setMotivo(QString m);
    void setDestinatarios(QStringList d);
    void setExtraInfos(ExtraInfos e);

    // getters
    QString getTipo() const {return tipo;}
    int getMisas() const {return misas;}
    QString getMotivo() const {return motivo;}
    QStringList getDestinatarios() const {return destinatarios;}
    ExtraInfos getExtraInfos() const {return extras;}

    QJsonObject getSufragio();

private:

    QString tipo;
    int misas;
    QString motivo;
    QStringList destinatarios;
    ExtraInfos extras;
};

#endif // SUFRAGIO_H
