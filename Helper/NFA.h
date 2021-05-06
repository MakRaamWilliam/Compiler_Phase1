#ifndef LEXICAL_ANALYZER_GENERATOR_NFA_H
#define LEXICAL_ANALYZER_GENERATOR_NFA_H

#include "Node.h"

class Node;

class NFA {
public:
    NFA(Node *start, Node *end);

    virtual ~NFA();

public:
    Node *getStart() const;

    Node *getEnd() const;

    string toString();

    set<Node *> getFinalStates();

private:
    Node *start;
    Node *end;

};


#endif //LEXICAL_ANALYZER_GENERATOR_NFA_H
