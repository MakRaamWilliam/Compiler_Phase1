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

void Edge::setDestination(Node *destination) {
    Edge::destination = destination;
}

char Edge::getStartAlphabet() const {
    return startAlphabet;
}

void Edge::setStartAlphabet(char startAlphabet) {
    Edge::startAlphabet = startAlphabet;
}

char Edge::getEndAlphabet() const {
    return this->endAlphabet;
}

void Edge::setEndAlphabet(char endAlphabet) {
    Edge::endAlphabet = endAlphabet;
}

int Edge::getSizeOfAlphabet() const {
    return sizeOfAlphabet;
}

void Edge::setSizeOfAlphabet(int sizeOfAlphabet) {
    Edge::sizeOfAlphabet = sizeOfAlphabet;
}

const unordered_set<char> &Edge::getDisallowedAlphabet() const {
    return disallowedAlphabet;
}

void Edge::setDisallowedAlphabet(const unordered_set<char> &disallowedAlphabet) {
    Edge::disallowedAlphabet = disallowedAlphabet;
}

void Edge::addDisallowedSymbol(const char symbol) {
    this->disallowedAlphabet.insert(symbol);
    if (symbol >= this->startAlphabet && symbol <= this->endAlphabet) {
        this->sizeOfAlphabet--;
    }
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
