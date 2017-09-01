#ifndef DLGRESOLUCIONES_H
#define DLGRESOLUCIONES_H

#include <QWidget>

#include "objs/tema.h"

class QSqlQueryModel;
class QSqlRelationalTableModel;
class QDataWidgetMapper;
class QModelIndex;
class QJsonModel;

class dlgSeleccionarGeneral;

namespace Ui {
class DlgResoluciones;
}

class DlgResoluciones : public QWidget
{
    Q_OBJECT

public:
    explicit DlgResoluciones(QWidget *parent = 0);
    ~DlgResoluciones();

private slots:

    void seleccionarResolucion(const QModelIndex &idx);
    void recibirNuevoTema(Tema t);
    // cuando añadimos detalles los recibimos en este slot
    void recibirNuevoJsonDetalles();
    void cargarDetalles(int id);
    void aplicarFiltro();

    void on_btAnadirTema_clicked();
    void on_btQuitarTema_clicked();
    void on_btAnadirDetalles_clicked();
    void on_btBorrarDetalles_clicked();

private:
    Ui::DlgResoluciones *ui;

    dlgSeleccionarGeneral *dlgseleccionar;

    /*
     * no pongo m_resoluciones pq "se confundiría
     * con el que suelo usar que carga toda la tabla,
     * y aquí solo cargamos una parte y además con datos de otras
     */
    QSqlQueryModel *resoluciones_model;
    QDataWidgetMapper *mapper_data;
    QSqlRelationalTableModel *temas_model;
    QJsonModel *json_model;

    /*
     * este lo usamos en el caso de que queramos
     * añadir nuevos Jsons a la resolución
     */
    QJsonModel *json_anadir_model;

    void cargarModelos();
    void cargarMapper();
    void cargarInfos();

    /*
     * aquí guardamos la id de la resolución que está escogida.
     */
    int resolucion_id;

    /*
     * aquí se guarda una lista de las ids de la tabla
     * resolutions_details, que se corresponde al campo
     * detail_id  y permite manipular las entradas de esta tabla
     */
    QList<int> ids_resolutions_details;
};

#endif // DLGRESOLUCIONES_H
