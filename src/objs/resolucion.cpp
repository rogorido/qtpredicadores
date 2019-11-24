#include "resolucion.h"

Resolucion::Resolucion() {}

void Resolucion::setId(const int i) { id = i; }
void Resolucion::setTexto(const QString t) { texto = t; }
void Resolucion::setTextoTraducido(const QString t) { texto_traducido = t; }
void Resolucion::setTextoResumido(const QString t) { texto_resumido = t; }
void Resolucion::setCapitulo(const int c) { capitulo = c; }
void Resolucion::setEpigrafe(const QString e) { epigrafe = e; }
void Resolucion::setProvincia(const int p) { provincia = p; }
void Resolucion::setEntendido(const bool e) { entendido = e; }
void Resolucion::setVolverMirar(const bool v) { volveramirar = v; }
void Resolucion::setTraducido(const bool t) { traducido = t; }
void Resolucion::setRazonada(const bool r) { razonada = r; }
void Resolucion::setInteres(const int i) { interes = i; }
void Resolucion::setResolucionAnterior(const int r) { resolucion_anterior = r; }
void Resolucion::setVerbos(const QStringList v) { verbos = v; }
void Resolucion::setExpresiones(const QStringList e) { expresiones = e; }
void Resolucion::setPages(const QString p) { pages = p; }
void Resolucion::setNotas(const QString n) { notas = n; }
