#ifndef DFAGRAPH_H
#define DFAGRAPH_H

#include <map>
#include "NfaGraph.h"


class DfaGraph {
public:
    DfaGraph(Node *startState, const map<Node *, map<char, Node *>> &dTable);

    map<Node *, map<char, Node *>> getDTable() const;

    Node *getStartState() const;

    void setDTable(map<Node *, map<char, Node *>>);

    Node *move(Node *, char);

    Node *nullNode = new Node("null", false);
private:
    Node *startState;
    map<Node *, map<char, Node *>> DTable;


};

#endif
