#include "jsongestor.h"

#include <QTreeWidget>
#include <QTreeWidgetItem>
#include <QMessageBox>
#include <QModelIndex>

#include <QJsonDocument>
#include <QDebug>

JsonGestor::JsonGestor(QObject *parent) : QObject(parent)
{
    modificando = false;
    bloqueadaEntrada = false;

}

void JsonGestor::setTreeWidget(QTreeWidget *tree){
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
        msgBox.setText("Entrada bloqueda.");
        msgBox.setInformativeText("Hay que añadir un nuevo bloque.");
        msgBox.setStandardButtons(QMessageBox::Ok);
        msgBox.setDefaultButton(QMessageBox::Ok);
        int ret = msgBox.exec();
        return;
    }

    m_json_activo.insert(key, value);

    /*
     * hay que hacer este pequeño lío para sacar el puto Qstringlist
     * del array. No sé por qué no hay un sistema más fácil..
     */
    QVariant valores = value.toVariant();
    if (value.isArray()){
        QStringList valores_lista = valores.toStringList();
        QString valores_final = valores_lista.join(", ");
        anadirChildItem(key, valores_final);
    }
    else
        anadirChildItem(key, valores.toString());
}



void JsonGestor::anadirValor(const QString &key, const QString &value, int id){

    if (bloqueadaEntrada) {
        QMessageBox msgBox;
        msgBox.setText("Entrada bloqueda.");
        msgBox.setInformativeText("Hay que añadir un nuevo bloque.");
        msgBox.setStandardButtons(QMessageBox::Ok);
        msgBox.setDefaultButton(QMessageBox::Ok);
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

    // ver explicación en el header!
    if (!m_json_activo.isEmpty())
        m_json_general.append(m_json_activo);

}

int JsonGestor::getSize(){
    return m_json_general.size();
}

bool JsonGestor::isEmpty()
{
    if (m_json_activo.isEmpty())
        return true;
    else
        return false;

}

QString JsonGestor::getJsonString(int i){

    /*
     * construimos un QJsonDocument con ese QJsonobject de la lista, pq eso permite luego pasarlo
     *    a una cadena de texto con toJson()
     * ¿Por qué no pongo aquí un ref a lo de actualizarPrevioIntroducir?
     */
    QJsonDocument jsondoc(m_json_general.at(i));
    QString jsonfinal;

    jsonfinal = jsondoc.toJson(QJsonDocument::Compact);

    return jsonfinal;
}

void JsonGestor::eliminarElemento(){

    QTreeWidgetItem *item;
    QTreeWidgetItem *padre;
    int pos;
    QVariant key;

    item = tree_original->currentItem();
    if (!item){
        return;
    }
    else {
        padre = item->parent();
    }

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
     * pq tenemos que coger un índice para sacar la row, pues de la otra
     * forma no lo consigo. Luego usamos eso como índice para acceder al
     * QJsonObject que está en esa posición en el QList m_json_gerenal
     * para borrarlo... y si nos hemos quedado sin elementos añadimos
     * un itemroot.
     */

    if (!padre){
        QModelIndex idx = tree_original->currentIndex();
        pos = idx.row();
        m_json_general.removeAt(pos);
        delete item;

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

    QTreeWidgetItem *item;
    QTreeWidgetItem *padre;

    // hay que mirar si realmente hay un item escogido...
    item = tree_original->currentItem();
    if (!item){
        return;}
    else{
        padre = item->parent();
    }

    // guardamos por si hay algo sin guardar...
    // aunque esto hay que pensarlo.
    if (!m_json_activo.isEmpty())
        m_json_general.append(m_json_activo);

    if (!padre){
        // cogemos la posición y convertimos el item en activo
        // si ya es dle nivel 1
        QModelIndex idx = tree_original->currentIndex();
        posicion = idx.row();
        item_activo = item;
        }
    else {
        posicion = tree_original->indexOfTopLevelItem(padre);
        item_activo = padre;
    }

    m_json_activo = m_json_general.at(posicion);
    modificando = true;
}
