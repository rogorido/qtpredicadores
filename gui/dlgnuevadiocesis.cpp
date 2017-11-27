#include "dlgnuevadiocesis.h"
#include "ui_dlgnuevadiocesis.h"

#include <QMessageBox>
#include <QStringList>
#include <QCompleter>
#include <QJsonObject>
#include <QMdiSubWindow>
#include <QDebug>

#include "gui/dlgseleccionargeneral.h"
#include "models/diocesismodel.h"
#include "models/lugaresmodel.h"
#include "widgets/myqmdiarea.h"
#include "objs/notas.h"

dlgNuevaDiocesis::dlgNuevaDiocesis(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::dlgNuevaDiocesis)
{
    ui->setupUi(this);
    cargarUI();
}

dlgNuevaDiocesis::dlgNuevaDiocesis(int diocesis, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::dlgNuevaDiocesis),
    modificando(true),
    diocesis_modificando(diocesis)
{
    ui->setupUi(this);
    cargarUI();
    cargarDiocesis();
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
    bool infidelibus = ui->ckInfidelibus->checkState();
    bool titular_see = ui->ckTitularSee->checkState();
    QString motivo_desaparicion = ui->txtMotivoDesaparicion->text();

    diocesis->setNombre(nombre);
    diocesis->setNombreLatin(nombre_latin);
    diocesis->setArchidiosis(archidiocesis);
    diocesis->setExistente(existe);
    diocesis->setSufraganea(sufraganea);
    diocesis->setLugar(lugar);
    diocesis->setInfidelibus(infidelibus);
    diocesis->setTitularSee(titular_see);
    diocesis->setMotivoDesaparicion(motivo_desaparicion);

    /*
     * creamos un QJonObject con los datos de la página gcatholic
     * pero solo si hemos modficiado el txtURL o si hemos marcado
     * el campo ckBuscado, o lo de la fecha de fundación...
     */

    if (!ui->txtURL->text().isEmpty() ||
            ui->ckBuscado->checkState() == Qt::Checked ||
            ui->spFundacion->value() != 0) {

        datos_concretos.insert("buscado", QJsonValue(ui->ckBuscado->isChecked()));
        datos_concretos.insert("url", ui->txtURL->text());
        if (ui->spParroquias != 0 )
            datos_concretos.insert("parishes_number", QJsonValue(ui->spParroquias->value()));
        if (ui->spSuperficie != 0 )
            datos_concretos.insert("area", QJsonValue(ui->spSuperficie->value()));
        if (ui->spFundacion != 0 )
            datos_concretos.insert("foundation", QJsonValue(ui->spFundacion->value()));

        otros_datos.insert("gcatholic", datos_concretos);
        diocesis->setOtrosDatos(otros_datos);
    }

    if (ui->wdNotas->haCambiado())
        diocesis->setNota(ui->wdNotas->getNotas());

    if (!m_diocesis->AnadirDiocesis(diocesis)){
        int ret = QMessageBox::warning(this, "Error al introducir la diócesis",
                                       "Error al introducir la diócesis en la BD");
        Q_UNUSED(ret)
        return;
    }
    else {
        borrarCampos();
    }

}

void dlgNuevaDiocesis::borrarCampos()
{
    ui->txtNombre->setText("");
    ui->txtNombreLatin->setText("");
    ui->txtLugar->setText("");
    ui->txtArchidiocesis->setText("");
    ui->txtMotivoDesaparicion->setText("");
    ui->ckArchidiocesis->setCheckState(Qt::Unchecked);
    ui->ckExiste->setCheckState(Qt::Unchecked);
    ui->ckInfidelibus->setCheckState(Qt::Unchecked);
    ui->ckTitularSee->setCheckState(Qt::Unchecked);
    ui->spParroquias->setValue(0);
    ui->spSuperficie->setValue(0);
    ui->spFundacion->setValue(0);

    // lo de json de gcatholic
    ui->ckBuscado->setCheckState(Qt::Unchecked);
    ui->txtURL->setText("");
    ui->spParroquias->setValue(0);

    ui->wdNotas->reiniciar();

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
        Q_UNUSED(ret)
        return;
    }
    dlgSeleccionarGeneral *seleccion = new dlgSeleccionarGeneral(DIOCESIS, this);
    connect(seleccion, SIGNAL(diocesisEscogidaSignal(Diocesis)), this, SLOT(recibirArchiDiocesis(Diocesis)));

    QMdiSubWindow *window = mdiarea->addSubWindow(seleccion);
    window->show();
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

void dlgNuevaDiocesis::cerrar()
{
    parentWidget()->close();
}

void dlgNuevaDiocesis::cargarUI()
{

    mdiarea = MyQmdiArea::Instance(this);

    m_diocesis = DiocesisModel::InstanceModel();
    m_lugares = LugaresModel::InstanceModel();

    lista_motivos = new QStringList();
    lista_motivos->append("Unida a otra");
    lista_motivos->append("Eliminada");

    /*
     * NOTE: no sé por qué narices esto tengo que
     * dereferenciarlo...
     */
    motivos_completer = new QCompleter(*lista_motivos, this);
    ui->txtMotivoDesaparicion->setCompleter(motivos_completer);

    connect(ui->btCancelar, SIGNAL(clicked(bool)), this, SLOT(cerrar()));
    connect(ui->btOK, SIGNAL(clicked(bool)), this, SLOT(aceptarDiocesis()));
    connect(ui->txtArchidiocesis, SIGNAL(dobleclick()), this, SLOT(anadirArchiDiocesis()));
    connect(ui->txtLugar, SIGNAL(dobleclick()), this, SLOT(anadirLugar()));

    ui->txtNombre->setFocus();

}

void dlgNuevaDiocesis::cargarDiocesis()
{
    QJsonObject otros_datos;
    QJsonObject gcatholic;
    QJsonObject json_notas;
    Lugar place;

    Diocesis *diocesisModificada = m_diocesis->devolverDiocesis(diocesis_modificando);

    ui->txtNombre->setText(diocesisModificada->getNombre());
    ui->ckArchidiocesis->setChecked(diocesisModificada->getArchidiocesis());
    ui->ckExiste->setChecked(diocesisModificada->getExisteHoy());
    ui->ckInfidelibus->setChecked(diocesisModificada->getInfidelibus());
    ui->ckTitularSee->setChecked(diocesisModificada->getTitularSee());

    sufraganea = diocesisModificada->getSufraganea();
    lugar = diocesisModificada->getLugar();

    ui->txtMotivoDesaparicion->setText(diocesisModificada->getMotivoDesaparicion());

    otros_datos = diocesisModificada->getOtrosDatos();

    // extramos lo de gcatholic
    gcatholic = otros_datos["gcatholic"].toObject();
    ui->ckBuscado->setChecked(gcatholic.value("buscado").toBool());
    ui->txtURL->setText(gcatholic.value("url").toString());
    ui->spFundacion->setValue(gcatholic.value("foundation").toInt());
    ui->spParroquias->setValue(gcatholic.value("parishes_number").toInt());
    ui->spSuperficie->setValue(gcatholic.value("area").toInt());

    // extramos las notas
    json_notas = otros_datos["nota"].toObject();
    if (!json_notas.isEmpty())
        ui->wdNotas->importNota(json_notas);

    /*
     * creamos la archidiócesis y la pasamos, entiendo que hay
     * que dereferenciarla... Pq aquí creamos un pointer (por qué lo hago
     * esto como pointer?), y en el método este necesitamos el objeto como tal
     */
    if (diocesisModificada->getSufraganea() != 0) {
        Diocesis *archidiocesis = m_diocesis->devolverDiocesis(diocesisModificada->getSufraganea());
        recibirArchiDiocesis(*archidiocesis);
    }

    place = m_lugares->devolverLugar(lugar);
    recibirLugar(place);

}
