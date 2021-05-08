#include "NfaGraph.h"

NfaGraph::NfaGraph(Node *start, Node *end) {
    this->start = start;
    this->end = end;
}

Node *NfaGraph::getStart() const {
    return start;
}

Node *NfaGraph::getEnd() const {
    return end;
}

NfaGraph::~NfaGraph() {
    free(this->start);
    free(this->end);
}

set<Node *> NfaGraph::getendState() {
    set<Node *> finalStates{};
    set<Node *> visited{};
    queue<Node *> s;
    unsigned count = 0;
    s.push(this->start);
    while (!s.empty()) {
        Node *node = s.front();
        s.pop();
        visited.insert(node);
        for (Edge *e:node->getEdges()) {
            Node *targetNode = e->getDestination();
            if (visited.find(targetNode) == visited.end()) {
                s.push(targetNode);
            }
        }
        if (node->checkEndState()) {
            finalStates.insert(node);
        }

    }
    return finalStates;
}
