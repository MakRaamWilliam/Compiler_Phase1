#include <iostream>
#include <bits/stdc++.h>
#include <algorithm>

#ifndef PHASE1_NONTERMINAL_H
#define PHASE1_NONTERMINAL_H

using namespace std;
enum productionType {
    terminal,non_terminal
};

class production {
public:
    string value;
    vector< vector< production > > RHS;
    bool eps;

    production(string val,productionType type);
    productionType type;

private:

};


#endif //PHASE1_NONTERMINAL_H
