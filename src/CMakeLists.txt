# la explicación de esta cosa tan rara está aquí
# https://cmake.org/pipermail/cmake/2010-July/037922.html

# el asunto clave es que cada add_subdirectory crea su propio
# scope para las variables. Pero: lo que no entiendo aquí es por qué
# coño ponemos fuentes_SRCS SIN ${} si realmetne entiendo que
# se está refiriendo a la variable q viene del CMaKelists principal. 

list(APPEND fuentes_SRCS
   ${CMAKE_CURRENT_LIST_DIR}/objs/afiliacion.cpp
   ${CMAKE_CURRENT_LIST_DIR}/objs/aprobacion.cpp
   ${CMAKE_CURRENT_LIST_DIR}/objs/capitulo.cpp
   ${CMAKE_CURRENT_LIST_DIR}/objs/casa.cpp
   ${CMAKE_CURRENT_LIST_DIR}/objs/declaracion.cpp
   ${CMAKE_CURRENT_LIST_DIR}/objs/diocesis.cpp
   ${CMAKE_CURRENT_LIST_DIR}/objs/infraccion.cpp
   ${CMAKE_CURRENT_LIST_DIR}/objs/licencia.cpp
   ${CMAKE_CURRENT_LIST_DIR}/objs/lugar.cpp
   ${CMAKE_CURRENT_LIST_DIR}/objs/mision.cpp
   ${CMAKE_CURRENT_LIST_DIR}/objs/notas.cpp
   ${CMAKE_CURRENT_LIST_DIR}/objs/obispo.cpp
   ${CMAKE_CURRENT_LIST_DIR}/objs/obra.cpp
   ${CMAKE_CURRENT_LIST_DIR}/objs/ordenanza.cpp
   ${CMAKE_CURRENT_LIST_DIR}/objs/pena.cpp
   ${CMAKE_CURRENT_LIST_DIR}/objs/persona.cpp
   ${CMAKE_CURRENT_LIST_DIR}/objs/provincia.cpp
   ${CMAKE_CURRENT_LIST_DIR}/objs/proxynombres.cpp
   ${CMAKE_CURRENT_LIST_DIR}/objs/qjsontreeitem.cpp
   ${CMAKE_CURRENT_LIST_DIR}/objs/resolucion.cpp
   ${CMAKE_CURRENT_LIST_DIR}/objs/retroreferencia.cpp
   ${CMAKE_CURRENT_LIST_DIR}/objs/sufragio.cpp
   ${CMAKE_CURRENT_LIST_DIR}/objs/tema.cpp
   ${CMAKE_CURRENT_LIST_DIR}/objs/viaje.cpp
   ${CMAKE_CURRENT_LIST_DIR}/objs/variados.h

   # ahora los modelos
   ${CMAKE_CURRENT_LIST_DIR}/models/afiliacionestablemodel.cpp
   ${CMAKE_CURRENT_LIST_DIR}/models/aprobacionestablemodel.cpp
   ${CMAKE_CURRENT_LIST_DIR}/models/capitulosmodel.cpp
   ${CMAKE_CURRENT_LIST_DIR}/models/casasmodel.cpp
   ${CMAKE_CURRENT_LIST_DIR}/models/diocesismodel.cpp
   ${CMAKE_CURRENT_LIST_DIR}/models/lugaresmodel.cpp
   ${CMAKE_CURRENT_LIST_DIR}/models/misionesmodel.cpp
   ${CMAKE_CURRENT_LIST_DIR}/models/obrasmodel.cpp
   ${CMAKE_CURRENT_LIST_DIR}/models/personasmodel.cpp
   ${CMAKE_CURRENT_LIST_DIR}/models/provinciasmodel.cpp
   ${CMAKE_CURRENT_LIST_DIR}/models/qjsonmodel.cpp
   ${CMAKE_CURRENT_LIST_DIR}/models/resolucionesmodel.cpp
   ${CMAKE_CURRENT_LIST_DIR}/models/sqlfiltrogestor.cpp
   ${CMAKE_CURRENT_LIST_DIR}/models/temasmodel.cpp

   # ahora el GUI (los cpp)
   ${CMAKE_CURRENT_LIST_DIR}/gui/dlgafiliacionentrada.cpp
   ${CMAKE_CURRENT_LIST_DIR}/gui/dlganneenuevo.cpp
   ${CMAKE_CURRENT_LIST_DIR}/gui/dlgaprobacionesentrada.cpp
   ${CMAKE_CURRENT_LIST_DIR}/gui/dlgasistentes.cpp
   ${CMAKE_CURRENT_LIST_DIR}/gui/dlgcapitulos.cpp
   ${CMAKE_CURRENT_LIST_DIR}/gui/dlgciudades.cpp
   ${CMAKE_CURRENT_LIST_DIR}/gui/dlgdeclaracionentrada.cpp
   ${CMAKE_CURRENT_LIST_DIR}/gui/dlgdeclaraciongeneralentrada.cpp
   ${CMAKE_CURRENT_LIST_DIR}/gui/dlgdetalles.cpp
   ${CMAKE_CURRENT_LIST_DIR}/gui/dlgdiocesis.cpp
   ${CMAKE_CURRENT_LIST_DIR}/gui/dlgdiocesisdetalles.cpp
   ${CMAKE_CURRENT_LIST_DIR}/gui/dlgentradamisionero.cpp
   ${CMAKE_CURRENT_LIST_DIR}/gui/dlgestadisticas.cpp
   ${CMAKE_CURRENT_LIST_DIR}/gui/dlgfuenteentrada.cpp
   ${CMAKE_CURRENT_LIST_DIR}/gui/dlggestioncasas.cpp
   ${CMAKE_CURRENT_LIST_DIR}/gui/dlggestionobras.cpp
   ${CMAKE_CURRENT_LIST_DIR}/gui/dlggestionpersonas.cpp
   ${CMAKE_CURRENT_LIST_DIR}/gui/dlginfraccionentrada.cpp
   ${CMAKE_CURRENT_LIST_DIR}/gui/dlglicenciaentrada.cpp
   ${CMAKE_CURRENT_LIST_DIR}/gui/dlgmisiones.cpp
   ${CMAKE_CURRENT_LIST_DIR}/gui/dlgnuevacasa.cpp
   ${CMAKE_CURRENT_LIST_DIR}/gui/dlgnuevadiocesis.cpp
   ${CMAKE_CURRENT_LIST_DIR}/gui/dlgnuevafuente.cpp
   ${CMAKE_CURRENT_LIST_DIR}/gui/dlgnuevamisionfilipinas.cpp
   ${CMAKE_CURRENT_LIST_DIR}/gui/dlgnuevaobra.cpp
   ${CMAKE_CURRENT_LIST_DIR}/gui/dlgnuevapersona.cpp
   ${CMAKE_CURRENT_LIST_DIR}/gui/dlgnuevaprovincia.cpp
   ${CMAKE_CURRENT_LIST_DIR}/gui/dlgnuevareedicion.cpp
   ${CMAKE_CURRENT_LIST_DIR}/gui/dlgnuevaresolucion.cpp
   ${CMAKE_CURRENT_LIST_DIR}/gui/dlgnuevocapitulo.cpp
   ${CMAKE_CURRENT_LIST_DIR}/gui/dlgnuevolugar.cpp
   ${CMAKE_CURRENT_LIST_DIR}/gui/dlgnuevoobispo.cpp
   ${CMAKE_CURRENT_LIST_DIR}/gui/dlgobispos.cpp
   ${CMAKE_CURRENT_LIST_DIR}/gui/dlgordenanzaentrada.cpp
   ${CMAKE_CURRENT_LIST_DIR}/gui/dlgpenaentrada.cpp
   ${CMAKE_CURRENT_LIST_DIR}/gui/dlgreforma.cpp
   ${CMAKE_CURRENT_LIST_DIR}/gui/dlgresoluciones.cpp
   ${CMAKE_CURRENT_LIST_DIR}/gui/dlgseleccionargeneral.cpp
   ${CMAKE_CURRENT_LIST_DIR}/gui/dlgsufragiosentrada.cpp
   ${CMAKE_CURRENT_LIST_DIR}/gui/dlgtemas.cpp
   ${CMAKE_CURRENT_LIST_DIR}/gui/dlgviajeentrada.cpp
   ${CMAKE_CURRENT_LIST_DIR}/gui/mainwindow.cpp

   # ahora el GUI (los cpp)
   ${CMAKE_CURRENT_LIST_DIR}/gui/dlgafiliacionentrada.ui
   ${CMAKE_CURRENT_LIST_DIR}/gui/dlganneenuevo.ui
   ${CMAKE_CURRENT_LIST_DIR}/gui/dlgaprobacionesentrada.ui
   ${CMAKE_CURRENT_LIST_DIR}/gui/dlgasistentes.ui
   ${CMAKE_CURRENT_LIST_DIR}/gui/dlgcapitulos.ui
   ${CMAKE_CURRENT_LIST_DIR}/gui/dlgciudades.ui
   ${CMAKE_CURRENT_LIST_DIR}/gui/dlgdeclaracionentrada.ui
   ${CMAKE_CURRENT_LIST_DIR}/gui/dlgdeclaraciongeneralentrada.ui
   ${CMAKE_CURRENT_LIST_DIR}/gui/dlgdetalles.ui
   ${CMAKE_CURRENT_LIST_DIR}/gui/dlgdiocesisdetalles.ui
   ${CMAKE_CURRENT_LIST_DIR}/gui/dlgdiocesis.ui
   ${CMAKE_CURRENT_LIST_DIR}/gui/dlgentradamisionero.ui
   ${CMAKE_CURRENT_LIST_DIR}/gui/dlgestadisticas.ui
   ${CMAKE_CURRENT_LIST_DIR}/gui/dlgfuenteentrada.ui
   ${CMAKE_CURRENT_LIST_DIR}/gui/dlggestioncasas.ui
   ${CMAKE_CURRENT_LIST_DIR}/gui/dlggestionobras.ui
   ${CMAKE_CURRENT_LIST_DIR}/gui/dlggestionpersonas.ui
   ${CMAKE_CURRENT_LIST_DIR}/gui/dlginfraccionentrada.ui
   ${CMAKE_CURRENT_LIST_DIR}/gui/dlglicenciaentrada.ui
   ${CMAKE_CURRENT_LIST_DIR}/gui/dlgmisiones.ui
   ${CMAKE_CURRENT_LIST_DIR}/gui/dlgnuevacasa.ui
   ${CMAKE_CURRENT_LIST_DIR}/gui/dlgnuevadiocesis.ui
   ${CMAKE_CURRENT_LIST_DIR}/gui/dlgnuevafuente.ui
   ${CMAKE_CURRENT_LIST_DIR}/gui/dlgnuevamisionfilipinas.ui
   ${CMAKE_CURRENT_LIST_DIR}/gui/dlgnuevaobra.ui
   ${CMAKE_CURRENT_LIST_DIR}/gui/dlgnuevapersona.ui
   ${CMAKE_CURRENT_LIST_DIR}/gui/dlgnuevaprovincia.ui
   ${CMAKE_CURRENT_LIST_DIR}/gui/dlgnuevareedicion.ui
   ${CMAKE_CURRENT_LIST_DIR}/gui/dlgnuevaresolucion.ui
   ${CMAKE_CURRENT_LIST_DIR}/gui/dlgnuevocapitulo.ui
   ${CMAKE_CURRENT_LIST_DIR}/gui/dlgnuevolugar.ui
   ${CMAKE_CURRENT_LIST_DIR}/gui/dlgnuevoobispo.ui
   ${CMAKE_CURRENT_LIST_DIR}/gui/dlgobispos.ui
   ${CMAKE_CURRENT_LIST_DIR}/gui/dlgordenanzaentrada.ui
   ${CMAKE_CURRENT_LIST_DIR}/gui/dlgpenaentrada.ui
   ${CMAKE_CURRENT_LIST_DIR}/gui/dlgreforma.ui
   ${CMAKE_CURRENT_LIST_DIR}/gui/dlgresoluciones.ui
   ${CMAKE_CURRENT_LIST_DIR}/gui/dlgseleccionargeneral.ui
   ${CMAKE_CURRENT_LIST_DIR}/gui/dlgsufragiosentrada.ui
   ${CMAKE_CURRENT_LIST_DIR}/gui/dlgtemas.ui
   ${CMAKE_CURRENT_LIST_DIR}/gui/dlgviajeentrada.ui
   ${CMAKE_CURRENT_LIST_DIR}/gui/mainwindow.ui

   # widgets (CPP)
   ${CMAKE_CURRENT_LIST_DIR}/widgets/barralabel.cpp
   ${CMAKE_CURRENT_LIST_DIR}/widgets/fechasdelegate.cpp
   ${CMAKE_CURRENT_LIST_DIR}/widgets/myqlineedit.cpp
   ${CMAKE_CURRENT_LIST_DIR}/widgets/myqmdiarea.cpp
   ${CMAKE_CURRENT_LIST_DIR}/widgets/widgetextrainfos.cpp
   ${CMAKE_CURRENT_LIST_DIR}/widgets/widgetnotas.cpp
   ${CMAKE_CURRENT_LIST_DIR}/widgets/widgettemas.cpp

   # widgets (UI)
   ${CMAKE_CURRENT_LIST_DIR}/widgets/widgetextrainfos.ui
   ${CMAKE_CURRENT_LIST_DIR}/widgets/widgetnotas.ui
   ${CMAKE_CURRENT_LIST_DIR}/widgets/widgettemas.ui
   
)

# luego con esto de PARENT_SCOPE lo que hacemos es modificar
# la variable del scope principal...
set(fuentes_SRCS ${fuentes_SRCS} PARENT_SCOPE)


