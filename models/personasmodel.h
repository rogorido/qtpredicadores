#ifndef PERSONASMODEL_H
#define PERSONASMODEL_H

#include <QSqlTableModel>

class Persona;

class PersonasModel : public QSqlTableModel
{
    Q_OBJECT

public:
    static PersonasModel *InstanceModel();

    bool AnadirPersona(const Persona *persona);
    Persona *devolverPersona(int id);

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
