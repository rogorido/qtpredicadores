#-------------------------------------------------
#
# Project created by QtCreator 2017-02-13T12:51:38
#
#-------------------------------------------------

QT       += core gui sql

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = qtPredicadores
TEMPLATE = app
#CONFIG += c++11

# The following define makes your compiler emit warnings if you use
# any feature of Qt which as been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

#QMAKE_CXXFLAGS_WARN_OFF += -Wunused-variable

SOURCES += main.cpp\
    gui/mainwindow.cpp \
    gui/dlgnuevocapitulo.cpp \
    gui/dlgnuevaresolucion.cpp \
    models/temasmodel.cpp \
    models/lugaresmodel.cpp \
    models/personasmodel.cpp \
    models/casasmodel.cpp \
    gui/dlgnuevapersona.cpp \
    objs/persona.cpp \
    objs/casa.cpp \
    objs/obra.cpp \
    gui/dlgnuevacasa.cpp \
    gui/dlgcapitulos.cpp \
    models/obrasmodel.cpp \
    gui/dlgnuevaobra.cpp \
    objs/proxynombres.cpp \
    objs/lugar.cpp \
    gui/dlgdetalles.cpp \
    gui/dlgnuevaprovincia.cpp \
    objs/provincia.cpp \
    models/provinciasmodel.cpp \
    gui/dlgseleccionargeneral.cpp \
    gui/dlgnuevolugar.cpp \
    widgets/myqlineedit.cpp \
    gui/dlgtemas.cpp \
    models/capitulosmodel.cpp \
    objs/capitulo.cpp \
    objs/resolucion.cpp \
    models/resolucionesmodel.cpp \
    objs/tema.cpp \
    gui/dlgresoluciones.cpp \
    gui/dlgciudades.cpp \
    gui/dlggestioncasas.cpp \
    gui/dlgasistentes.cpp \
    objs/aprobacion.cpp \
    gui/dlgaprobacionesentrada.cpp \
    models/aprobacionestablemodel.cpp \
    objs/licencia.cpp \
    gui/dlglicenciaentrada.cpp \
    gui/dlgestadisticas.cpp \
    objs/pena.cpp \
    gui/dlgpenaentrada.cpp \
    widgets/widgetextrainfos.cpp \
    objs/afiliacion.cpp \
    gui/dlgafiliacionentrada.cpp \
    models/afiliacionestablemodel.cpp \
    objs/ordenanza.cpp \
    gui/dlgordenanzaentrada.cpp \
    objs/retroreferencia.cpp \
    objs/qjsontreeitem.cpp \
    models/qjsonmodel.cpp \
    objs/sufragio.cpp \
    gui/dlgsufragiosentrada.cpp \
    widgets/widgettemas.cpp \
    objs/notas.cpp \
    widgets/widgetnotas.cpp \
    objs/infraccion.cpp \
    objs/declaracion.cpp \
    objs/diocesis.cpp \
    gui/dlgnuevadiocesis.cpp \
    models/diocesismodel.cpp \
    objs/obispo.cpp \
    gui/dlgnuevoobispo.cpp \
    gui/dlgnuevafuente.cpp \
    gui/dlgfuenteentrada.cpp \
    gui/dlgreforma.cpp \
    gui/dlgdeclaracionentrada.cpp \
    gui/dlgdeclaraciongeneralentrada.cpp \
    gui/dlginfraccionentrada.cpp \
    widgets/myqmdiarea.cpp \
    gui/dlgobispos.cpp \
    models/sqlfiltrogestor.cpp \
    widgets/fechasdelegate.cpp \
    gui/dlgnuevamisionfilipinas.cpp \
    objs/mision.cpp \
    models/misionesmodel.cpp \
    objs/viaje.cpp \
    gui/dlgviajeentrada.cpp \ 
    gui/dlgmisiones.cpp \
    gui/dlgentradamisionero.cpp \
    gui/dlgdiocesis.cpp \
    gui/dlgdiocesisdetalles.cpp \
    gui/dlganneenuevo.cpp \
    gui/dlggestionobras.cpp \
    gui/dlggestionpersonas.cpp \
    gui/dlgnuevareedicion.cpp \
    widgets/barralabel.cpp

HEADERS  += gui/mainwindow.h \
    gui/dlgnuevocapitulo.h \
    gui/dlgnuevaresolucion.h \
    models/temasmodel.h \
    models/lugaresmodel.h \
    models/personasmodel.h \
    models/casasmodel.h \
    gui/dlgnuevapersona.h \
    objs/persona.h \
    objs/casa.h \
    objs/obra.h \
    gui/dlgnuevacasa.h \
    gui/dlgcapitulos.h \
    models/obrasmodel.h \
    gui/dlgnuevaobra.h \
    objs/proxynombres.h \
    objs/lugar.h \
    gui/dlgdetalles.h \
    gui/dlgnuevaprovincia.h \
    objs/provincia.h \
    models/provinciasmodel.h \
    gui/dlgseleccionargeneral.h \
    objs/variados.h \
    gui/dlgnuevolugar.h \
    widgets/myqlineedit.h \
    gui/dlgtemas.h \
    models/capitulosmodel.h \
    objs/capitulo.h \
    objs/resolucion.h \
    models/resolucionesmodel.h \
    objs/tema.h \
    gui/dlgresoluciones.h \
    gui/dlgciudades.h \
    gui/dlggestioncasas.h \
    gui/dlgasistentes.h \
    objs/aprobacion.h \
    gui/dlgaprobacionesentrada.h \
    models/aprobacionestablemodel.h \
    objs/licencia.h \
    gui/dlglicenciaentrada.h \
    gui/dlgestadisticas.h \
    objs/pena.h \
    gui/dlgpenaentrada.h \
    widgets/widgetextrainfos.h \
    objs/afiliacion.h \
    gui/dlgafiliacionentrada.h \
    models/afiliacionestablemodel.h \
    objs/ordenanza.h \
    gui/dlgordenanzaentrada.h \
    objs/retroreferencia.h \
    objs/qjsontreeitem.h \
    models/qjsonmodel.h \
    objs/sufragio.h \
    gui/dlgsufragiosentrada.h \
    widgets/widgettemas.h \
    objs/notas.h \
    widgets/widgetnotas.h \
    objs/infraccion.h \
    objs/declaracion.h \
    objs/diocesis.h \
    gui/dlgnuevadiocesis.h \
    models/diocesismodel.h \
    objs/obispo.h \
    gui/dlgnuevoobispo.h \
    gui/dlgnuevafuente.h \
    gui/dlgfuenteentrada.h \
    gui/dlgreforma.h \
    gui/dlgdeclaracionentrada.h \
    gui/dlgdeclaraciongeneralentrada.h \
    gui/dlginfraccionentrada.h \
    widgets/myqmdiarea.h \
    gui/dlgobispos.h \
    models/sqlfiltrogestor.h \
    widgets/fechasdelegate.h \
    gui/dlgnuevamisionfilipinas.h \
    objs/mision.h \
    models/misionesmodel.h \
    objs/viaje.h \
    gui/dlgviajeentrada.h \ 
    gui/dlgmisiones.h \
    gui/dlgentradamisionero.h \
    gui/dlgdiocesis.h \
    gui/dlgdiocesisdetalles.h \
    gui/dlganneenuevo.h \
    gui/dlggestionobras.h \
    gui/dlggestionpersonas.h \
    gui/dlgnuevareedicion.h \
    widgets/barralabel.h

FORMS    += gui/mainwindow.ui \
    gui/dlgnuevocapitulo.ui \
    gui/dlgnuevaresolucion.ui \
    gui/dlgnuevapersona.ui \
    gui/dlgnuevacasa.ui \
    gui/dlgcapitulos.ui \
    gui/dlgnuevaobra.ui \
    gui/dlgdetalles.ui \
    gui/dlgnuevaprovincia.ui \
    gui/dlgseleccionargeneral.ui \
    gui/dlgnuevolugar.ui \
    gui/dlgtemas.ui \
    gui/dlgresoluciones.ui \
    gui/dlgciudades.ui \
    gui/dlggestioncasas.ui \
    gui/dlgasistentes.ui \
    gui/dlgaprobacionesentrada.ui \
    gui/dlglicenciaentrada.ui \
    gui/dlgestadisticas.ui \
    gui/dlgpenaentrada.ui \
    widgets/widgetextrainfos.ui \
    gui/dlgafiliacionentrada.ui \
    gui/dlgordenanzaentrada.ui \
    gui/dlgsufragiosentrada.ui \
    widgets/widgettemas.ui \
    widgets/widgetnotas.ui \
    gui/dlgnuevadiocesis.ui \
    gui/dlgnuevoobispo.ui \
    gui/dlgnuevafuente.ui \
    gui/dlgfuenteentrada.ui \
    gui/dlgreforma.ui \
    gui/dlgdeclaracionentrada.ui \
    gui/dlgdeclaraciongeneralentrada.ui \
    gui/dlginfraccionentrada.ui \
    gui/dlgobispos.ui \
    gui/dlgnuevamisionfilipinas.ui \
    gui/dlgviajeentrada.ui \ 
    gui/dlgmisiones.ui \
    gui/dlgentradamisionero.ui \
    gui/dlgdiocesis.ui \
    gui/dlgdiocesisdetalles.ui \
    gui/dlganneenuevo.ui \
    gui/dlggestionobras.ui \
    gui/dlggestionpersonas.ui \
    gui/dlgnuevareedicion.ui

RESOURCES += \
    icons.qrc
