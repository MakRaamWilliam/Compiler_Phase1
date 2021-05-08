#ifndef NFATODFA_H
#define NFATODFA_H

#include "DfaGraph.h"

class NfaToDfa {
public:
    static NfaToDfa *getInstance();

    DfaGraph *Convert(NfaGraph *Nfa, const set<char> &alpha);


private:
    NfaToDfa() = default;

    static NfaToDfa *instance;

    bool CompSets(const set<Node *> &x, set<Node *> y);

    set<Node *> Change(const set<Node *> &nodes, char symbol);

    set<Node *> closure(set<Node *> nodes);

    Node *nullNode = new Node("null", false);

};


#endif
