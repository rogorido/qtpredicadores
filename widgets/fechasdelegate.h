#ifndef FECHASDELEGATE_H
#define FECHASDELEGATE_H

#include <QStyledItemDelegate>

class FechasDelegate : public QStyledItemDelegate
{
    Q_OBJECT

public:
    explicit FechasDelegate(QObject *parent = 0);
    virtual QString displayText(const QVariant &value, const QLocale &locale) const;
};

#endif // FECHASDELEGATE_H
