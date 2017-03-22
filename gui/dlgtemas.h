#ifndef DLGTEMAS_H
#define DLGTEMAS_H

#include <QDialog>

class TemasModel;

namespace Ui {
class dlgTemas;
}

class dlgTemas : public QDialog
{
    Q_OBJECT

public:
    explicit dlgTemas(QWidget *parent = 0);
    ~dlgTemas();

private slots:

    void on_btNuevoTema_clicked();
    void on_btAnadirTema_clicked();
    void on_btQuitarTema_clicked();

    void aceptarTemas();

private:
    Ui::dlgTemas *ui;

    TemasModel *m_temas;

    struct elementopareado{
      int id;
      QString elemento;
    };

    QList<elementopareado> temas_lista;

    void rellenarCombos();

signals:
    /*
     * curioso: esto tiene que ir después del bloque private:
     * pq si no da un error por el elementopareado
     */
    void temasSeleccionadosSignal(QList<elementopareado> temas);

};

#endif // DLGTEMAS_H
