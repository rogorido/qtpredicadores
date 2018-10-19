#ifndef DLGFUENTEENTRADA_H
#define DLGFUENTEENTRADA_H

#include <QDialog>

#include "src/objs/variados.h"

class QSqlQueryModel;
class QCompleter;

namespace Ui {
class dlgFuenteEntrada;
}

class dlgFuenteEntrada : public QDialog
{
    Q_OBJECT

public:
    explicit dlgFuenteEntrada(QWidget *parent = 0);
    ~dlgFuenteEntrada();

protected:

    void accept();

signals:

    void signalFuente(fuente f);

private:
    Ui::dlgFuenteEntrada *ui;

    QSqlQueryModel *m_obras;
    QCompleter *m_obras_completer;
};

#endif // DLGFUENTEENTRADA_H
