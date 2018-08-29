#ifndef OBRASMODEL_H
#define OBRASMODEL_H

#include <QSqlTableModel>

class Obra;
class QJsonModel;

class ObrasModel : public QSqlTableModel
{
    Q_OBJECT

public:
    static ObrasModel *InstanceModel();

    /*
     * Dos métodos: uno para añadir nuevo y otro para modificar...
     * NOTE: Pero esto tiene que haber otra forma pq esto me obliga a
     * repetir el código?
     */
    bool AnadirObra(const Obra *obra, int obra_id = 0);

    Obra *devolverObra(int id);
    void actualizarObra(int id);
    QVector<int> materiasObra(int obra_id);
    // esto devuelve los detalles de una obra
    QJsonModel *devolverDetalles(int id);

protected:
    ObrasModel();
    ObrasModel(const ObrasModel &);
    ObrasModel &operator =(const ObrasModel &);

private:
    static ObrasModel *pInstance;
    static void DestroyMe();

};

#endif // OBRASMODEL_H
