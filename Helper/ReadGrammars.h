#ifndef PHASE1_READGRAMMARS_H
#define PHASE1_READGRAMMARS_H

#include <iostream>
#include <bits/stdc++.h>
#include <regex>
#include <algorithm>
#include "production.h"
using namespace std;

class ReadGrammars {

public:
    virtual ~ReadGrammars() = default;

    map<string, production *> ReadGrammarFile(const string &grammerfile);

//    void makeTransTable(const string &fileName, const map<Node *, map<char, Node *>> &table, const set<char> &alpha);

    static ReadGrammars *getInstance();



private:
    regex form;
    smatch match;

private:
    static ReadGrammars *instance;

    ReadGrammars();

    static vector< vector< production *> >  split(const string &str,production *t,map<string, production *> &nonterminals,map<string, production *> &terminals);
    static production* findNonTerminal(string name,map<string, production *> &nonterminals);
    static production* findTerminal(const string &name,map<string, production *> &terminals);

    static string removeSpaces(string str);
//
//    static vector<string> splitSpaces(string splitted);
//

//
//    static vector<string> split(const string &str);
//
//    static vector<string> splitExpression(const string &str);
//
//    static vector<string> splitEachChar(const string &str);






};

#endif //PHASE1_READGRAMMARS_H