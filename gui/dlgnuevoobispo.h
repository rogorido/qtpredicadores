#ifndef DLGNUEVOOBISPO_H
#define DLGNUEVOOBISPO_H

#include <QDialog>

namespace Ui {
class dlgNuevoObispo;
}

class dlgNuevoObispo : public QDialog
{
    Q_OBJECT

public:
    explicit dlgNuevoObispo(QWidget *parent = 0);
    ~dlgNuevoObispo();

private:
    Ui::dlgNuevoObispo *ui;
};

#endif // DLGNUEVOOBISPO_H
