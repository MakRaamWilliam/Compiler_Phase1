#include "Node.h"

#include <utility>
#include "Edge.h"

Node::Node(string name, int isend) {
    this->isend = isend;
    this->name = std::move(name);

}

Node::~Node() {
    this->edges.clear();
}

Node::Node(int isend) {
    this->isend = isend;
}

const string &Node::getName() const {
    return name;
}

void Node::setName(const string &name) {
    this->name = name;
}

int Node::checkEndState() const {
    return isend;
}

void Node::setEndState(int isFinal) {
    this->isend = isFinal;
}

vector<Edge *> Node::getEdges() const {
    return this->edges;
}

void Node::addEdge(Edge *edge) {
    this->edges.push_back(edge);
}

