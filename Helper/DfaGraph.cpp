#include "DfaGraph.h"

#include <utility>


DfaGraph::DfaGraph(Node *startState, const map<Node *, map<char, Node *>> &dTable) {
    this->startState = startState;
    this->DTable = dTable;
}

map<Node *, map<char, Node *>> DfaGraph::getDTable() const {
    return DTable;
}

Node *DfaGraph::getStartState() const {
    return startState;
}

void DfaGraph::setDTable(map<Node *, map<char, Node *>> dTable) {
    DTable = std::move(dTable);
}

Node *DfaGraph::move(Node *state, char symbol) {
    if (DTable.at(state).find(symbol) != DTable.at(state).end()) {
        return this->DTable.at(state).at(symbol);
    }
    return nullNode;
}
