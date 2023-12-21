cmake_minimum_required(VERSION 3.26)
project(cgg)

set(CMAKE_CXX_STANDARD 17)

add_executable(cgg main.cpp
        lex/lexAnalyser.h
        lex/lexAnalyser.cpp
        lex/lexAnalyser.cpp
        parser/parser.cpp
        parser/parser.h
        dataExplorer/dataExplorer.cpp
        dataExplorer/dataExplorer.h
        parser/parser.constDecl.cpp
        parser/parser.varDecl.cpp
        parser/parser.exp.cpp
        parser/parser.funcDef.cpp
        parser/parser.strCon.cpp
        parser/parser.stmt.cpp
        dataExplorer/dataExplorer.symbol.cpp
        midcode/midCode.cpp
        midcode/midCode.stmt.cpp
        midcode/midCode.exp.cpp
        midcode/midCode.func.cpp
        midcode/midCode.constDecl.cpp
        midcode/midCode.varDecl.cpp
        dataExplorer/dataExplorer.midCode.cpp
        dataExplorer/dataExplorer.tempVarPool.cpp
)
