#include <iostream>
#include <fstream>
#include "Helper/ReadRules.h"
#include "Helper/MakeGraph.h"
#include "Helper/NfaToDfa.h"
#include "Helper/Minimiztion.h"

#include "Helper/ReadGrammars.h"
#include "Helper/ParserTable.h"

void calcFollow(production *pProduction, vector<production *> vector);

using namespace std;

DfaGraph * phaseOne() {
    // parsing file and build
    map<string, int> mp_prio{};
    vector<LexicalRule *> vec_rule = ReadRules::getInstance()->ReadRuleFile("rules.txt", &mp_prio);
    // NfaGraph* nfa = MakeGraph::getInstance()->buildNFAFromLexicalRules(vec_rule, mp_prio);
    vector<NfaGraph *> startsNodes;
    for (LexicalRule *rule:vec_rule) {
        if (rule->getType() != RegularDefinition) {
            NfaGraph *a = MakeGraph::getInstance()->makeLexRule(rule, mp_prio);
            startsNodes.push_back(a);
        }
    }
    NfaGraph *nfa = MakeGraph::getInstance()->makeComRecongz(startsNodes);


    //Convert  from nfa to dfa
    DfaGraph *dfa = NfaToDfa::getInstance()->Convert(nfa, MakeGraph::getInstance()->getAlphabet());
    map<Node *, map<char, Node *>> op = dfa->getDTable();


    //minimize dfa
    Minimiztion::getInstance()->partts.clear();
    Minimiztion::getInstance()->dfaStates = dfa->getDTable();
    vector<Node *> endState;
    vector<Node *> nonendState;
    map<Node *, map<char, Node *>>::iterator itr;
    for (itr = Minimiztion::getInstance()->dfaStates.begin();
         itr != Minimiztion::getInstance()->dfaStates.end(); itr++) {
        if (itr->first->checkEndState()) {
            endState.push_back(itr->first);
        } else {
            nonendState.push_back(itr->first);
        }
    }
    Minimiztion::getInstance()->partts.push_back(nonendState);
    Minimiztion::getInstance()->partts.push_back(endState);
    Minimiztion::getInstance()->Minimize(Minimiztion::getInstance()->partts);
    dfa->setDTable(Minimiztion::getInstance()->dfaStates);

    //make trans table
    op = dfa->getDTable();
    ReadRules::getInstance()->makeTransTable("TransTable", op, MakeGraph::getInstance()->getAlphabet());

    return dfa;
}


int main() {

    DfaGraph *dfa=phaseOne();
    cout << "----------------------\n";
    cout << "----------------------\n";

    vector<production *> m = ReadGrammars::getInstance()->ReadGrammarFile("grammar.txt");

    ParserTable *table = ParserTable::getInstance();
    table->SetFirst(m);
    table->SetFollow(m);
    map<pair < production * , string>, vector<production *>>
    symtable = table->getTable(m);
    table->printTable(m);
    cout << "----------------------\n";
    cout << "----------------------\n";

    map<string, production *>::iterator it;
    for (auto it : symtable) {
        cout << it.first.first->value << ": " << it.first.second << ": ";
        for (auto itr : it.second) {
            cout << itr->value;
        }
        cout << "\n";
    }
    cout << "----------------------\n";
    cout << "----------------------\n";
    if (table->isAmbiguity()) {
        cout << "Ambiguous Grammar\n";
    } else {
        ifstream file("TestProgram.txt");
        table->getOutput(dfa, m[0],file);
        file.close();
    }

    return 0;
}