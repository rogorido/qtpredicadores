#ifndef DLGANNEENUEVO_H
#define DLGANNEENUEVO_H

#include <QWidget>

#include "src/objs/persona.h"
#include "src/objs/tema.h"

class QCompleter;
class QSqlQueryModel;

class MyQmdiArea;

namespace Ui {
class dlgAnneeNuevo;
}

class dlgAnneeNuevo : public QWidget {
  Q_OBJECT

 public:
  explicit dlgAnneeNuevo(QWidget *parent = 0);
  ~dlgAnneeNuevo();

 protected:
  bool eventFilter(QObject *obj, QEvent *e);

 private slots:

  void cerrar();
  void aceptarAnnee();

  void anadirPersona();
  void anadirPersonaAdicional();
  void quitarPersonaAdicional();
  void anadirMeditacion();
  void quitarMeditacion();
  void anadirConceptoMeditacion();
  void quitarConceptoMeditacion();
  void anadirCategoriasMeditacion();
  void anadirCategoriasGeneral();
  void quitarCategoriasGeneral();

  void recibirPersonaPrincipal(const Persona persona);
  void recibirPersonaAdicional(const Persona persona);
  void recibirTemaMeditacion(const Tema tema);
  void recibirTemaGeneral(const Tema tema);

 private:
  Ui::dlgAnneeNuevo *ui;
  MyQmdiArea *mdiarea;

  QSqlQueryModel *autores_model;
  QCompleter *autores_completer;
  QSqlQueryModel *temasprincipales_model;
  QCompleter *temasprincipales_completer;
  QSqlQueryModel *conceptos_model;
  QCompleter *conceptos_completer;

  /*
   * aquí vienen las variables donde vamos a guardar los datos
   * pq por ahroa no hago una clase extra para esto
   */
  int persona_id = 0;

  struct m_meditacion {
    int numeracion;
    QString pensamiento;
    QHash<int, QString> categorias;
    QStringList conceptos;
  };

  QList<m_meditacion> meditaciones;

  /*
   * aquí metemos los conceptos que luego pasamos
   * a m_meditacion
   */
  QStringList m_conceptos;

  /*
   * aquí metemos las categorías que vamos escogiendo
   * con dlgseleccionar y que luego asociaremos en el struct
   * m_meditacion...
   */

  QHash<int, QString> categorias_seleccionadas_meditaciones;

  /*
   * aquí metemos las categorías generales que vamos escogiendo
   * con dlgseleccionar y luego va a la table themes_refs
   */

  QHash<int, QString> categorias_seleccionadas_general;

  /*
   *  aquí metemos las personas, realmetne con los ids sería
   * suficiente, pero para que lo muestre en la tabla hago esto...
   */
  struct otrapersona {
    int id;
    QString nombre;
  };

  QList<otrapersona> personas_adicionales;

  void cargarModelos();
  void borrarCampos();

  // esto sirve para meter datos si ha funcionado con la tabla principal
  void meterMeditaciones(const int id);
  /*
   * esto son las categorías... hacen faltan dos int pq uno es para
   * la meditation_id y el otro es para coger dentro del QList las categorías
   * que están metidas...
   */
  void meterMeditacionesReferencias(const int meditation_id,
                                    const int lista_meditaciones_id);
  void meterPersonasAdicionales(const int id);
  void meterCategoriasGenerales(const int id);
};

#endif  // DLGANNEENUEVO_H
