# @author Saul Ruiz Fernandez
# @date 2023-08-04
# @brief Archivo de configuración de CMake para el programa del reloj solar

cmake_minimum_required(VERSION 3.1)

project(complejos
    VERSION 1.0
    DESCRIPTION "Archivo de CMake para reloj solar"
    LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Donde se almacenaran los ejecutables binarios
set(EXECUTABLE_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/build)

# Opciones del compilador
set(CMAKE_CXX_FLAGS_DEBUG "-g -O0 -Wall -Wextra -Wpedantic -Weffc++")
set(CMAKE_CXX_FLAGS_RELEASE "-O3")

# Donde encontrar los archivos de cabecera *.h
include_directories(${PROJECT_SOURCE_DIR}/src)

# Añade un ejecutable que invocara el resto de codigo fuente del directorio src
add_executable(reloj
    src/reloj-solar-main.cc
    src/reloj-solar.cc
    src/reloj-solar.h)

# Añadimos las caracteristicas esperadas al target
target_compile_features(reloj PRIVATE cxx_std_17)

# Añadimos al target las opciones del compilador
target_compile_options(reloj PRIVATE -Wall -Wextra -Wpedantic -Weffc++)
