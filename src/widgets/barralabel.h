#ifndef BARRALABEL_H
#define BARRALABEL_H

#include <QLabel>

class BarraLabel : public QLabel {
  Q_OBJECT
 public:
  explicit BarraLabel(QWidget *parent = nullptr);
  ~BarraLabel();

  void setNumeroObisposTotal(const int n) { n_obispos = n; }
  void setNumeroObrasTotal(const int n) { n_obras = n; }
  void setNumeroPersonasTotal(const int n) { n_personas = n; }
  void setNumeroCasasTotal(const int n) { n_casas = n; }
  void setNumeroCiudadesTotal(const int n) { n_ciudades = n; }

  void inicializar();

 signals:

 public slots:

  void setNumeroObisposFiltrados(const int n);
  void setNumeroObrasFiltrados(const int n);
  void setNumeroPersonasFiltrados(const int n);
  void setNumeroCasasFiltrados(const int n);
  void setNumeroCiudadesFiltrados(const int n);

 private:
  // número de... n=total; f=filtrado
  int n_obispos, n_obras, n_personas, n_ciudades, n_casas, f_obispos, f_obras,
      f_personas, f_ciudades, f_casas;

  QString textomostrado;

  void crearTexto();
};

#endif  // BARRALABEL_H
