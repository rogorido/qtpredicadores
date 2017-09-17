#ifndef SQLFILTROGESTOR_H
#define SQLFILTROGESTOR_H

#include <QObject>
#include <QMap>

class SqlFiltroGestor : public QObject
{
    Q_OBJECT
public:
    explicit SqlFiltroGestor(QString sql, QObject *parent = nullptr);

    void setSqlGeneral(QString sql);
    void setSqlOrder(QString sql);
    void anadirFiltro(QString nombre, QString sql);
    void quitarFiltro(QString nombre);
    void borrarFiltros();

signals:

    void actualizadoSqlFiltroGestor(QString s);

private:

    /*
     * guardamos los filtros con su nombre
     * y el código SQL
     */
    QMap<QString, QString> filtros;

    /*
     * Aquí está el SQL general que llega
     * del formulario.
     */
    QString sqlgeneral;

    /*
     * este es el SQL que creamos
     */
    QString sqlcreado;

    /*
     * Aquí está el SQL que sirve para ordenar
     */
    QString sqlorder;

    void generarSql();

};

#endif // SQLFILTROGESTOR_H
