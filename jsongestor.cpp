#include "jsongestor.h"

#include <QTreeWidget>
#include <QTreeWidgetItem>
#include <QMessageBox>
#include <QModelIndex>

#include <QJsonDocument>
#include <QDebug>

JsonGestor::JsonGestor(QTreeWidget *tree, QObject *parent) : QObject(parent)
{
    modificando = false;
    bloqueadaEntrada = false;

    tree_original = new QTreeWidget(tree);
    tree_original->setColumnCount(2);

    crearItemRootGeneral();
}

void JsonGestor::crearItemRootGeneral(){
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

    if (bloqueadaEntrada) {
        QMessageBox msgBox;
        msgBox.setText("The document has been modified.");
        msgBox.setInformativeText("Do you want to save your changes?");
        msgBox.setStandardButtons(QMessageBox::Save | QMessageBox::Discard | QMessageBox::Cancel);
        msgBox.setDefaultButton(QMessageBox::Save);
        int ret = msgBox.exec();
        return;
    }

    m_json_activo.insert(key, value);
    anadirChildItem(key, value.toString());
}

void JsonGestor::anadirValor(const QString &key, const QString &value, int id){

    if (bloqueadaEntrada) {
        QMessageBox msgBox;
        msgBox.setText("The document has been modified.");
        msgBox.setInformativeText("Do you want to save your changes?");
        msgBox.setStandardButtons(QMessageBox::Save | QMessageBox::Discard | QMessageBox::Cancel);
        msgBox.setDefaultButton(QMessageBox::Save);
        int ret = msgBox.exec();
        return;
    }

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

    bloqueadaEntrada = false;

    anadirItemNivelCero();

}

void JsonGestor::anadirItemNivelCero(){
    QTreeWidgetItem *itemnivelcero = new QTreeWidgetItem(tree_original);
    int nivel = m_json_general.count();
    itemnivelcero->setText(0, QString("Datos %1").arg(nivel));

    item_activo = itemnivelcero;
}

void JsonGestor::actualizarPrevioIntroducir(){

    if (!m_json_activo.isEmpty())
        m_json_general.append(m_json_activo);

}

int JsonGestor::getSize(){
    return m_json_general.size();
}

QString JsonGestor::getJsonString(int i){

    /*
     * el asunto es el siguiente:
     * 1. construimos un QJsonDocument con ese QJsonobject de la lista, pq eso permite luego pasarlo
     *    a una cadena de texto con toJson()
     * 3. lo metemos en una puta variable, pq si no no funciona....
     */
    QJsonDocument jsondoc(m_json_general.at(i));
    QString jsonfinal;

    jsonfinal = jsondoc.toJson(QJsonDocument::Compact);

    return jsonfinal;
}

void JsonGestor::eliminarElemento(){

    QTreeWidgetItem *item = tree_original->currentItem();
    QTreeWidgetItem *padre = item->parent();
    int pos;
    QVariant key;

    /*
     * metemos lo que haya en m_json_activo y bloqueamos
     * después la entrada de datos
     */
    if (!m_json_activo.isEmpty()){
        m_json_general.append(m_json_activo);
        m_json_activo = QJsonObject();
    }

    // bloqueamos la entrada...
    bloqueadaEntrada = true;

    /*
     * lo primero que hacemos es mirar si es un elemento padre
     * pq entonces tenemos que actuar de otra forma. El asunto es un lío
     * pq tenemos que mirar:
     * 1. que no haya td nada en m_json_general
     * 2. que sí lo haya pero que el nuevo m_json_activo no esté metido
     * 3. otros casos
     */
    qDebug() << "tamano de la qlist: " << m_json_general.size();
    if (!padre){
        QModelIndex idx = tree_original->currentIndex();
        pos = idx.row();

            //pos = tree_original->indexOfTopLevelItem(padre);
            qDebug() << "el indice es: " << pos;
            m_json_general.removeAt(pos);
            delete item;

            qDebug() << "tamano de la qlist: " << m_json_general.size();
            if (m_json_general.size() == 0){
                        crearItemRootGeneral();
                    }

            return;
        }


    /*
     * cogemos la posición en la que está pq es la que se corresponde
     * con la QList m_json_general
     */
    pos = tree_original->indexOfTopLevelItem(padre);

    key = item->data(0, Qt::DisplayRole);

    QJsonObject jsontemporal = m_json_general.at(pos);
    jsontemporal.remove(key.toString());
    m_json_general.replace(pos, jsontemporal);

    // borramos el item, curiosamente se hace así...
    if (item)
        delete item;
}

void JsonGestor::modificandoDatos(bool checked){


    if (modificando == true && checked == false) {
        /*
         * en este caso entiendo que vengo de modificar algo
         * por lo que hay q introducir los datos...
         * esto es un puto lío del carajo...
         */

        m_json_general.replace(posicion, m_json_activo);
        m_json_activo = QJsonObject();

        // y añadimos uno... aunque no sé si tiene mucho sentido...
        anadirItemNivelCero();
        modificando = false;
        return;
    }

    QTreeWidgetItem *item = tree_original->currentItem();
    QTreeWidgetItem *padre = item->parent();

    // guardamos por si hay algo sin guardar...
    // aunque esto hay que pensarlo.
    if (!m_json_activo.isEmpty())
        m_json_general.append(m_json_activo);

    if (!padre){
        // cogemos la posición y convertimos el item en activo
        // si ya es dle nivel 1
        posicion = tree_original->indexOfTopLevelItem(item);
        item_activo = item;
        }
    else {
        posicion = tree_original->indexOfTopLevelItem(padre);
        item_activo = padre;
    }

    m_json_activo = m_json_general.at(posicion);
    modificando = true;
}
