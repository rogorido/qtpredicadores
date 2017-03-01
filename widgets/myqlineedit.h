#ifndef MYQLINEEDIT_H
#define MYQLINEEDIT_H

#include <QObject>
#include <QWidget>
#include <QLineEdit>

class myQLineEdit : public QLineEdit
{
    Q_OBJECT

public:
    myQLineEdit(QWidget *parent = 0);

signals:

    void dobleclick();

protected:
    void mouseReleaseEvent(QMouseEvent *e) override;
};

#endif // MYQLINEEDIT_H
