#include "dlgnuevareedicion.h"
#include "ui_dlgnuevareedicion.h"

#include <QMdiSubWindow>
#include <QSqlQueryModel>
#include <QCompleter>

#include "gui/dlgseleccionargeneral.h"
#include "widgets/myqmdiarea.h"

const QString sql_editores = "SELECT DISTINCT details->>'editor' FROM works_details ORDER BY 1";
const QString sql_lenguas = "SELECT DISTINCT details->>'language' FROM works_details ORDER BY 1";
const QString sql_formats = "SELECT DISTINCT details->>'format' FROM works_details ORDER BY 1";


dlgNuevaReedicion::dlgNuevaReedicion(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::dlgNuevaReedicion)
{
    ui->setupUi(this);
    mdiarea = MyQmdiArea::Instance(this);

    connect(ui->txtLugar, SIGNAL(dobleclick()), this, SLOT(anadirLugar()));

    cargarModelos();

}

dlgNuevaReedicion::~dlgNuevaReedicion()
{
    delete ui;
}

void dlgNuevaReedicion::aceptadaReedicion()
{
    QJsonObject datos;

    datos.insert("tipo", QJsonValue(QString("reedición")));

    if (elem_lugar.id != 0)
        datos.insert("lugar", QJsonValue(elem_lugar.id));

    if (ui->spYear->value() != 1400)
        datos.insert("year", QJsonValue(ui->spYear->value()));

    if (!ui->txtEditor->text().isEmpty())
        datos.insert("editor", QJsonValue(ui->txtEditor->text()));

    if (ui->ckModificado->checkState() != Qt::Unchecked)
        datos.insert("modified", QJsonValue(true));

    if (ui->ckOtherAuthor->checkState() != Qt::Unchecked)
        datos.insert("other_author", QJsonValue(true));

    if (ui->ckTranslation->checkState() != Qt::Unchecked)
        datos.insert("translation", QJsonValue(true));

    if (!ui->txtLanguage->text().isEmpty())
        datos.insert("translation_into", QJsonValue(ui->txtLanguage->text()));

    if (ui->ckAutoresAnadidos->checkState() != Qt::Unchecked)
        datos.insert("authors_added", QJsonValue(true));

    if (!ui->txtFormat->text().isEmpty())
        datos.insert("format", QJsonValue(ui->txtFormat->text()));

    emit aceptarReedicion(datos);

}

void dlgNuevaReedicion::anadirLugar()
{
    dlgSeleccionarGeneral *seleccionar = new dlgSeleccionarGeneral(LUGAR, true, this);
    connect(seleccionar, SIGNAL(lugarEscogidoSignal(Lugar)), this, SLOT(recibirLugar(Lugar)));

    QMdiSubWindow *window = mdiarea->addSubWindow(seleccionar);
    window->show();
}

void dlgNuevaReedicion::cargarModelos()
{
    m_editores = new QSqlQueryModel(this);
    m_editores->setQuery(sql_editores);

    m_editores_completer = new QCompleter(m_editores);
    m_editores_completer->setCompletionColumn(0);
    m_editores_completer->setCaseSensitivity(Qt::CaseInsensitive);
    ui->txtEditor->setCompleter(m_editores_completer);

    m_lenguas = new QSqlQueryModel(this);
    m_lenguas->setQuery(sql_lenguas);
    m_lenguas_completer = new QCompleter(m_lenguas);
    m_lenguas_completer->setCompletionColumn(0);
    m_lenguas_completer->setCaseSensitivity(Qt::CaseInsensitive);
    ui->txtLanguage->setCompleter(m_lenguas_completer);

    m_formatos = new QSqlQueryModel(this);
    m_formatos->setQuery(sql_formats);
    m_formatos_completer = new QCompleter(m_formatos);
    m_formatos_completer->setCompletionColumn(0);
    m_formatos_completer->setCaseSensitivity(Qt::CaseInsensitive);
    ui->txtFormat->setCompleter(m_formatos_completer);

}

void dlgNuevaReedicion::on_pbOK_clicked()
{
    aceptadaReedicion();
}

void dlgNuevaReedicion::on_pbCancelar_clicked()
{
    parentWidget()->close();
}

void dlgNuevaReedicion::recibirLugar(Lugar lugar)
{
    elem_lugar.id = lugar.getId();

    ui->txtLugar->setText(lugar.getLugar());
}

void dlgNuevaReedicion::on_pbQuitarLugar_clicked()
{
    elem_lugar.id = 0;
    elem_lugar.elemento = "";

    ui->txtLugar->setText("");
}
