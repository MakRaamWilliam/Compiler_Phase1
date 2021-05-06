#include "NFA.h"

NFA::NFA(Node *start, Node *end) {
    this->start = start;
    this->end = end;
}

Node *NFA::getStart() const {
    return start;
}

Node *NFA::getEnd() const {
    return end;
}

NFA::~NFA() {
    free(this->start);
    free(this->end);
}

string NFA::toString() {
    string str;
    unordered_map<Node *, unsigned> visited{};
    queue<Node *> s;
    unsigned count = 0;
    visited[this->start] = count;
    s.push(this->start);
    count++;
    while (!s.empty()) {
        Node *node = s.front();
        s.pop();

        for (Edge *e:node->getEdges()) {
            Node *targetNode = e->getDestination();
            if (visited.find(targetNode) == visited.end()) {
                visited[targetNode] = count;
                count++;
                s.push(targetNode);
            }
            if (e->isEPSTransition()) {
                str += "s" + to_string(visited[node]) + " ----->" + "s" + to_string(visited[targetNode]) + "\n";
            } else {
                str += "s" + to_string(visited[node]) + " ---(" + e->getStartAlphabet() + "-" + e->getEndAlphabet() +
                       ")-->" + "s" + to_string(visited[targetNode]) + "\n";
            }
        }

    }
    str += this->getEnd()->getName() + " START : s" + to_string(visited[this->start]) + "\n";
    return str;
}

set<Node *> NFA::getFinalStates() {
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
        if (node->isFinalState()) {
            finalStates.insert(node);
        }

    }
    return finalStates;
}
