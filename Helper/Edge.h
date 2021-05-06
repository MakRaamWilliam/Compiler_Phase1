#ifndef EDGE_H
#define EDGE_H

#include <iostream>
#include <bits/stdc++.h>
#include "Node.h"

#define EPS '\0'
using namespace std;

class Node;

class Edge {
public:
    Edge(Node *destination, char startAlphabet, char endAlphabet);

    virtual ~Edge();

public:
    Node *getDestination() const;

    void setDestination(Node *destination);

    char getStartAlphabet() const;

    void setStartAlphabet(char startAlphabet);

    char getEndAlphabet() const;

    void setEndAlphabet(char endAlphabet);

    int getSizeOfAlphabet() const;

    void setSizeOfAlphabet(int sizeOfAlphabet);

    const unordered_set<char> &getDisallowedAlphabet() const;

    void setDisallowedAlphabet(const unordered_set<char> &disallowedAlphabet);

    void addDisallowedSymbol(char symbol);

    bool isAcceptSymbol(char symbol);

    Node *doTransition(char symbol);

    bool isEPSTransition() const;

private:

    Node *destination;
    char startAlphabet;
    char endAlphabet;
    int sizeOfAlphabet;
    unordered_set<char> disallowedAlphabet;

};


#endif
