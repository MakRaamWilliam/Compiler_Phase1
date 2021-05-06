#ifndef LEXICAL_ANALYZER_GENERATOR_MINIMIZER_H
#define LEXICAL_ANALYZER_GENERATOR_MINIMIZER_H

#include "DFA.h"

class Node;

class NFA;

class Minimizer {
public:
    void DFAMinimize(DFA *dfa);

private:
    static Minimizer *instance;
public:
    static Minimizer *getInstance();

private:
    vector<vector<Node *>> partitions;
    map<Node *, map<char, Node *>> DFAStates;

    vector<vector<Node *>> Minimize(const vector<vector<Node *>> &partitions);

    bool areStatesUnique(const vector<vector<Node *>> &partitions, Node *state1, Node *state2);

    bool containedBySamePartition(const vector<vector<Node *>> &partitions, Node *State1, Node *State2);

    bool containState(const vector<vector<Node *>> &partitions, Node *state);

    void updateTable(vector<Node *> temp);

};

#endif //LEXICAL_ANALYZER_GENERATOR_MINIMIZER_H