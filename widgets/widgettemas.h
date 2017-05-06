#ifndef WIDGETTEMAS_H
#define WIDGETTEMAS_H

#include <QWidget>

class QSqlTableModel;
class QSortFilterProxyModel;

namespace Ui {
class WidgetTemas;
}

class WidgetTemas : public QWidget
{
    Q_OBJECT

public:
    explicit WidgetTemas(QWidget *parent = 0);
    ~WidgetTemas();

signals:

    void temasSeleccionadosCambio(QString filtro);

private slots:
    void on_btAnadir_clicked();

private:
    Ui::WidgetTemas *ui;

    QSqlTableModel *m_temas;
    QSortFilterProxyModel *temas_noseleccionados_proxy;
    QSortFilterProxyModel *temas_seleccionados_proxy;
};

#endif // WIDGETTEMAS_H
