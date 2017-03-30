#include "capitulo.h"

Capitulo::Capitulo()
{ }

void Capitulo::setId(int i) { id = i; }
void Capitulo::setNombre(QString n) { nombre = n; }
void Capitulo::setLugar(int l) { lugar = l; }
void Capitulo::setTipo(QString t) { tipo = t; }
void Capitulo::setAsistentes(QString a) { asistentes = a; }
void Capitulo::setVolumen(QString v) { volumen = v; }
void Capitulo::setPaginas(QString p) { paginas = p; }
void Capitulo::setNotas(QString n) { notas = n; }
void Capitulo::setMaestroGeneral(int m) { maestrogeneral = m; }
void Capitulo::setFechaInicio(QDate fi) { fecha_inicio = fi; }
void Capitulo::setFechaFin(QDate ff) { fecha_fin = ff; }
