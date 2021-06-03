#include "nonTerminal.h"
#ifndef PHASE1_PARSERTABLE_H
#define PHASE1_PARSERTABLE_H

class ParserTable {
public:
    static ParserTable *getInstance();
    bool isAmbiguity();
    map<pair<string ,string>,string> getTable(map <string,unordered_set<string>>,map <string,unordered_set<string>>,
                                              map <string,unordered_set<string>>,vector<string>,vector<string>);

private:
    ParserTable();
    static ParserTable* instance;
    bool  flagIsAmbiguity;
    map<pair<char,char>,string> table;
    map <string,unordered_set<string>>  first;
    map <string,unordered_set<string>>  follow ;
    map<string,unordered_set<string>> grammer;
    vector <string> terminal ;
    vector <string> nonTerminal ;
};


#endif //PHASE1_PARSERTABLE_H
