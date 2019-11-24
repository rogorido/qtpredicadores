#ifndef DLGNUEVAMISIONFILIPINAS_H
#define DLGNUEVAMISIONFILIPINAS_H

#include <src/objs/lugar.h>

#include <QDialog>

class MisionesModel;
class QJsonModel;
class MyQmdiArea;

namespace Ui {
class dlgNuevaMisionFilipinas;
}

class dlgNuevaMisionFilipinas : public QDialog {
  Q_OBJECT

 public:
  enum class TipoLugar { SALIDAMISION, SALIDAETAPA, LLEGADAETAPA };

  explicit dlgNuevaMisionFilipinas(QWidget *parent = 0);
  ~dlgNuevaMisionFilipinas();

 private slots:

  void aceptarMision();

  /*
   * aquí está el código general para abrir el form SeleccionarGeneral
   */
  void anadirLugarGeneral();
  /*
   * estos tres llaman todos a anadirLugarGeneral
   * adaptando la variable tipolugar_pulsado
   */
  void anadirSalidaMision();
  void anadirSalidaEtapa();
  void anadirLlegadaEtapa();

  void anadirEtapa();

  /*
   * con esto lo recibe del fomrulario, pero luego hay que
   * pasarlo con el TipoLugar, porque así uso este slot para
   * los tres campos que hay de lugar en el form.
   */
  void recibirLugarSlot(Lugar lugar);

  void cerrar();

 private:
  Ui::dlgNuevaMisionFilipinas *ui;
  MyQmdiArea *mdiarea;

  MisionesModel *m_misiones;

  QJsonModel *json_etapas;

  int lugarsalida_mision_id;
  // estos son para la etapa que luego habrá que borrar
  int lugarsalida_etapa_id = 0;
  int lugarllegada_etapa_id = 0;

  /*
   * con esto sabemos qué widget realmente se ha pulsado
   */
  TipoLugar tipolugar_pulsado;

  void borrarcamposMision();
  void borrarCamposEtapa();
  void cargarModelEtapas();
};

#endif  // DLGNUEVAMISIONFILIPINAS_H
