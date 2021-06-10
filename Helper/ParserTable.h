#ifndef PHASE1_PARSERTABLE_H
#define PHASE1_PARSERTABLE_H

#include "production.h"
#include "ReadProg.h"
class ParserTable {
public:
    virtual ~ParserTable() = default;

    static ParserTable *getInstance();

    bool isAmbiguity();

    void calcFollow(production *t, vector<production *> nonTerminal);

    void SetFollow(vector<production *> nonTerminal);

    void SetFirst(vector<production *> nonTerminal);

    map<pair<production *, string>, vector<production *>> getTable(vector<production *> nonTerminal);

    void printTable(vector<production *> nonTerminal);

    void getOutput(DfaGraph *dfa, production *start,ifstream &file);

private:
    static ParserTable *instance;

    ParserTable();

    map<pair<production *, string>, vector<production *>> table;
    bool Ambiguity;
    unordered_set<string> terminalSet;
};


#endif //PHASE1_PARSERTABLE_H
