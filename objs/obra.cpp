#include "obra.h"

Obra::Obra() { }

void Obra::setTitulo(QString t) {titulo = t;}
void Obra::setIdioma(QString i) {idioma = i;}
void Obra::setAutor(int a) {autor = a;}
void Obra::setTipo(QString t) {tipo = t;}
void Obra::setFormato(QString f) {formato = f;}
void Obra::setTomos(int t) {tomos = t;}
void Obra::setNumeroPags(QString np) {numeropags = np;}
void Obra::setImpreso(bool i) {impreso = i;}
void Obra::setTalVezImpreso(bool i) {talvez_impreso = i;}
void Obra::setManuscrito(bool m) {manuscrito = m;}
void Obra::setLugarOriginal(QString l) {lugaroriginal = l;}
void Obra::setLugar(int l) {lugar = l;}
void Obra::setFecha(int f) {fecha = f;}
void Obra::setEditor(QString e) {editor = e;}
void Obra::setReferencias(bool r) {refs = r;}
void Obra::setTituloReducido(bool t) {tituloreducido = t;}
void Obra::setContenido(bool c) {contenido = c;}
void Obra::setInteresante(int i) {interesante = i;}
void Obra::setDudoso(bool d) {dudoso = d;}
void Obra::setExpurgable(bool e) {expurgable = e;}
void Obra::setFiabilidad(int f) { fiabilidad = f; }
void Obra::setVolverMirar(bool v) { volveramirar = v; }
void Obra::setTraduccion(QString t) { traduccion = t; }
void Obra::setPageQuetif(QString p) { page_quetif = p; }
void Obra::setNotas(QString n) {notas = n;}
