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

    bool AnadirObra(const Obra *obra);
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
