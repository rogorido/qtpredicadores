#include "dlgcapitulos.h"
#include "ui_dlgcapitulos.h"

#include <QSqlTableModel>

DlgCapitulos::DlgCapitulos(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DlgCapitulos)
{
    ui->setupUi(this);

    m_capitulos = new QSqlTableModel(this);
    m_capitulos->setTable("public.capitulos");
    m_capitulos->select();

    ui->twCapitulos->setModel(m_capitulos);
}

DlgCapitulos::~DlgCapitulos()
{
    delete ui;
}
