#include "Edge.h"

Edge::Edge(Node *des, char startAlpha, char endAlpha) {
    this->des = des;
    this->startAlpha = startAlpha;
    this->endAlpha = endAlpha;
    this->sizeAlpha = endAlpha - startAlpha + 1;
}

Edge::~Edge() {

    free(this->des);
    this->notallow.clear();
}

Node *Edge::getDestination() const {
    return des;
}


bool Edge::isAccSymb(const char symb) {

    if (this->notallow.find(symb) != this->notallow.end()) {
        return false;
    }
    return symb >= this->startAlpha && symb <= this->endAlpha;
}

Node *Edge::maketrans(const char symb) {

    if (this->isAccSymb(symb)) {
        return this->des;
    }
    return nullptr;
}

bool Edge::isEpsTrans() const {
    return this->startAlpha == EPS && this->endAlpha == EPS;
}
