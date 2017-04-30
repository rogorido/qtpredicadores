#ifndef DLGESTADISTICAS_H
#define DLGESTADISTICAS_H

#include <QDialog>

class QSqlQueryModel;

namespace Ui {
class dlgEstadisticas;
}

class dlgEstadisticas : public QDialog
{
    Q_OBJECT

public:
    explicit dlgEstadisticas(QWidget *parent = 0);
    ~dlgEstadisticas();

private slots:

    void cambiarModelo(int row);


private:
    Ui::dlgEstadisticas *ui;

    QSqlQueryModel *estadisticas;
};

#endif // DLGESTADISTICAS_H
