#include "dlgobispos.h"
#include "ui_dlgobispos.h"

#include <QSqlQueryModel>

const QString sqlgeneral = "SELECT * from bishops.bishops";

dlgObispos::dlgObispos(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::dlgObispos)
{
    ui->setupUi(this);

    obispos_model = new QSqlQueryModel(this);
    obispos_model->setQuery(sqlgeneral);

    ui->twObispos->setModel(obispos_model);

}

dlgObispos::~dlgObispos()
{
    delete ui;
}
