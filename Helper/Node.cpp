#include "Node.h"

#include <utility>
#include "Edge.h"

Node::Node(string name, int isFinal) {
    this->isFinal = isFinal;
    this->name = std::move(name);

}

Node::~Node() {
    this->edges.clear();
}

Node::Node(int isFinal) {
    this->isFinal = isFinal;
}

const string &Node::getName() const {
    return name;
}

void Node::setName(const string &name) {
    this->name = name;
}

int Node::isFinalState() const {
    return isFinal;
}

void Node::setIsFinal(int isFinal) {
    this->isFinal = isFinal;
}

vector<Edge *> Node::getEdges() const {
    return this->edges;
}

void Node::addEdge(Edge *edge) {
    this->edges.push_back(edge);
}

