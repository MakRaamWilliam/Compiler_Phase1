#include "Minimiztion.h"
#include <map>
#include <string>
#include <algorithm>

Minimiztion *Minimiztion::instance = nullptr;


vector<vector<Node *>> Minimiztion::Minimize(const vector<vector<Node *>> &parrts) {

    vector<vector<Node *>> res;

    for (vector<Node *> p:parrts) {
        if (p.size() > 1) {
            for (int i = 0; i < p.size(); i++) {
                if (HaveState(res, p.at(i))) {
                    continue;
                }
                vector<Node *> temp;
                temp.push_back(p.at(i));

                for (int j = i + 1; j < p.size(); j++) {
                    Node *s1 = p.at(i);
                    Node *s2 = p.at(j);

                    if ((!compState(parrts, s1, s2)) && dfaStates.find(s1) != dfaStates.end() &&
                        dfaStates.find(s2) != dfaStates.end()) {

                        if (dfaStates.at(s1) == dfaStates.at(s2)) {
                            if (!s1->checkEndState()) {
                                temp.push_back(s2);
                            } else if (s1->getName() == s2->getName()) {
                                temp.push_back(s2);
                            }
                        }
                    }
                }
                res.push_back(temp);
                updateTable(temp);
            }
        } else {
            res.push_back(p);
        }
    }
    if (parrts.size() == res.size()) {
        return res;
    }

    return Minimize(res);
}

void Minimiztion::updateTable(vector<Node *> temp) {
    if (temp.size() > 1) {
        Node *state = temp.at(0);
        for (int i = 1; i < temp.size(); i++) {
            dfaStates.erase(temp.at(i));
        }
        for (pair<Node *, map<char, Node *>> row:dfaStates) {
            for (pair<char, Node *> c:row.second) {
                for (int i = 1; i < temp.size(); i++) {
                    if (temp.at(i) == c.second) {
                        dfaStates.at(row.first).at(c.first) = state;
                    }
                }
            }
        }
    }
}


bool Minimiztion::compState(const vector<vector<Node *>> &partitions, Node *state1, Node *state2) {
    for (const vector<Node *> &p:partitions) {

        if (!HaveEqualstate(partitions, state1, state2)) {
            return true;
        }
    }
    return false;
}

bool Minimiztion::HaveEqualstate(const vector<vector<Node *>> &partts, Node *state1, Node *state2) {

    for (vector<Node *> p:partts) {
        if ((std::find(p.begin(), p.end(), state1) != p.end()) && (std::find(p.begin(), p.end(), state2) != p.end())) {
            return true;
        }
    }
    return false;
}

bool Minimiztion::HaveState(const vector<vector<Node *>> &partts, Node *state) {

    for (const vector<Node *> &p:partts) {
        for (Node *N:p) {
            if (N == state) {
                return true;
            }
        }
    }
    return false;
}

Minimiztion *Minimiztion::getInstance() {
    if (instance == nullptr) {
        instance = new Minimiztion();
    }
    return instance;
}
