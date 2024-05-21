cmake_minimum_required(VERSION 3.27)
project(TAD_Matrice)

set(CMAKE_CXX_STANDARD 14)

include_directories("Proiect C++")
include_directories(Teste)

add_executable(TAD_Matrice
        "Proiect C++/App.cpp"
        "Proiect C++/Matrice.cpp"
        "Proiect C++/Matrice.h"
        Teste/TestExtins.cpp
        Teste/TestExtins.h
        Teste/TestScurt.cpp
        Teste/TestScurt.h)
