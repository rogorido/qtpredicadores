#ifndef DLGOBISPOS_H
#define DLGOBISPOS_H

#include <QDialog>

class QSqlQueryModel;

namespace Ui {
class dlgObispos;
}

class dlgObispos : public QDialog
{
    Q_OBJECT

public:
    explicit dlgObispos(QWidget *parent = 0);
    ~dlgObispos();

private:
    Ui::dlgObispos *ui;

    QSqlQueryModel *obispos_model;
};

#endif // DLGOBISPOS_H
