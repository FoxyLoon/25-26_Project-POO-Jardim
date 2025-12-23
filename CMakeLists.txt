cmake_minimum_required(VERSION 4.0)
project(Project_POO_Jardim_25-26 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(Project_POO_Jardim_25-26 main.cpp
        src/ferramentas/Adubo.cpp
        src/ferramentas/Ferramenta.cpp
        src/ferramentas/Regador.cpp
        src/ferramentas/TesouraPoda.cpp
        src/jardim/Jardim.cpp
        src/jardim/Solo.cpp
        src/jardineiro/Jardineiro.cpp
        src/simulador/Simulador.cpp
        src/plantas/Cacto.cpp
        src/plantas/ErvaDaninha.cpp
        src/plantas/Planta.cpp
        src/plantas/Roseira.cpp
)