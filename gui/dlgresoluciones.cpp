#include "dlgresoluciones.h"
#include "ui_dlgresoluciones.h"

#include <QSqlQueryModel>

DlgResoluciones::DlgResoluciones(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DlgResoluciones)
{
    ui->setupUi(this);

    resoluciones_model = new QSqlQueryModel(this);
    resoluciones_model->setQuery("SELECT resolution_id, substring(resolution_text, 0, 100), chapters.general_name, "
                                 "small_title FROM resolutions JOIN chapters ON chapter=chapter_id;");
    ui->twResoluciones->setModel(resoluciones_model);

    connect(ui->btCerrar, SIGNAL(clicked()), this, SLOT(close()));
}

DlgResoluciones::~DlgResoluciones()
{
    delete ui;
}
