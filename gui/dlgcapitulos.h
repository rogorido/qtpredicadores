#ifndef DLGCAPITULOS_H
#define DLGCAPITULOS_H

#include <QDialog>

class CapitulosModel;
class QModelIndex;
class dlgMasivo;

namespace Ui {
class dlgCapitulos;
}

class dlgCapitulos : public QDialog
{
    Q_OBJECT

public:
    explicit dlgCapitulos(QWidget *parent = 0);
    ~dlgCapitulos();

private slots:
    void escogidoCapitulo(const QModelIndex &idx);
    void introducirAsistentes();

private:
    Ui::dlgCapitulos *ui;

    CapitulosModel *m_capitulos;

    dlgMasivo *dlgmasivo;



};

#endif // DLGCAPITULOS_H
