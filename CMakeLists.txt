cmake_minimum_required(VERSION 2.8.12)

project(qtPredicadores)

# Find includes in corresponding build directories
set(CMAKE_INCLUDE_CURRENT_DIR ON)
# Instruct CMake to run moc automatically when needed
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTORCC ON)

# para que genere una compilation database
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

find_package(Qt5Core)
# para usar con SQL 
find_package(Qt5Sql REQUIRED)
# para usar en una aplicación con ventanas
find_package(Qt5Widgets CONFIG REQUIRED)

# Metemos en una variable los nombres de los ficheros 
set(fuentes_SRCS src/main.cpp)
add_subdirectory(src)

# aquí se puede poner:
add_executable(${PROJECT_NAME} ${fuentes_SRCS} src/icons.qrc)

target_link_libraries(${PROJECT_NAME} Qt5::Widgets Qt5::Sql)

