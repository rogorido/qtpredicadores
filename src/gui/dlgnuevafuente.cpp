#include "dlgnuevafuente.h"

#include <QMessageBox>
#include <QSqlQuery>

#include "ui_dlgnuevafuente.h"

dlgNuevaFuente::dlgNuevaFuente(QWidget *parent)
    : QDialog(parent), ui(new Ui::dlgNuevaFuente)
{
  ui->setupUi(this);
}

dlgNuevaFuente::~dlgNuevaFuente() { delete ui; }

void dlgNuevaFuente::accept()
{
  QSqlQuery query;
  QString titulo;
  QString autor;

  titulo = ui->txtTitulo->text();
  autor = ui->txtAutor->text();

  query.prepare("INSERT INTO sources(title, author) VALUES(:titulo, :autor)");
  query.bindValue(":titulo", titulo);
  query.bindValue(":autor", autor);

  if (query.exec()) {
    close();
  }
  else {
    int ret = QMessageBox::warning(
        this, "Error",
        "Ha habido un error al ejecutar la consulta de inserción.");
    Q_UNUSED(ret)
    return;
  }
}
