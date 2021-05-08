#include <iostream>
#include "Helper/ReadRules.h"
#include "Helper/MakeGraph.h"
#include "Helper/NfaToDfa.h"
#include "Helper/Minimiztion.h"
#include "Helper/ReadProg.h"
using namespace std;

int main() {

    // parsing file and build
    map<string, int> mp_prio{};

    vector<LexicalRule*>vec_rule = ReadRules::getInstance()->read_from_file("rules.txt", &mp_prio);

    vector<NfaGraph *> startsNodes;
    for (LexicalRule *rule:vec_rule) {
        if (rule->getType() != RegularDefinition) {
            NfaGraph *a = MakeGraph::getInstance()->makeLexRule(rule, mp_prio);
            startsNodes.push_back(a);
        }
    }
    NfaGraph *nfa = MakeGraph::getInstance()->makeComRecongz(startsNodes);


    //convert  from nfa to dfa
    DfaGraph* dfa = NfaToDfa::getInstance()->convert(nfa, MakeGraph::getInstance()->getAlphabet());
    map<Node *, map<char, Node *>> op = dfa->getDTable();


    //minimize dfa
    Minimiztion::getInstance()->partitions.clear();
    Minimiztion::getInstance()->DFAStates = dfa->getDTable();
    vector<Node *> endState;
    vector<Node *> nonendState;
    map<Node *, map<char, Node *>>::iterator itr;
    for (itr = Minimiztion::getInstance()->DFAStates.begin(); itr != Minimiztion::getInstance()->DFAStates.end(); itr++) {
        if (itr->first->isFinalState()) {
            endState.push_back(itr->first);
        } else {
            nonendState.push_back(itr->first);
        }
    }
    Minimiztion::getInstance()->partitions.push_back(nonendState);
    Minimiztion::getInstance()->partitions.push_back(endState);
    Minimiztion::getInstance()->Minimize(Minimiztion::getInstance()->partitions);
    dfa->setDTable(Minimiztion::getInstance()->DFAStates);

    //print table
    op = dfa->getDTable();
    ReadRules::getInstance()->printTable("table", op, MakeGraph::getInstance()->getAlphabet());

    //read the test program
    vector<pair<string, string>> tokens = ReadProg::getInstance()->scanProgramFile("test.txt",  dfa);
    
    //print the output file
    for(const pair<string, string>&token : tokens){
        cout << token.first  <<" "<<token.second << "\n";
    }

    return 0;
}
