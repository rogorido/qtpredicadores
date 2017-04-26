#ifndef DLGRESOLUCIONES_H
#define DLGRESOLUCIONES_H

#include <QDialog>

class QSqlQueryModel;
class QSqlRelationalTableModel;
class QDataWidgetMapper;
class QModelIndex;

namespace Ui {
class DlgResoluciones;
}

class DlgResoluciones : public QDialog
{
    Q_OBJECT

public:
    explicit DlgResoluciones(QWidget *parent = 0);
    ~DlgResoluciones();

private slots:

    void seleccionarResolucion(const QModelIndex &idx);

private:
    Ui::DlgResoluciones *ui;

    /*
     * no pongo m_resoluciones pq "se confundiría
     * con el que suelo usar que carga toda la tabla,
     * y aquí solo cargamos una parte y además con datos de otras
     */
    QSqlQueryModel *resoluciones_model;
    QDataWidgetMapper *mapper_data;
    QSqlRelationalTableModel *temas_model;

    void cargarModelos();
};

#endif // DLGRESOLUCIONES_H
