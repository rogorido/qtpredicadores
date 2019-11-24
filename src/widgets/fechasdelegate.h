#ifndef FECHASDELEGATE_H
#define FECHASDELEGATE_H

#include <QStyledItemDelegate>

class FechasDelegate : public QStyledItemDelegate {
  Q_OBJECT

 public:
  enum class TipoFecha { FULL_DATE, ONLY_YEAR };

  explicit FechasDelegate(TipoFecha tipo, QObject *parent = 0);
  virtual QString displayText(const QVariant &value,
                              const QLocale &locale) const;

 private:
  TipoFecha m_tipo;
};

#endif  // FECHASDELEGATE_H
