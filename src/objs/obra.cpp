#include "obra.h"

Obra::Obra() { }

void Obra::setId(const int i) {id = i;}
void Obra::setTitulo(const QString t) {titulo = t;}
void Obra::setIdioma(const QString i) {idioma = i;}
void Obra::setAutor(const int a) {autor = a;}
void Obra::setTipo(const QString t) {tipo = t;}
void Obra::setFormato(const QString f) {formato = f;}
void Obra::setTomos(const int t) {tomos = t;}
void Obra::setNumeroPags(const QString np) {numeropags = np;}
void Obra::setImpreso(const bool i) {impreso = i;}
void Obra::setTalVezImpreso(const bool i) {talvez_impreso = i;}
void Obra::setManuscrito(const bool m) {manuscrito = m;}
void Obra::setLugarOriginal(const QString l) {lugaroriginal = l;}
void Obra::setLugar(const int l) {lugar = l;}
void Obra::setFecha(const int f) {fecha = f;}
void Obra::setEditor(const QString e) {editor = e;}
void Obra::setReferencias(const bool r) {refs = r;}
void Obra::setTituloReducido(const bool t) {tituloreducido = t;}
void Obra::setContenido(const bool c) {contenido = c;}
void Obra::setInteresante(const int i) {interesante = i;}
void Obra::setDudoso(const bool d) {dudoso = d;}
void Obra::setExpurgable(const bool e) {expurgable = e;}
void Obra::setFiabilidad(const int f) { fiabilidad = f; }
void Obra::setVolverMirar(const bool v) { volveramirar = v; }
void Obra::setInvestigar(const bool i) { investigar = i; }
void Obra::setTraduccion(const QString t) { traduccion = t; }
void Obra::setPageQuetif(const QString p) { page_quetif = p; }
void Obra::setNotas(const QString n) {notas = n;}
