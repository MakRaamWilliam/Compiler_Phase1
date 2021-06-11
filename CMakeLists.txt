cmake_minimum_required(VERSION 3.19)
project(Phase1)

set(CMAKE_CXX_STANDARD 14)

add_executable(Phase1 main.cpp Helper/Node.cpp Helper/Node.h Helper/Edge.cpp Helper/Edge.h Helper/NfaGraph.cpp Helper/NfaGraph.h Helper/MakeGraph.cpp Helper/MakeGraph.h Helper/DfaGraph.cpp Helper/DfaGraph.h Helper/ReadRules.cpp Helper/ReadRules.h Helper/LexicalRule.h Helper/LexBulider.cpp Helper/LexBulider.h Helper/Minimiztion.h Helper/Minimiztion.cpp Helper/NfaToDfa.cpp Helper/NfaToDfa.h Helper/ReadProg.cpp Helper/ReadProg.h Helper/ReadGrammars.cpp Helper/ReadGrammars.h Helper/ParserTable.cpp Helper/ParserTable.h Helper/production.cpp Helper/production.h)