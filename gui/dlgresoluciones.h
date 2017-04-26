#ifndef DLGRESOLUCIONES_H
#define DLGRESOLUCIONES_H

#include <QDialog>

class QSqlQueryModel;

namespace Ui {
class DlgResoluciones;
}

class DlgResoluciones : public QDialog
{
    Q_OBJECT

public:
    explicit DlgResoluciones(QWidget *parent = 0);
    ~DlgResoluciones();

private:
    Ui::DlgResoluciones *ui;

    /*
     * no pongo m_resoluciones pq "se confundiría
     * con el que suelo usar que carga toda la tabla,
     * y aquí solo cargamos una parte y además con datos de otras
     */
    QSqlQueryModel *resoluciones_model;
};

#endif // DLGRESOLUCIONES_H
