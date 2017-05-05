#ifndef SUFRAGIO_H
#define SUFRAGIO_H

#include <QString>
#include <QStringList>
#include <QJsonObject>

class Sufragio
{
public:
    Sufragio();

    // setters
    void setTipo(QString t);
    void setMisas(int m);
    void setMotivo(QString m);
    void setDestinatarios(QStringList d);

    // getters
    QString getTipo() const {return tipo;}
    int getMisas() const {return misas;}
    QString getMotivo() const {return motivo;}
    QStringList getDestinatarios() const {return destinatarios;}

    QJsonObject getSufragio();

private:

    QString tipo;
    int misas;
    QString motivo;
    QStringList destinatarios;
};

#endif // SUFRAGIO_H
