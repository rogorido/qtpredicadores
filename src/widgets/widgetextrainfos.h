#ifndef WIDGETEXTRAINFOS_H
#define WIDGETEXTRAINFOS_H

#include <QWidget>

#include "src/objs/variados.h"

class QSqlQueryModel;
class QCompleter;

namespace Ui {
class WidgetExtraInfos;
}

class WidgetExtraInfos : public QWidget
{
    Q_OBJECT

public:
    explicit WidgetExtraInfos(QWidget *parent = 0);
    ~WidgetExtraInfos();

    ExtraInfos getExtraInfos();
    void clear();
    // esto es para crear completers en caso de que sea requerido
    void recibirConsultasCompleter(QString sql_claves, QString sql_valores);

private slots:

    void anadirPar();
    void eliminarPar();

private:
    Ui::WidgetExtraInfos *ui;

    QSqlQueryModel *librekeys_model;
    QSqlQueryModel *librevalues_model;
    QCompleter *librekeys_completer;
    QCompleter *librevalues_completer;

    ExtraInfos extras;
};

#endif // WIDGETEXTRAINFOS_H
