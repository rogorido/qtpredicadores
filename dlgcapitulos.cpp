#include "dlgcapitulos.h"
#include "ui_dlgcapitulos.h"

#include <QSqlTableModel>
#include <QDebug>

DlgCapitulos::DlgCapitulos(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DlgCapitulos)
{
    ui->setupUi(this);

    m_capitulos = new QSqlTableModel(this);
    m_capitulos->setTable("public.capitulos");
    m_capitulos->select();

    ui->twCapitulos->setModel(m_capitulos);

    // esto es para hacer el loop de un array de ints...
    // la finalidad: ocultar algunas columnas
    std::vector<int> v = {0, 2, 6, 7, 8, 9, 10, 11, 12};
    for(int n : v) {
        ui->twCapitulos->hideColumn(n);
        }
}

DlgCapitulos::~DlgCapitulos()
{
    delete ui;
}
