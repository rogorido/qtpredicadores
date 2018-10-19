#include "dlggestioncasas.h"
#include "ui_dlggestioncasas.h"

#include <QDebug>
#include <QMdiSubWindow>
#include <QSqlQueryModel>

#include "src/models/casasmodel.h"

#include "src/models/sqlfiltrogestor.h"
#include "src/objs/proxynombres.h"
#include "dlgnuevacasa.h"
#include "dlgseleccionargeneral.h"
#include "src/widgets/myqmdiarea.h"

const QString sql_general = "SELECT * from vistas.houses_alternatives";
const QString sql_tiposcasas = "SELECT DISTINCT type_house FROM houses WHERE type_house IS NOT NULL ORDER BY type_house";

dlgGestionCasas::dlgGestionCasas(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::dlgGestionCasas)
{
    ui->setupUi(this);
    mdiarea = MyQmdiArea::Instance(this);

    sqlactivo = sql_general;

    sql_gestor = new SqlFiltroGestor(sql_general, this);

    connect(sql_gestor, SIGNAL(actualizadoSqlFiltroGestor(QString)), this, SLOT(actualizarSql(QString)));

    cargarModelos();

    connect(ui->twCasas->selectionModel(), SIGNAL(currentRowChanged(QModelIndex, QModelIndex)),
            this, SLOT(seleccionarCasa(QModelIndex)));
    connect(ui->txtFiltro, SIGNAL(textEdited(QString)), this, SLOT(actualizarFiltro(QString)));

    connect(ui->btCerrar, SIGNAL(clicked(bool)), this, SLOT(cerrar()));

    ui->twCasas->verticalHeader()->hide();
}

dlgGestionCasas::~dlgGestionCasas()
{
    delete ui;
}

void dlgGestionCasas::actualizarFiltro(const QString filtro)
{
    if (filtro.length() > 2) {
        proxy_casas->setFilterRegExp(QRegExp(filtro, Qt::CaseInsensitive, QRegExp::FixedString));
        ui->twCasas->resizeRowsToContents();
        ui->twCasas->resizeColumnsToContents();
        //contarTotal();
    }
    else
    {
        proxy_casas->setFilterRegExp(QRegExp("", Qt::CaseInsensitive, QRegExp::FixedString));
        ui->twCasas->resizeRowsToContents();
        ui->twCasas->resizeColumnsToContents();
        //contarTotal();
    }
}

void dlgGestionCasas::seleccionarCasa(const QModelIndex &idx)
{
    Q_UNUSED(idx)
    // NOTE: aquí no estoy usando lo de idx... he cogido este código de lo de modificar persona...
    QModelIndex indice= proxy_casas->index(ui->twCasas->currentIndex().row(), 0);
    if (!indice.isValid())
        return;

    int id = m_casas->data(proxy_casas->mapToSource(indice), Qt::DisplayRole).toInt();
    qDebug() << "estamos escogiendo la casa: " << id;

    //QString mensaje = QString("Persona_id: ") + QString::number(id);
    //emit infoPersonaSeleccionada(mensaje);


}

void dlgGestionCasas::actualizarModeloTrasCasaIntroducida()
{
    m_casas->setQuery(sqlactivo);
}

void dlgGestionCasas::actualizarSql(QString s)
{
    sqlactivo = s;

    m_casas->setQuery(sqlactivo);
    ui->twCasas->resizeColumnsToContents();
    ui->twCasas->resizeRowsToContents();

    emit infoBarra(m_casas->rowCount());

}

void dlgGestionCasas::cerrar()
{
    parentWidget()->close();
}

void dlgGestionCasas::cargarModelos(){

    m_casas = CasasModel::InstanceModel();
    m_casas->setQuery(sqlactivo);

    proxy_casas = new ProxyNombres(CASASGESTION, this);
    proxy_casas->setSourceModel(m_casas);

    ui->twCasas->setModel(proxy_casas);
    ui->twCasas->hideColumn(0);
    ui->twCasas->hideColumn(6);
    ui->twCasas->hideColumn(12);

    ui->twCasas->setSortingEnabled(true);
    ui->twCasas->resizeColumnsToContents();
    ui->twCasas->resizeRowsToContents();
    ui->twCasas->setAlternatingRowColors(true);
    ui->twCasas->setSelectionMode(QAbstractItemView::SingleSelection);
    ui->twCasas->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->twCasas->horizontalHeader()->setStretchLastSection(true);

    proxy_casas->sort(1, Qt::AscendingOrder);

    ui->twCasas->resizeColumnsToContents();
    ui->twCasas->resizeRowsToContents();

    // escogemos la primera línea del modelo...
    QModelIndex index = proxy_casas->index(0,0);
    if (index.isValid()) {
        ui->twCasas->setCurrentIndex(index);
    }

    m_tiposcasas = new QSqlQueryModel(this);
    m_tiposcasas->setQuery(sql_tiposcasas);

    ui->cbTipos->setModel(m_tiposcasas);
    ui->cbTipos->setCurrentIndex(-1);

}

void dlgGestionCasas::generarSQLProvincias()
{
    QString sql;

    if (provincias_escogidas.size() == 0) {
        sql_gestor->quitarFiltro("provincias");
        return;
    }

    // construimos la SQL
    for (int var = 0; var < provincias_escogidas.size(); ++var) {
        sql += QString("province_id = ") + QString::number(provincias_escogidas.at(var).id) + QString(" OR ");
    }
    // borramos el último OR
    sql.chop(4);
    sql = QString("house_id IN (SELECT DISTINCT house_id FROM houses WHERE ") + sql + QString(")");

    qDebug() << "el filtro es: " << sql;

    sql_gestor->anadirFiltro("provincias", sql);

}

void dlgGestionCasas::generarSQLTipos()
{
    QString sql;

    if (tipos_escogidos.size() == 0) {
        sql_gestor->quitarFiltro("tipos");
        return;
    }

    foreach (const QString &value, tipos_escogidos) {
        qDebug() << value;
        sql += QString("type_house = '") + value + QString("' OR ");
    }
    // borramos el último OR
    sql.chop(4);
    sql = QString("house_id IN (SELECT DISTINCT house_id FROM houses WHERE ") + sql + QString(")");

    qDebug() << "el filtro es: " << sql;

    sql_gestor->anadirFiltro("tipos", sql);

}

void dlgGestionCasas::on_btModificar_clicked()
{
    QModelIndex indice= proxy_casas->index(ui->twCasas->currentIndex().row(), 0);
    if (!indice.isValid())
        return;

    int id = m_casas->data(proxy_casas->mapToSource(indice), Qt::DisplayRole).toInt();
    qDebug() << "escogido: " << id;

    dlgCasaAModificar = new dlgNuevaCasa(this, id);
    QMdiSubWindow *window = mdiarea->addSubWindow(dlgCasaAModificar);
    connect(dlgCasaAModificar, SIGNAL(casaIntroducida()), this, SLOT(actualizarModeloTrasCasaIntroducida));
    window->show();
}

void dlgGestionCasas::on_rbFemeninas_toggled(bool checked)
{
    if (checked) {
        sql_gestor->anadirFiltro("femeninas", "men = FALSE");
        sql_gestor->quitarFiltro("masculinas");
    }
    else
        sql_gestor->quitarFiltro("femeninas");

}

void dlgGestionCasas::on_rbMasculinas_toggled(bool checked)
{
    if (checked) {
        sql_gestor->anadirFiltro("masculinas", "men = TRUE");
        sql_gestor->quitarFiltro("femeninas");
    }
    else
        sql_gestor->quitarFiltro("masculinas");

}

void dlgGestionCasas::on_rbTodas_toggled(bool checked)
{
    Q_UNUSED(checked)

    sql_gestor->quitarFiltro("masculinas");
    sql_gestor->quitarFiltro("femeninas");

}

void dlgGestionCasas::on_btAnadirProvincia_clicked()
{
    dlgSeleccionarGeneral *dlgseleccionar = new dlgSeleccionarGeneral(PROVINCIA, true, this);

    connect(dlgseleccionar, SIGNAL(provinciaEscogidaSignal(Provincia)), this, SLOT(recibirProvincia(Provincia)));
    QMdiSubWindow *window = mdiarea->addSubWindow(dlgseleccionar);
    window->show();

}

void dlgGestionCasas::recibirProvincia(const Provincia provincia)
{
    elementopareado nuevaprovincia;

    nuevaprovincia.id = provincia.getId();
    nuevaprovincia.elemento = provincia.getNombre();

    provincias_escogidas.append(nuevaprovincia);
    QListWidgetItem *item = new QListWidgetItem(nuevaprovincia.elemento, ui->lwProvincias);
    Q_UNUSED(item)

    generarSQLProvincias();

}

void dlgGestionCasas::on_btResetearFiltros_clicked()
{
    ui->lwProvincias->clear();
    provincias_escogidas.clear();
    ui->lwTipos->clear();
    tipos_escogidos.clear();

    ui->rbTodas->setChecked(true);

    sql_gestor->borrarFiltros();

}

void dlgGestionCasas::on_btQuitarTodasProvincias_clicked()
{
    ui->lwProvincias->clear();
    provincias_escogidas.clear();
    sql_gestor->quitarFiltro("provincias");

}

void dlgGestionCasas::on_btAnadirTipo_clicked()
{
    QString tipo_escogido;

    if (ui->cbTipos->currentIndex() != -1) {

        tipo_escogido = ui->cbTipos->currentText();

        if (!tipos_escogidos.contains(tipo_escogido)) {

            QListWidgetItem *item = new QListWidgetItem(tipo_escogido, ui->lwTipos);
            Q_UNUSED(item)

            tipos_escogidos << tipo_escogido;

            generarSQLTipos();
        }
    }
}

void dlgGestionCasas::on_btQuitarTipo_clicked()
{
    QModelIndex idx = ui->lwTipos->currentIndex();

    if (!idx.isValid())
        return;

    QString valor = idx.data().toString();

    ui->lwTipos->takeItem(ui->lwTipos->currentRow());
    tipos_escogidos.remove(valor);

    generarSQLTipos();

}

void dlgGestionCasas::on_btQuitarTiposTodos_clicked()
{
    ui->lwTipos->clear();
    tipos_escogidos.clear();

    sql_gestor->quitarFiltro("tipos");
}

void dlgGestionCasas::on_btQuitarProvincia_clicked()
{
    QModelIndex idx = ui->lwProvincias->currentIndex();

    if (!idx.isValid())
        return;

    QString valor = idx.data().toString();

    ui->lwProvincias->takeItem(ui->lwProvincias->currentRow());

    for (int i = 0; i < provincias_escogidas.size(); ++i) {
      if(provincias_escogidas.at(i).elemento == valor){
        provincias_escogidas.removeAt(i);
        break;
      }
     }

    generarSQLProvincias();
}
