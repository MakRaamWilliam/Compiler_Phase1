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
    Edge(Node *des, char startAlpha, char endAlpha);

    virtual ~Edge();

public:
    Node *getDestination() const;

    bool isAccSymb(char symb);

    Node *maketrans(char symb);

    bool isEpsTrans() const;

private:
    char startAlpha;
    char endAlpha;
    Node *des;
    int sizeAlpha;
    unordered_set<char> notallow;

};


#endif
