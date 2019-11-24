#include "dlgfuenteentrada.h"

#include <QCompleter>
#include <QMessageBox>
#include <QSqlQueryModel>

#include "ui_dlgfuenteentrada.h"

dlgFuenteEntrada::dlgFuenteEntrada(QWidget *parent)
    : QDialog(parent), ui(new Ui::dlgFuenteEntrada)
{
  ui->setupUi(this);

  m_obras = new QSqlQueryModel(this);
  m_obras->setQuery(
      "SELECT source_id, title FROM general.sources ORDER BY title");

  m_obras_completer = new QCompleter(m_obras, this);
  m_obras_completer->setCompletionColumn(1);
  m_obras_completer->setCaseSensitivity(Qt::CaseInsensitive);

  ui->txtObra->setCompleter(m_obras_completer);
}

dlgFuenteEntrada::~dlgFuenteEntrada() { delete ui; }

void dlgFuenteEntrada::accept()
{
  int obra;
  QString tomo = ui->txtTomo->text();
  QString paginas = ui->txtPaginas->text();
  QModelIndex idx;

  fuente datosobra;

  idx = m_obras_completer->currentIndex();
  if (idx.isValid()) {
    int row = idx.row();
    obra = m_obras_completer->completionModel()->index(row, 0).data().toInt();
  }
  else {
    int ret = QMessageBox::warning(this, "Obra no reconocida",
                                   "Introduzca por favor una obra conocida.");
    return;
  }

  datosobra.titulo = obra;
  datosobra.tomo = tomo;
  datosobra.paginas = paginas;

  emit(signalFuente(datosobra));

  close();
}
