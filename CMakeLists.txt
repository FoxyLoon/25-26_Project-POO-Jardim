cmake_minimum_required(VERSION 3.20)
project(TP)

# Define a versão do C++ a utilizar
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Adiciona todos os diretórios onde existem ficheiros .h
include_directories(
        src
        src/simulador
        src/jardim
        src/jardineiro
        src/plantas
        src/faramentas
)

# Encontra automaticamente todos os ficheiros .cpp dentro de src/
file(GLOB_RECURSE SOURCE_FILES
        src/*.cpp
        main.cpp
)

# Cria o executável
add_executable(TP ${SOURCE_FILES})
