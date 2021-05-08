#include "Minimiztion.h"
#include <map>
#include <string>
#include <algorithm>

Minimiztion *Minimiztion::instance = nullptr;

// minimizer function
// void Minimiztion::DFAMinimize(DfaGraph *dfa) {

//     this->partitions.clear();
//     // get dfa before minimizing
//     DFAStates = dfa->getDTable();
//     vector<Node *> FinalStates;
//     vector<Node *> NonFinalStates;
//     map<Node *, map<char, Node *>>::iterator itr;
//     for (itr = DFAStates.begin(); itr != DFAStates.end(); itr++) {
//         if (itr->first->isFinalState()) {
//             FinalStates.push_back(itr->first);
//         } else {
//             NonFinalStates.push_back(itr->first);
//         }
//     }

//     // the final and non final put them in queue of vector of nodes
//     partitions.push_back(NonFinalStates);
//     partitions.push_back(FinalStates);

//     // minimize the table
//     Minimize(partitions);
//     dfa->setDTable(DFAStates);
// }

/*
 * minimize the results
 */
vector<vector<Node *>> Minimiztion::Minimize(const vector<vector<Node *>> &partitions) {

    vector<vector<Node *>> res;

    for (vector<Node *> p:partitions) {
        if (p.size() > 1) {
            for (int i = 0; i < p.size(); i++) {

                // if already in partition
                if (containState(res, p.at(i))) {
                    continue;
                }
                vector<Node *> temp;
                temp.push_back(p.at(i));

                for (int j = i + 1; j < p.size(); j++) {
                    Node *s1 = p.at(i);
                    Node *s2 = p.at(j);

                    if ((!areStatesUnique(partitions, s1, s2)) && DFAStates.find(s1) != DFAStates.end() &&
                        DFAStates.find(s2) != DFAStates.end()) {

                        if (DFAStates.at(s1) == DFAStates.at(s2)) {
                            if (!s1->isFinalState()) {
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
            // when group contain one state only
            res.push_back(p);
        }
    }
    // if already minimized
    if (partitions.size() == res.size()) {
        return res;
    }

    return Minimize(res);
}

/*
 * update table of the DFAStates
 */
void Minimiztion::updateTable(vector<Node *> temp) {
    if (temp.size() > 1) {
        Node *state = temp.at(0);
        for (int i = 1; i < temp.size(); i++) {
            DFAStates.erase(temp.at(i));
        }
        for (pair<Node *, map<char, Node *>> row:DFAStates) {
            for (pair<char, Node *> c:row.second) {
                for (int i = 1; i < temp.size(); i++) {
                    if (temp.at(i) == c.second) {
                        DFAStates.at(row.first).at(c.first) = state;
                    }
                }
            }
        }
    }
}

/*
 * return true if two states are unique
 */
bool Minimiztion::areStatesUnique(const vector<vector<Node *>> &partitions, Node *state1, Node *state2) {
    for (const vector<Node *> &p:partitions) {

        if (!containedBySamePartition(partitions, state1, state2)) {
            return true;
        }
    }
    return false;
}

/*
 * return true if two states are in the same partition
 */
bool Minimiztion::containedBySamePartition(const vector<vector<Node *>> &partitions, Node *State1, Node *State2) {

    for (vector<Node *> p:partitions) {
        if ((std::find(p.begin(), p.end(), State1) != p.end()) && (std::find(p.begin(), p.end(), State2) != p.end())) {
            return true;
        }
    }
    return false;
}

/*
 * return true if partition contain state
 */
bool Minimiztion::containState(const vector<vector<Node *>> &partitions, Node *state) {

    for (const vector<Node *> &p:partitions) {
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
