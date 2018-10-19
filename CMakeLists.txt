# aquí hay una config más complicada y completa para compilar con Qt
# https://github.com/nholthaus/cmake-qt-project/blob/master/CMakeLists.txt
# otra muy buena y larga es la de Clementine

cmake_minimum_required(VERSION 2.8.12)

project(qtPredicadores)

# Find includes in corresponding build directories
set(CMAKE_INCLUDE_CURRENT_DIR ON)
# Instruct CMake to run moc automatically when needed
set(CMAKE_AUTOMOC ON)
# Create code from a list of Qt designer ui files
set(CMAKE_AUTOUIC ON)
# Esto creo que sirve para añadir los resources?
set(CMAKE_AUTORCC ON)

# para que genere una compilation database
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# con esto se pone que use C++11, pero cuidado esto sirve para clang?
# eso es lo que utilizo en emacs conn rtags...
# set (CMAKE_CXX_STANDARD 11)

find_package(Qt5Core)
# para usar con SQL 
find_package(Qt5Sql REQUIRED)
# para usar en una aplicación con ventanas
find_package(Qt5Widgets CONFIG REQUIRED)
# atención: aquí dicen que es mejor esto:
# https://blog.kitware.com/cmake-finding-qt5-the-right-way/
# find_package(Qt5 COMPONENTS Core Widgets REQUIRED)

# Metemos en una variable los nombres de los ficheros 
set(fuentes_SRCS src/main.cpp)
add_subdirectory(src)

# aquí se puede poner:
add_executable(${PROJECT_NAME} ${fuentes_SRCS} src/icons.qrc)

# En el caso de programa de consola usamos esto: 
#target_link_libraries(${PROJECT_NAME} Qt5::Core)

# En el caso de programa gráfico usamos esto: 
#target_link_libraries(${PROJECT_NAME} Qt5::Widgets)

# en el caso de uso de QtSql
target_link_libraries(${PROJECT_NAME} Qt5::Widgets Qt5::Sql)

