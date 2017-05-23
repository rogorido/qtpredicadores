#include "dlgfuenteentrada.h"
#include "ui_dlgfuenteentrada.h"

#include <QSqlQueryModel>
#include <QCompleter>

dlgFuenteEntrada::dlgFuenteEntrada(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::dlgFuenteEntrada)
{
    ui->setupUi(this);

    m_obras = new QSqlQueryModel(this);
    m_obras->setQuery("SELECT title FROM general.sources ORDER BY title");

    m_obras_completer = new QCompleter(m_obras, this);
    m_obras_completer->setCompletionColumn(0);
    m_obras_completer->setCaseSensitivity(Qt::CaseInsensitive);

    ui->txtObra->setCompleter(m_obras_completer);
}

dlgFuenteEntrada::~dlgFuenteEntrada()
{
    delete ui;
}

void dlgFuenteEntrada::accept()
{
    int obra;
    QString tomo = ui->txtTomo->text();
    QString paginas = ui->txtPaginas->text();
    QModelIndex idx;

    fuente datosobra;

    idx = m_obras_completer->model()->index(m_obras_completer->currentIndex().row(), 0);
    obra = idx.data().toInt();

    datosobra.titulo = obra;
    datosobra.tomo = tomo;
    datosobra.paginas = paginas;

    emit(signalFuente(datosobra));

}
