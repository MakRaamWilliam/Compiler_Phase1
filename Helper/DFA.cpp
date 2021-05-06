#include "DFA.h"

#include <utility>


DFA::DFA(Node *startState, const map<Node *, map<char, Node *>> &dTable) {
    this->startState = startState;
    this->DTable = dTable;
}

map<Node *, map<char, Node *>> DFA::getDTable() const {
    return DTable;
}

Node *DFA::getStartState() const {
    return startState;
}

void DFA::setDTable(map<Node *, map<char, Node *>> dTable) {
    DTable = std::move(dTable);
}

Node *DFA::move(Node *state, char symbol) {
    if (DTable.at(state).find(symbol) != DTable.at(state).end()) {
        return this->DTable.at(state).at(symbol);
    }
    return nullNode;
}
