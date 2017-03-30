#include "resolucion.h"

Resolucion::Resolucion()
{ }

void Resolucion::setId(int i) { id = i; }
void Resolucion::setTexto(QString t) { texto = t; }
void Resolucion::setTextoTraducido(QString t) { texto_traducido = t; }
void Resolucion::setTextoResumido(QString t) { texto_resumido = t; }
void Resolucion::setCapitulo(int c) { capitulo = c; }
void Resolucion::setEpigrafe(QString e) { epigrafe = e; }
void Resolucion::setProvincia(int p) { provincia = p; }
void Resolucion::setEntendido(bool e) { entendido = e; }
void Resolucion::setVolverMirar(bool v) { volveramirar = v; }
void Resolucion::setTraducido(bool t) { traducido = t; }
void Resolucion::setInteres(int i) { interes = i; }
void Resolucion::setResolucionAnterior(int r) { resolucion_anterior = r; }
