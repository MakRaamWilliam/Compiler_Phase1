#ifndef MINIMIZTION_H
#define MINIMIZTION_H

#include "DfaGraph.h"

class Node;

class NfaGraph;

class Minimiztion {


public:
    static Minimiztion *getInstance();

    static Minimiztion *instance;

    map<Node *, map<char, Node *>> dfaStates;

    vector<vector<Node *>> partts;

    vector<vector<Node *>> Minimize(const vector<vector<Node *>> &parrts);

private:

    bool compState(const vector<vector<Node *>> &partitions, Node *state1, Node *state2);

    bool HaveState(const vector<vector<Node *>> &partts, Node *state);

    bool HaveEqualstate(const vector<vector<Node *>> &partts, Node *state1, Node *state2);

    void updateTable(vector<Node *> partts);

};

#endif