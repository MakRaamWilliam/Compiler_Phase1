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
