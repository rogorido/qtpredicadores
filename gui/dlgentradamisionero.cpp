#include "dlgentradamisionero.h"
#include "ui_dlgentradamisionero.h"

#include <QMdiSubWindow>
#include <QSqlQuery>

#include "dlgseleccionargeneral.h"
#include "dlgfuenteentrada.h"
#include "widgets/myqmdiarea.h"

dlgEntradaMisionero::dlgEntradaMisionero(int mision, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::dlgEntradaMisionero), mision_id(mision)
{
    ui->setupUi(this);
    mdiarea = MyQmdiArea::Instance(this);

    connect(ui->btCancelar, SIGNAL(clicked()), this, SLOT(cerrar()));
    connect(ui->btOK, SIGNAL(clicked()), this, SLOT(aceptarMisionero()));
    connect(ui->btFuente, SIGNAL(clicked()), this, SLOT(anadirFuente()));
    connect(ui->txtPersona, SIGNAL(dobleclick()), this, SLOT(anadirPersona()));
}

dlgEntradaMisionero::~dlgEntradaMisionero()
{
    delete ui;
}

void dlgEntradaMisionero::anadirPersona()
{
    dlgSeleccionarGeneral *seleccionar = new dlgSeleccionarGeneral(PERSONA, this);
    connect(seleccionar, SIGNAL(personaEscogidaSignal(Persona)), this, SLOT(recibirPersona(Persona)));

    QMdiSubWindow *window = mdiarea->addSubWindow(seleccionar);
    window->show();
}

void dlgEntradaMisionero::anadirFuente()
{
    dlgFuenteEntrada *dlgfuente = new dlgFuenteEntrada(this);
    connect(dlgfuente, SIGNAL(signalFuente(fuente)), this, SLOT(recibirFuente(fuente)));

    dlgfuente->show();
}

void dlgEntradaMisionero::recibirPersona(Persona persona)
{
    persona_id = persona.getId();
    ui->txtPersona->setText(persona.getNombreCompleto());
}

void dlgEntradaMisionero::recibirFuente(fuente datoobra)
{
    QJsonObject json_datosconcretos;

    fuente_recibida = true;

    json_datosconcretos.insert("source_id", QJsonValue(datoobra.titulo));
    json_datosconcretos.insert("volume", datoobra.tomo);
    json_datosconcretos.insert("pages", datoobra.paginas);

    fuentedatos->insert("source", json_datosconcretos);

}

void dlgEntradaMisionero::cerrar()
{
    parentWidget()->close();
}

void dlgEntradaMisionero::aceptarMisionero()
{

}

void dlgEntradaMisionero::borrarCampos()
{
    persona_id = 0;
    ui->txtPersona->clear();

    ui->ckLlego->setCheckState(Qt::Unchecked);
    ui->ckRegreso->setCheckState(Qt::Unchecked);
    ui->ckVolverMirar->setCheckState(Qt::Unchecked);

    ui->txtNotas->setText("");

    /*
     * no borramos el punto fuentedatos
     * pque ahora no sé cómo borrar un pointer
     * pero en principio conesta variable debería ser
     * suficiente
     */
    //fuentedatos = QJsonObject();
    fuente_recibida = false;

}
