#ifndef MINIMIZTION_H
#define MINIMIZTION_H

#include "DfaGraph.h"

class Node;

class NfaGraph;

class Minimiztion {
public:
    void DFAMinimize(DfaGraph *dfa);

private:
    static Minimiztion *instance;
public:
    static Minimiztion *getInstance();

    map<Node *, map<char, Node *>> DFAStates;
    vector<vector<Node *>> partitions;

    vector<vector<Node *>> Minimize(const vector<vector<Node *>> &partitions);

private:

    bool areStatesUnique(const vector<vector<Node *>> &partitions, Node *, Node *);

    bool containedBySamePartition(const vector<vector<Node *>> &, Node *, Node *);

    bool containState(const vector<vector<Node *>> &, Node *);

    void updateTable(vector<Node *>);

};

#endif