#ifndef MYQMDIAREA_H
#define MYQMDIAREA_H

#include <QMdiArea>
#include <QObject>
#include <QWidget>

/*
 * Esta clase singleton no tiene método DestroyMe
 * como otras que tengo, porque veo que me da un segmentation fault.
 * Creo que la razón es la siguiente: de alguna forma borra el objeto
 * antes de que lo borre la mainwindow. Entonces la mainwindow al cerrarse
 * intenta borrarlo y como ha desaparecido da un error.
 */

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
};

#endif // MYQMDIAREA_H
