#include "capitulo.h"

Capitulo::Capitulo()
{ }

void Capitulo::setId(const int i) { id = i; }
void Capitulo::setNombre(const QString n) { nombre = n; }
void Capitulo::setLugar(const int l) { lugar = l; }
void Capitulo::setTipo(const QString t) { tipo = t; }
void Capitulo::setAsistentes(const QString a) { asistentes = a; }
void Capitulo::setVolumen(const QString v) { volumen = v; }
void Capitulo::setPaginas(const QString p) { paginas = p; }
void Capitulo::setNotas(const QString n) { notas = n; }
void Capitulo::setMaestroGeneral(const int m) { maestrogeneral = m; }
void Capitulo::setDefinitorio(const bool d) { definitorio = d; }
void Capitulo::setFechaInicio(const QDate fi) { fecha_inicio = fi; }
void Capitulo::setFechaFin(const QDate ff) { fecha_fin = ff; }
