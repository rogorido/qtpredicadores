#ifndef DLGCAPITULOS_H
#define DLGCAPITULOS_H

#include <QDialog>

class QSqlTableModel;
class QSortFilterProxyModel;
class QModelIndex;

namespace Ui {
class dlgCapitulos;
}

class dlgCapitulos : public QDialog
{
    Q_OBJECT

public:
    explicit dlgCapitulos(QWidget *parent = 0);
    ~dlgCapitulos();

private slots:
    void escogidoCapitulo(const QModelIndex &idx);

private:
    Ui::dlgCapitulos *ui;

    QSqlTableModel *m_capitulos;
    QSqlTableModel *m_resoluciones;
    QSortFilterProxyModel *m_proxyresoluciones;
};

#endif // DLGCAPITULOS_H
