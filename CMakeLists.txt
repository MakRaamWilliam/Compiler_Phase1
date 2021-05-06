cmake_minimum_required(VERSION 3.19)
project(Phase1)

set(CMAKE_CXX_STANDARD 14)

add_executable(Phase1 main.cpp Helper/Node.cpp Helper/Node.h Helper/Edge.cpp Helper/Edge.h Helper/NFA.cpp Helper/NFA.h Helper/Builder.cpp Helper/Builder.h Helper/DFA.cpp Helper/DFA.h Helper/LexRules.cpp Helper/LexRules.h Helper/LexicalRule.h Helper/LexBulider.cpp Helper/LexBulider.h Helper/Minimiztion.h Helper/Minimiztion.cpp Helper/Converter.cpp Helper/Converter.h Helper/Scanner.cpp Helper/Scanner.h)