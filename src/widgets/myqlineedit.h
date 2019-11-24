#ifndef MYQLINEEDIT_H
#define MYQLINEEDIT_H

#include <QLineEdit>
#include <QObject>
#include <QWidget>

class myQLineEdit : public QLineEdit {
  Q_OBJECT

 public:
  myQLineEdit(QWidget *parent = 0);

 signals:

  void dobleclick();

 protected:
  void mouseReleaseEvent(QMouseEvent *e) override;
};

#endif  // MYQLINEEDIT_H
