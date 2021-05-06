#ifndef LEXICAL_ANALYZER_GENERATOR_DFA_H
#define LEXICAL_ANALYZER_GENERATOR_DFA_H

#include <map>
#include "NFA.h"


class DFA {
public:
    DFA(Node *startState, const map<Node *, map<char, Node *>> &dTable);

    map<Node *, map<char, Node *>> getDTable() const;

    Node *getStartState() const;

    void setDTable(map<Node *, map<char, Node *>> dTable);

    Node *move(Node *state, char symbol);

private:
    Node *startState;
    map<Node *, map<char, Node *>> DTable;
    Node *nullNode = new Node("null", false);

    /**
     Sim:
     map<   Node*        ,        map<char , Node*>    >
            dfaStates
                             a   b   c   d   e ...    <----- alphabet
               A             B   -   -   E   - ...    <----- go from A to B by input a.
               .
               .
               .
     **/

};

#endif //LEXICAL_ANALYZER_GENERATOR_DFA_H
