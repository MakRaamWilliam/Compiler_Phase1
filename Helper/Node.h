#ifndef NODE_H
#define NODE_H

#include <iostream>
#include <bits/stdc++.h>
#include "Edge.h"

#define FINALSTATE true
using namespace std;

class Edge;

class Node {
public:
    Node(string name, int isend);

    explicit Node(int isend);

    virtual ~Node();

private:
    string name;
    int isend;
    vector<Edge *> edges;

public:
    int checkEndState() const;

    void setEndState(int isFinal);

    const string &getName() const;

    void setName(const string &name);

    vector<Edge *> getEdges() const;

    void addEdge(Edge *edge);

};


#endif
