#include "dlgnuevadiocesis.h"
#include "ui_dlgnuevadiocesis.h"

#include <QMessageBox>

#include "gui/dlgseleccionargeneral.h"
#include "models/diocesismodel.h"

dlgNuevaDiocesis::dlgNuevaDiocesis(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::dlgNuevaDiocesis)
{
    ui->setupUi(this);

    m_diocesis = DiocesisModel::InstanceModel();

    connect(ui->btCancelar, SIGNAL(clicked(bool)), this, SLOT(close()));
    connect(ui->btOK, SIGNAL(clicked(bool)), this, SLOT(aceptarDiocesis()));

}

dlgNuevaDiocesis::~dlgNuevaDiocesis()
{
    delete ui;
}

void dlgNuevaDiocesis::aceptarDiocesis()
{
    Diocesis *diocesis = new Diocesis();

    QString nombre = ui->txtNombre->text();
    QString nombre_latin = ui->txtNombreLatin->text();
    bool archidiocesis = ui->ckArchidiocesis->checkState();
    bool existe = ui->ckExiste->checkState();

    diocesis->setNombre(nombre);
    diocesis->setNombreLatin(nombre_latin);
    diocesis->setArchidiosis(archidiocesis);
    diocesis->setExistente(existe);

    if (sufraganea != 0)
        diocesis->setSufraganea(sufraganea);

    if (lugar != 0 )
        diocesis->setLugar(lugar);

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

    sufraganea = 0;
    lugar = 0;
}

void dlgNuevaDiocesis::anadirLugar()
{
    dlgSeleccionarGeneral *seleccionlugar = new dlgSeleccionarGeneral(LUGAR, this);
    seleccionlugar->show();

    connect(seleccionlugar, SIGNAL(lugarEscogidoSignal(Lugar)), this, SLOT(recibirLugar(Lugar)));

}

void dlgNuevaDiocesis::anadirArchiDiocesis()
{

}

void dlgNuevaDiocesis::recibirLugar(Lugar lugarrecibido)
{
    lugar = lugarrecibido.getId();
    ui->txtLugar->setText(lugarrecibido.getLugar());
}

void dlgNuevaDiocesis::recibirArchiDiocesis(Diocesis diocesis)
{

}
