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


    vector<production *> ReadGrammarFile(const string &grammerfile);

    vector<production *> parseGrammar(vector<pair<string, string> > lines);

    static ReadGrammars *getInstance();


private:
    regex form;
    regex theRest;
    smatch match;

private:
    static ReadGrammars *instance;

    ReadGrammars();

    static vector<vector<production *> >
    split(const string &str, production *t, map<string, production *> &nonterminals,
          map<string, production *> &terminals);

    static production *findNonTerminalRHS(string name, map<string, production *> &nonterminals, production *t);

    static production *findNonTerminalLHS(string name, map<string, production *> &nonterminals);

    static production *findTerminal(const string &name, map<string, production *> &terminals);

    static string removeSpaces(string str);

};

#endif