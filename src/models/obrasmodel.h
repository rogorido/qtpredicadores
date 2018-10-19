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
     * Si se trata de una nueva obra no pasamos el parámetro obra_id
     * y funciona.
     */
    bool AnadirObra(const Obra *obra, int obra_id = 0);

    Obra *devolverObra(const int id);
    QVector<int> materiasObra(const int obra_id);
    // esto devuelve los detalles de una obra
    QJsonModel *devolverDetalles(const int id);

protected:
    ObrasModel();
    ObrasModel(const ObrasModel &);
    ObrasModel &operator =(const ObrasModel &);

private:
    static ObrasModel *pInstance;
    static void DestroyMe();

};

#endif // OBRASMODEL_H
