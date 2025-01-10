cmake_minimum_required(VERSION 3.28)
project(Cafea)

set(CMAKE_CXX_STANDARD 17)

add_executable(Cafea cmake-build-debug/main.cpp
        cmake-build-debug/Angajat.h
        cmake-build-debug/Decision.h
        cmake-build-debug/Functions.h
        cmake-build-debug/FunctionsProduse.h
        cmake-build-debug/FunctionsIngrediente.h
        cmake-build-debug/FunctionsComenzi.h
        cmake-build-debug/FunctionsEvenimente.h
        cmake-build-debug/Gestiune.h
        cmake-build-debug/DecisionsE.h
)
