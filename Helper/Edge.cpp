#include "Edge.h"

Edge::Edge(Node *destination, char startAlphabet, char endAlphabet) {
    this->destination = destination;
    this->startAlphabet = startAlphabet;
    this->endAlphabet = endAlphabet;
    this->sizeOfAlphabet = endAlphabet - startAlphabet + 1;
}

Edge::~Edge() {

    free(this->destination);
    this->disallowedAlphabet.clear();
}

Node *Edge::getDestination() const {
    return destination;
}


bool Edge::isAcceptSymbol(const char symbol) {

    if (this->disallowedAlphabet.find(symbol) != this->disallowedAlphabet.end()) {
        return false;
    }
    return symbol >= this->startAlphabet && symbol <= this->endAlphabet;
}

Node *Edge::doTransition(const char symbol) {

    if (this->isAcceptSymbol(symbol)) {
        return this->destination;
    }
    return nullptr;
}

bool Edge::isEPSTransition() const {
    return this->startAlphabet == EPS && this->endAlphabet == EPS;
}
