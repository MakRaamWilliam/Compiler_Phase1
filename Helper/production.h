#include <iostream>
#include <bits/stdc++.h>
#include <algorithm>

#ifndef PHASE1_NONTERMINAL_H
#define PHASE1_NONTERMINAL_H

using namespace std;
enum productionType {
    terminal, non_terminal
};

class production {
public:
    string value;
    string temp;
    vector<vector<production *> > RHS;
    vector<production *> appearance;
    bool eps;
    map<string, vector<production *>> PrFirst;
    map<string, vector<production *>> follow;

    production(string val, productionType type);

    void SetFirst(map<string, production *> nonTerminal);

    productionType type;

    void print();

private:

};


#endif //PHASE1_NONTERMINAL_H
