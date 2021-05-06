#ifndef CONVERTER_H
#define CONVERTER_H

#include "DFA.h"

class Converter {
public:
    static Converter *getInstance();

    DFA *convert(NFA *nfa, const set<char> &alphabet);


private:
    Converter() = default;

    static Converter *instance;

    bool compareSets(const set<Node *> &x, set<Node *> y);

    set<Node *> move(const set<Node *> &nodes, char symbol);

    set<Node *> closure(set<Node *> nodes);

    Node *nullNode = new Node("null", false);

};


#endif
