#include "dlgestadisticas.h"
#include "ui_dlgestadisticas.h"

#include <QSqlQueryModel>

const QString est_temas_por_resolucion="SELECT * FROM analysis.categories_per_resolution";
const QString est_resoluciones_por_capitulo="SELECT * FROM analysis.resolutions_per_chapter";
const QString est_casas_por_provincias="SELECT * FROM analysis.casas_por_provincias";

dlgEstadisticas::dlgEstadisticas(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::dlgEstadisticas)
{
    ui->setupUi(this);

    estadisticas = new QSqlQueryModel(this);

    ui->twEstadisticas->horizontalHeader()->setStretchLastSection(true);

    connect(ui->cbQuery, SIGNAL(currentIndexChanged(int)), this, SLOT(cambiarModelo(int)));

    ui->cbQuery->addItem("Tema por resolución");
    ui->cbQuery->addItem("Resoluciones por capítulo");
    ui->cbQuery->addItem("Casas por provincias");

}

dlgEstadisticas::~dlgEstadisticas()
{
    delete ui;
}

void dlgEstadisticas::cambiarModelo(int row)
{
    switch (row) {
    case 0:
        estadisticas->setQuery(est_temas_por_resolucion);
        break;
    case 1:
        estadisticas->setQuery(est_resoluciones_por_capitulo);
        break;
    case 2:
        estadisticas->setQuery(est_casas_por_provincias);
    default:
        break;
    }

    ui->twEstadisticas->setModel(estadisticas);
    ui->twEstadisticas->resizeColumnsToContents();
    ui->twEstadisticas->resizeRowsToContents();

}
