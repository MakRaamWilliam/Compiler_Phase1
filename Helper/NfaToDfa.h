#ifndef NFATODFA_H
#define NFATODFA_H

#include "DfaGraph.h"

class NfaToDfa {
public:
    static NfaToDfa *getInstance();

    DfaGraph *convert(NfaGraph *nfa, const set<char> &alphabet);


private:
    NfaToDfa() = default;

    static NfaToDfa *instance;

    bool CompSets(const set<Node *> &x, set<Node *> y);

    set<Node *> move(const set<Node *> &nodes, char symbol);

    set<Node *> closure(set<Node *> nodes);

    Node *nullNode = new Node("null", false);

};


#endif
