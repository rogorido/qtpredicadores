#ifndef PERSONASMODEL_H
#define PERSONASMODEL_H

#include <QSqlTableModel>

class Persona;
class QJsonModel;

class PersonasModel : public QSqlTableModel
{
    Q_OBJECT

public:
    static PersonasModel *InstanceModel();

    /*
     * Si se trata de una nueva obra no pasamos el parámetro persona_id
     * y funciona.
     */
    bool AnadirPersona(const Persona *persona, int persona_id = 0);

    Persona *devolverPersona(int id);
    // esto devuelve los detalles de una persona
    QJsonModel *devolverDetalles(int id);

signals:

    void actualizado();

protected:
    PersonasModel();
    PersonasModel(const PersonasModel &);
    PersonasModel &operator =(const PersonasModel &);

private:
    static PersonasModel *pInstance;
    static void DestroyMe();
};

#endif // PERSONASMODEL_H
