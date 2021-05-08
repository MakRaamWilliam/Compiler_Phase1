#ifndef NFAGRAPH_H
#define NFAGRAPH_H

#include "Node.h"

class Node;

class NfaGraph {
public:
    NfaGraph(Node *start, Node *end);

    virtual ~NfaGraph();

public:
    Node *getStart() const;

    Node *getEnd() const;

    set<Node *> getendState();

private:
    Node *start;
    Node *end;
};


#endif
