#include "jsongestor.h"

#include <QTreeWidget>
#include <QTreeWidgetItem>

JsonGestor::JsonGestor(QTreeWidget *tree)
{
    tree_original = new QTreeWidget(tree);
    tree_original->setColumnCount(2);

    QTreeWidgetItem *itemnivelcero = new QTreeWidgetItem(tree_original);
    /*
     * realmente esto es una cutrada.. habría que ponerlo solo si
     * hay algo, pero bueno, ya lo corregiré...
     */
    itemnivelcero->setText(0, "Datos 0");

    /*
     * convertimos el QtreeWidgetItem que acabamos de meter
     * en el "activo" al que tienen que ir los children
     */
    item_activo = new QTreeWidgetItem();
    item_activo = itemnivelcero;

}

void JsonGestor::anadirValor(const QString &key, const QJsonValue &value){

    m_json_activo.insert(key, value);
    anadirChildItem(key, value.toString());
}

void JsonGestor::anadirValor(const QString &key, const QString &value, int id){

    m_json_activo.insert(key, QJsonValue(id));
    anadirChildItem(key, value);
}

void JsonGestor::anadirChildItem(const QString &key, const QString &value){

    QTreeWidgetItem *itemniveluno = new QTreeWidgetItem();
    itemniveluno->setText(0, key);
    itemniveluno->setText(1, value);
    item_activo->addChild(itemniveluno);
}

void JsonGestor::nuevoBloqueJson(){
    /*
     * esto se llama cuando queremos meter otro bloque
     * de datos en json
     */

    /*
     * en ppo lo primero que hacemos es comprobar si
     * jsondetalles está vacío pues si no lo está quiere decir
     * que ya hemos estado metiendo cosas SIN pasarlas a
     * jsondetalles_lista...
     * pero tiene que haber una manera mejor!
     */

    if (!m_json_activo.isEmpty())
        m_json_general.append(m_json_activo);

    // borramos el contenido de este objeto
    m_json_activo = QJsonObject();

    QTreeWidgetItem *itemnivelcero = new QTreeWidgetItem(tree_original);
    int nivel = m_json_general.count();
    itemnivelcero->setText(0, QString("Datos %1").arg(nivel));

    item_activo = itemnivelcero;
}
