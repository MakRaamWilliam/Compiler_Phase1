#include "NfaToDfa.h"

NfaToDfa *NfaToDfa::instance = nullptr;


NfaToDfa *NfaToDfa::getInstance() {
    if (instance == nullptr) {
        instance = new NfaToDfa();
    }
    return instance;
}

DfaGraph *NfaToDfa::Convert(NfaGraph *Nfa, const set<char> &alpha) {
    set<Node *> nfaState;
    map<set<Node *>, Node *> ndStates;
    map<Node *, bool> mark;
    map<Node *, map<char, Node *>> Dtable;
    int i = 0;
    nfaState.insert(Nfa->getStart());
    nfaState = closure(nfaState);
    Node *dfaState = new Node("A", 0);
    dfaState->setEndState(0);
    for (auto f:Nfa->getendState()) {
        if (nfaState.find(f) != nfaState.end() && (f->checkEndState() > dfaState->checkEndState())) {
            dfaState->setEndState(f->checkEndState());
            dfaState->setName(f->getName());
        }
    }
    Node *startState = dfaState;
    ndStates.insert(pair<set<Node *>, Node *>(nfaState, dfaState));
    mark.insert(pair<Node *, bool>(dfaState, false));
    int flag = 0;
    int bsize;
    do {
        bsize = ndStates.size();
        flag = 0;
        for (const auto &itr:ndStates)
        {
            nfaState = itr.first;
            dfaState = itr.second;
            if (!mark.find(dfaState)->second) {
                flag--;
                if (mark.find(dfaState) != mark.end()) {
                    mark.find(dfaState)->second = true;
                }
                auto *drow = new map<char, Node *>();
                drow->clear();
                map<char, Node *>::iterator it2;
                for (auto c:alpha)
                {
                    drow->insert(pair<char, Node *>(c, nullNode));
                    if (Change(nfaState, c).empty()) {
                        continue;
                    }
                    set<Node *> u = closure(Change(nfaState, c));
                    bool found = false;
                    for (const auto &itr2:ndStates) {
                        if (CompSets(u, itr2.first)) {
                            if (drow->find(c) != drow->end()) {
                                drow->find(c)->second = itr2.second;
                            }
                            Edge *nedge = new Edge(itr2.second, c, c);
                            dfaState->addEdge(nedge);
                            found = true;
                            break;
                        }
                    }
                    if (!found) {
                        i++;
                        std::string s(1, 'A' + i);
                        Node *d = new Node(s, false);
                        d->setName(s);
                        if (drow->find(c) != drow->end()) {
                            drow->find(c)->second = d;
                        }
                        Edge *nedge = new Edge(d, c, c);
                        dfaState->addEdge(nedge);
                        ndStates.insert(pair<set<Node *>, Node *>(u, d));
                        mark.insert(pair<Node *, bool>(d, false));
                    }
                }
                Dtable.insert(pair<Node *, map<char, Node *>>(dfaState, *drow));
            }
            for (auto f:Nfa->getendState()) {
                if (nfaState.find(f) != nfaState.end() && (f->checkEndState() > dfaState->checkEndState())) {
                    dfaState->setEndState(f->checkEndState());
                    dfaState->setName(f->getName());
                }
            }
        }
    } while (flag != 0 || bsize != ndStates.size());

    return new DfaGraph(startState, Dtable);
}

set<Node *> NfaToDfa::closure(set<Node *> nodes) {
    int i = 0;
    set<Node *>::iterator itr;
    while (nodes.size() != i) {
        i = 0;
        for (itr = nodes.begin(); itr != nodes.end(); itr++)
        {
            i++;
            vector<Edge *> edges = (*itr)->getEdges();
            Edge *x;
            for (auto &edge : edges)
            {
                x = edge;
                if (x->isEpsTrans()) {
                    nodes.insert(x->getDestination());
                }

            }
        }
    }
    return nodes;
}


set<Node *> NfaToDfa::Change(const set<Node *> &nodes, char symbol) {
    set<Node *>::iterator itr;
    set<Node *> res;
    for (itr = nodes.begin(); itr != nodes.end(); itr++)
    {
        vector<Edge *> edges = (*itr)->getEdges();
        Edge *x;
        for (auto &edge : edges)
        {
            x = edge;
            if (x->isAccSymb(symbol)) {
                res.insert(x->maketrans(symbol));
            }
        }
    }
    return res;
}

bool NfaToDfa::CompSets(const set<Node *> &x, set<Node *> y) {
    if (x.size() != y.size()) {
        return false;
    }
    int size = x.size();
    for (auto i:x) {
        y.insert(i);
    }
    return y.size() == size;
}