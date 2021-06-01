#include <iostream>
#include <bits/stdc++.h>
#include <algorithm>

#ifndef PHASE1_NONTERMINAL_H
#define PHASE1_NONTERMINAL_H

using namespace std;

class nonTerminal {
public:
    string value;
    vector<string> terms;
    bool eps;

    nonTerminal(string val,vector <string> term);

private:

};


#endif //PHASE1_NONTERMINAL_H
