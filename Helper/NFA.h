#ifndef NFA_H
#define NFA_H

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


#endif 
