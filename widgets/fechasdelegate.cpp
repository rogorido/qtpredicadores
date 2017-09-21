#include "fechasdelegate.h"

#include <QDate>

FechasDelegate::FechasDelegate(QObject *parent):QStyledItemDelegate(parent)
{

}

QString FechasDelegate::displayText(const QVariant &value, const QLocale &locale) const
{
    Q_UNUSED(locale)

    QDate fechaoriginal = value.toDate();
    // ponemos sólo el año...
    //QString fechaformateada = fechaoriginal.toString("dd/MM/yyyy");
    QString fechaformateada = fechaoriginal.toString("yyyy");
    return fechaformateada;

}
