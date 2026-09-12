cmake_minimum_required(VERSION 4.0)
project(AutoMat)

set(CMAKE_CXX_STANDARD 20)

add_executable(AutoMat main.cpp
        AST.cpp
        AST.h
        Parser.cpp
        Parser.h
        Nfa.cpp
        Nfa.h
        NfaCompiler.cpp
        NfaCompiler.h)
