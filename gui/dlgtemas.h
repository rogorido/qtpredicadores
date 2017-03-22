#ifndef DLGTEMAS_H
#define DLGTEMAS_H

#include <QDialog>

namespace Ui {
class dlgTemas;
}

class dlgTemas : public QDialog
{
    Q_OBJECT

public:
    explicit dlgTemas(QWidget *parent = 0);
    ~dlgTemas();

private:
    Ui::dlgTemas *ui;
};

#endif // DLGTEMAS_H
