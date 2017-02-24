#include "jsongestor.h"

#include <QTreeWidget>
#include <QTreeWidgetItem>

JsonGestor::JsonGestor(QTreeWidget *tree)
{
    tree_original = new QTreeWidget(tree);

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

void JsonGestor::setTreeView(QTreeWidget *tree){
    tree_original = new QTreeWidget(tree);

    //tree_original = tree;
}

void JsonGestor::anadirValor(const QString &key, const QJsonValue &value){

    m_json_activo.insert(key, value);

    QTreeWidgetItem *itemniveluno = new QTreeWidgetItem();
    itemniveluno->setText(0, key);
    itemniveluno->setText(1, value.toString());
    item_activo->addChild(itemniveluno);
}
