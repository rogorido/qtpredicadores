#ifndef MYQMDIAREA_H
#define MYQMDIAREA_H

#include <QMdiArea>
#include <QObject>
#include <QWidget>

class MyQmdiArea : public QMdiArea
{
    Q_OBJECT

public:
    MyQmdiArea(QWidget *parent = 0);
};

#endif // MYQMDIAREA_H
