cmake_minimum_required(VERSION 3.26)
project(cgg)

set(CMAKE_CXX_STANDARD 17)

add_executable(cgg main.cpp
        lexAnalyser.h
        lexAnalyser.cpp
        lexAnalyser.cpp
        parser.cpp
        parser.h
        dataExplorer.cpp
        dataExplorer.h
        parser.constDecl.cpp
        parser.varDecl.cpp
        parser.exp.cpp
        parser.funcDef.cpp
        parser.strCon.cpp
        parser.stmt.cpp
)
