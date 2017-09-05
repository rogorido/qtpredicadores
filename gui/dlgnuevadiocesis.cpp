#include "dlgnuevadiocesis.h"
#include "ui_dlgnuevadiocesis.h"

#include <QMessageBox>
#include <QJsonObject>
#include <QMdiSubWindow>
#include <QDebug>

#include "gui/dlgseleccionargeneral.h"
#include "models/diocesismodel.h"
#include "widgets/myqmdiarea.h"

dlgNuevaDiocesis::dlgNuevaDiocesis(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::dlgNuevaDiocesis)
{
    ui->setupUi(this);

    mdiarea = MyQmdiArea::Instance(this);

    m_diocesis = DiocesisModel::InstanceModel();

    connect(ui->btCancelar, SIGNAL(clicked(bool)), this, SLOT(close()));
    connect(ui->btOK, SIGNAL(clicked(bool)), this, SLOT(aceptarDiocesis()));
    connect(ui->txtArchidiocesis, SIGNAL(dobleclick()), this, SLOT(anadirArchiDiocesis()));
    connect(ui->txtLugar, SIGNAL(dobleclick()), this, SLOT(anadirLugar()));

}

dlgNuevaDiocesis::~dlgNuevaDiocesis()
{
    delete ui;
}

void dlgNuevaDiocesis::aceptarDiocesis()
{
    Diocesis *diocesis = new Diocesis();

    /*
     * tenemos dos, pq realmente lo metemos de esta forma:
     * {gcatholic: {datos, etc.}}
     */
    QJsonObject otros_datos;
    QJsonObject datos_concretos;

    QString nombre = ui->txtNombre->text();
    QString nombre_latin = ui->txtNombreLatin->text();
    bool archidiocesis = ui->ckArchidiocesis->checkState();
    bool existe = ui->ckExiste->checkState();

    diocesis->setNombre(nombre);
    diocesis->setNombreLatin(nombre_latin);
    diocesis->setArchidiosis(archidiocesis);
    diocesis->setExistente(existe);
    diocesis->setSufraganea(sufraganea);
    diocesis->setLugar(lugar);

    /*
     * creamos un QJonObject con los datos de la página gcatholic
     * pero solo si hemos modficiado el txtURL o si hemos marcado
     * el campo ckBuscado
     */

    if (!ui->txtURL->text().isEmpty() || ui->ckBuscado->checkState() == Qt::Checked) {

        datos_concretos.insert("buscado", QJsonValue(ui->ckBuscado->isChecked()));
        datos_concretos.insert("url", ui->txtURL->text());
        if (ui->spParroquias != 0 )
            datos_concretos.insert("parishes_number", QJsonValue(ui->spParroquias->value()));
        if (ui->spSuperficie != 0 )
            datos_concretos.insert("area", QJsonValue(ui->spSuperficie->value()));

        otros_datos.insert("gcatholic", datos_concretos);
        diocesis->setOtrosDatos(otros_datos);
    }

    if (!m_diocesis->AnadirDiocesis(diocesis)){
        int ret = QMessageBox::warning(this, "Error al introducir la diócesis",
                                       "Error al introducir la diócesis en la BD");
        return;
    }
    else
        borrarCampos();

}

void dlgNuevaDiocesis::borrarCampos()
{
    ui->txtNombre->setText("");
    ui->txtNombreLatin->setText("");
    ui->txtLugar->setText("");
    ui->txtArchidiocesis->setText("");
    ui->ckArchidiocesis->setCheckState(Qt::Unchecked);
    ui->ckExiste->setCheckState(Qt::Unchecked);

    // lo de json de gcatholic
    ui->ckBuscado->setCheckState(Qt::Unchecked);
    ui->txtURL->setText("");
    ui->spParroquias->setValue(0);

    sufraganea = 0;
    lugar = 0;

    ui->txtNombre->setFocus();
}

void dlgNuevaDiocesis::anadirLugar()
{
    dlgSeleccionarGeneral *seleccionlugar = new dlgSeleccionarGeneral(LUGAR, this);
    connect(seleccionlugar, SIGNAL(lugarEscogidoSignal(Lugar)), this, SLOT(recibirLugar(Lugar)));

    QMdiSubWindow *window = mdiarea->addSubWindow(seleccionlugar);
    window->show();
}

void dlgNuevaDiocesis::anadirArchiDiocesis()
{
    /*
     * pongo esto pq parece que si intento abrir este formulario
     * y la vista esa está vacía me hace crash (que no entiendo por qué...)
     */
    if (m_diocesis->rowCount() < 1) {
        qDebug() << "cojones, hay: " << m_diocesis->rowCount();
        int ret = QMessageBox::warning(this, "Todavía no hay diócesis",
                                       "No hay diócesis. Introduzca alguna.");
        return;
    }
    dlgSeleccionarGeneral *seleccion = new dlgSeleccionarGeneral(DIOCESIS, this);
    seleccion->show();

    connect(seleccion, SIGNAL(diocesisEscogidaSignal(Diocesis)), this, SLOT(recibirArchiDiocesis(Diocesis)));
}

void dlgNuevaDiocesis::recibirLugar(Lugar lugarrecibido)
{
    lugar = lugarrecibido.getId();
    ui->txtLugar->setText(lugarrecibido.getLugar());
}

void dlgNuevaDiocesis::recibirArchiDiocesis(Diocesis diocesis)
{
    sufraganea = diocesis.getId();
    ui->txtArchidiocesis->setText(diocesis.getNombre());
}
