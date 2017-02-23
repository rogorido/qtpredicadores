#include "dlgnuevaobra.h"
#include "ui_dlgnuevaobra.h"

#include <QSqlQueryModel>
#include <QCompleter>

dlgNuevaObra::dlgNuevaObra(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::dlgNuevaObra)
{
    ui->setupUi(this);
}

dlgNuevaObra::~dlgNuevaObra()
{
    delete ui;
}

void dlgNuevaObra::cargarCompleters(){

    m_lugaresoriginales = new QSqlQueryModel(this);
    m_lugaresoriginales->setQuery("SELECT lugar_impresion_original FROM obras.obras ORDER BY lugar_impresion_original");

    c_lugaresoriginales = new QCompleter(m_lugaresoriginales, this);
    c_lugaresoriginales->setCompletionColumn(0);
    c_lugaresoriginales->setCaseSensitivity(Qt::CaseInsensitive);
    ui->txtLugarOriginalImpresion->setCompleter(c_lugaresoriginales);

    m_editores = new QSqlQueryModel(this);
    m_editores->setQuery("SELECT editor FROM obras.obras ORDER BY editor");

    c_editor = new QCompleter(m_editores, this);
    c_editor->setCompletionColumn(0);
    c_editor->setCaseSensitivity(Qt::CaseInsensitive);
    ui->txtEditor->setCompleter(c_editor);

    m_idiomas = new QSqlQueryModel(this);
    m_idiomas->setQuery("SELECT idioma FROM obras.obras ORDER BY idioma");

    c_idiomas = new QCompleter(m_idiomas, this);
    c_idiomas->setCompletionColumn(0);
    c_idiomas->setCaseSensitivity(Qt::CaseInsensitive);
    ui->txtIdioma->setCompleter(c_idiomas);


}
