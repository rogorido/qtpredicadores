#ifndef DLGDIOCESIS_H
#define DLGDIOCESIS_H

#include <QWidget>
#include <QModelIndex>

class QMenu;
//class QAction;
class QSqlQueryModel;
class QSortFilterProxyModel;
class SqlFiltroGestor;
class ProxyNombres;
class QMenu;
class QAction;

class MyQmdiArea;

namespace Ui {
class dlgDiocesis;
}

class dlgDiocesis : public QWidget
{
    Q_OBJECT

public:
    explicit dlgDiocesis(QWidget *parent = 0);
    ~dlgDiocesis();

private slots:

    void seleccionarDiocesis(const QModelIndex &idx);
    void actualizarSql(QString s);
    void actualizarFiltro(const QString filtro);
    void menuContextualDiocesis(const QPoint &point);
    void modificarDiocesis();
    void abrirUrl();

    void cerrar();

    void on_ckSinComprobar_toggled(bool checked);
    void on_pbIntroducirObispos_clicked();

    void on_pbMarcarComprobado_clicked();

private:
    Ui::dlgDiocesis *ui;
    MyQmdiArea *mdiarea;

    QMenu *menuContextoDiocesis;

    QAction *a_modificarDiocesis;

    /*
     * NOTE: esto es un poco absurdo, pues este model ya exsite como
     * QSqlTableModel. Pero: ahora mismo tengo problemas con QsqlTableModel
     * y por eso lo hago así...
     */
    QSqlQueryModel *m_diocesis;
    QSqlQueryModel *m_obispos;
    QSortFilterProxyModel *m_obispos_proxy;

    SqlFiltroGestor *sql_gestor;
    ProxyNombres *proxy_diocesis;

    QString sqlactivo;
    int diocesis_seleccionada = 0;

    void cargarModelos();
    QString extraerUrl();
    void mostrarObispos();
    void cargarMenus();

};

#endif // DLGDIOCESIS_H
