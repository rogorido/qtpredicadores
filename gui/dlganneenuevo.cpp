#include "dlganneenuevo.h"
#include "ui_dlganneenuevo.h"

#include <QSqlQueryModel>
#include <QCompleter>
#include <QMdiSubWindow>
#include <QTableWidget>

#include "widgets/myqmdiarea.h"
#include "dlgseleccionargeneral.h"

QString sql_autores = "SELECT DISTINCT author_initial_text FROM annee_general ORDER BY author_initial_text";
QString sql_temas = "SELECT DISTINCT main_theme FROM annee_general ORDER BY main_theme";

dlgAnneeNuevo::dlgAnneeNuevo(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::dlgAnneeNuevo)
{
    ui->setupUi(this);
    mdiarea = MyQmdiArea::Instance(this);

    connect(ui->btCancelar, SIGNAL(clicked()), this, SLOT(cerrar()));
    connect(ui->btOK, SIGNAL(clicked()), this, SLOT(aceptarAnnee()));
    connect(ui->btAnadirPersonaPrincipal, SIGNAL(clicked(bool)), this, SLOT(anadirPersona()));
    connect(ui->btAnadirPersonaAdicional, SIGNAL(clicked(bool)), this, SLOT(anadirPersonaAdicional()));
    connect(ui->btQuitarPersonaAdicional, SIGNAL(clicked(bool)), this, SLOT(quitarPersonaAdicional()));
    connect(ui->btAnadirMeditacion, SIGNAL(clicked(bool)), this, SLOT(anadirMeditacion()));
    connect(ui->btQuitarMeditacion, SIGNAL(clicked(bool)), this, SLOT(quitarMeditacion()));
    connect(ui->btTemas, SIGNAL(clicked(bool)), this, SLOT(anadirCategoriasMeditacion()));

    ui->twMeditaciones->setColumnCount(3);
    ui->twPersonasAdicionales->setColumnCount(1);
    ui->lblPersonaPrincipal->setText("");

    cargarModelos();
}

dlgAnneeNuevo::~dlgAnneeNuevo()
{
    delete ui;
}

void dlgAnneeNuevo::cerrar()
{
    parentWidget()->close();
}

void dlgAnneeNuevo::aceptarAnnee()
{

}

void dlgAnneeNuevo::anadirPersona()
{
    dlgSeleccionarGeneral *seleccionar = new dlgSeleccionarGeneral(PERSONA, this);
    connect(seleccionar, SIGNAL(personaEscogidaSignal(Persona)), this, SLOT(recibirPersonaPrincipal(Persona)));

    QMdiSubWindow *window = mdiarea->addSubWindow(seleccionar);
    window->show();
}

void dlgAnneeNuevo::anadirPersonaAdicional()
{
    dlgSeleccionarGeneral *seleccionar = new dlgSeleccionarGeneral(PERSONA, this);
    connect(seleccionar, SIGNAL(personaEscogidaSignal(Persona)), this, SLOT(recibirPersonaAdicional(Persona)));

    QMdiSubWindow *window = mdiarea->addSubWindow(seleccionar);
    window->show();

}

void dlgAnneeNuevo::quitarPersonaAdicional()
{
    QModelIndex idx = ui->twPersonasAdicionales->currentIndex();

    if (!idx.isValid())
        return;

    int row = ui->twPersonasAdicionales->currentRow();
    ui->twPersonasAdicionales->removeRow(row);

    personas_adicionales.removeAt(row);

}

void dlgAnneeNuevo::anadirMeditacion()
{
    m_meditacion meditacion;
    QString categorias_lista; // esto es para el widgetitem

    meditacion.numeracion = ui->spNumeroMeditacion->value();
    meditacion.pensamiento = ui->txtMeditacion->text();
    meditacion.categorias = categorias_seleccionadas;

    meditaciones.append(meditacion);

    /* añadimos un elem a la tabla: este es el mejor método? */
    QTableWidgetItem *item1 = new QTableWidgetItem(QString::number(meditacion.numeracion));
    QTableWidgetItem *item2 = new QTableWidgetItem(meditacion.pensamiento);

    // lo de las categorías es más complicado...
    QHashIterator<int, QString> i(categorias_seleccionadas);
    while (i.hasNext()) {
        i.next();
        categorias_lista = categorias_lista + i.value()+ QString(", ");
        //cout << i.key() << ": " << i.value() << endl;
    }
    QTableWidgetItem *item3 = new QTableWidgetItem(categorias_lista);

    //this will give the present number of rows available.
    int insertRow = ui->twMeditaciones->rowCount();
    //insert the row at the bottom of the table widget - using.
    ui->twMeditaciones->insertRow(insertRow);

    ui->twMeditaciones->setItem(insertRow, 0, item1);
    ui->twMeditaciones->setItem(insertRow, 1, item2);
    ui->twMeditaciones->setItem(insertRow, 2, item3);

    ui->twMeditaciones->resizeColumnsToContents();
    ui->twMeditaciones->resizeRowsToContents();

    // tenemos que borrar algunas cosas
    ui->txtMeditacion->setText("");
    categorias_seleccionadas.clear();

}

void dlgAnneeNuevo::quitarMeditacion()
{
    QModelIndex idx = ui->twMeditaciones->currentIndex();

    if (!idx.isValid())
        return;

    int row = ui->twMeditaciones->currentRow();
    ui->twMeditaciones->removeRow(row);

    meditaciones.removeAt(row);

}

void dlgAnneeNuevo::anadirCategoriasMeditacion()
{
    dlgSeleccionarGeneral *seleccionar = new dlgSeleccionarGeneral(TEMA, this);
    connect(seleccionar, SIGNAL(temaEscogidoSignal(Tema)), this, SLOT(recibirTema(Tema)));

    QMdiSubWindow *window = mdiarea->addSubWindow(seleccionar);
    window->show();
}

void dlgAnneeNuevo::recibirPersonaPrincipal(Persona persona)
{
    persona_id = persona.getId();
    ui->lblPersonaPrincipal->setText(persona.getNombreCompleto());
}

void dlgAnneeNuevo::recibirPersonaAdicional(Persona persona)
{
    otrapersona nueva_persona;

    nueva_persona.id = persona.getId();
    nueva_persona.nombre = persona.getNombreCompleto();

    personas_adicionales.append(nueva_persona);

    /* añadimos un elem a la tabla: este es el mejor método? */
    QTableWidgetItem *item = new QTableWidgetItem(nueva_persona.nombre);
    //this will give the present number of rows available.
    int insertRow = ui->twPersonasAdicionales->rowCount();
    //insert the row at the bottom of the table widget - using.
    ui->twPersonasAdicionales->insertRow(insertRow);

    ui->twPersonasAdicionales->setItem(insertRow, 0, item);

    ui->twPersonasAdicionales->resizeColumnsToContents();
    ui->twPersonasAdicionales->resizeRowsToContents();

}

void dlgAnneeNuevo::recibirTema(Tema tema)
{
    categorias_seleccionadas.insert(tema.getId(), tema.getTema());
}

void dlgAnneeNuevo::cargarModelos()
{
    m_autores = new QSqlQueryModel(this);
    m_autores->setQuery(sql_autores);

    m_autores_completer = new QCompleter(this);
    m_autores_completer->setModel(m_autores);
    m_autores_completer->setCaseSensitivity(Qt::CaseInsensitive);

    ui->txtAutorPensamiento->setCompleter(m_autores_completer);

    m_temasprincipales = new QSqlQueryModel(this);
    m_temasprincipales->setQuery(sql_temas);

    m_temasprincipales_completer = new QCompleter(this);
    m_temasprincipales_completer->setModel(m_temasprincipales);
    m_temasprincipales_completer->setCaseSensitivity(Qt::CaseInsensitive);

    ui->txtTemaPrincipal->setCompleter(m_temasprincipales_completer);
}
