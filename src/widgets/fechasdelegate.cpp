#include "fechasdelegate.h"

#include <QDate>

FechasDelegate::FechasDelegate(TipoFecha tipo, QObject *parent)
    : QStyledItemDelegate(parent), m_tipo(tipo)
{
}

QString FechasDelegate::displayText(const QVariant &value,
                                    const QLocale &locale) const
{
  QString fechaformateada;
  Q_UNUSED(locale)

  QDate fechaoriginal = value.toDate();

  switch (m_tipo) {
    case TipoFecha::ONLY_YEAR:
      fechaformateada = fechaoriginal.toString("yyyy");
      break;
    case TipoFecha::FULL_DATE:
      fechaformateada = fechaoriginal.toString("dd/MM/yyyy");
      break;
    default:
      break;
  }

  return fechaformateada;
}
