//
// Created by makram99 on 6/2/2021.
//
#include "nonTerminal.h"
#ifndef PHASE1_PARSERTABLE_H
#define PHASE1_PARSERTABLE_H

class ParserTable {
public:
    static ParserTable *getInstance();
    map <char,char>  first;
    map <char,char>  follow ;
    map<string,string> grammer;
    vector <char> terminal ;
    vector <char> nonTerminal ;
    bool isAmbiguity();
    map<pair<char,char>,string> getTable();

private:
    ParserTable();
    static ParserTable* instance;
    bool  flagIsAmbiguity;
    map<pair<char,char>,string> table;

};


#endif //PHASE1_PARSERTABLE_H
