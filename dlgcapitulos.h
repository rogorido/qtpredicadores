#ifndef DLGCAPITULOS_H
#define DLGCAPITULOS_H

#include <QDialog>

class QSqlTableModel;
class QSortFilterProxyModel;
class QModelIndex;

namespace Ui {
class DlgCapitulos;
}

class DlgCapitulos : public QDialog
{
    Q_OBJECT

public:
    explicit DlgCapitulos(QWidget *parent = 0);
    ~DlgCapitulos();

private slots:
    void escogidoCapitulo(const QModelIndex &idx);

private:
    Ui::DlgCapitulos *ui;

    QSqlTableModel *m_capitulos;
    QSqlTableModel *m_resoluciones;
    QSortFilterProxyModel *m_proxyresoluciones;
};

#endif // DLGCAPITULOS_H
