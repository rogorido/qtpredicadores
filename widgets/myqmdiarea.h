#ifndef MYQMDIAREA_H
#define MYQMDIAREA_H

#include <QMdiArea>
#include <QObject>
#include <QWidget>

class MyQmdiArea : public QMdiArea
{
    Q_OBJECT

public:
    static MyQmdiArea *Instance(QWidget *parent = 0);

protected:
    MyQmdiArea(QWidget *parent = 0);
    MyQmdiArea(const MyQmdiArea &);
    MyQmdiArea &operator =(const MyQmdiArea &);

private:

    static MyQmdiArea *pInstance;
    static void DestroyMe();
};

#endif // MYQMDIAREA_H
