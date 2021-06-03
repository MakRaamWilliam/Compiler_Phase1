#include <iostream>
#include "Helper/ReadRules.h"
#include "Helper/MakeGraph.h"
#include "Helper/NfaToDfa.h"
#include "Helper/Minimiztion.h"
#include "Helper/ReadProg.h"
#include "Helper/ReadGrammars.h"

using namespace std;

DfaGraph* phaseOne(){
    // parsing file and build
    map<string, int> mp_prio{};
    vector<LexicalRule*>vec_rule = ReadRules::getInstance()->ReadRuleFile("rules.txt", &mp_prio);
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
    DfaGraph* dfa = NfaToDfa::getInstance()->Convert(nfa, MakeGraph::getInstance()->getAlphabet());
    map<Node *, map<char, Node *>> op = dfa->getDTable();


    //minimize dfa
    Minimiztion::getInstance()->partts.clear();
    Minimiztion::getInstance()->dfaStates = dfa->getDTable();
    vector<Node *> endState;
    vector<Node *> nonendState;
    map<Node *, map<char, Node *>>::iterator itr;
    for (itr = Minimiztion::getInstance()->dfaStates.begin(); itr != Minimiztion::getInstance()->dfaStates.end(); itr++) {
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

void SetFirst(map<string,production *> nonTerminal) {
    cout << "Firrrrst\n";
    for (auto it : nonTerminal) {
        string value = it.first;
        cout<<value<<"\n";
        vector<vector<production *>> RHS = it.second->RHS;
        for (int i = 0; i < RHS.size(); i++) {
            stack<production *> st;
            st.push(RHS[i][0]);
            while (!st.empty()) {
                production *pr = st.top();
                st.pop();
                if (pr->type == terminal) {
                    it.second->first[pr->value] = RHS[i];
                    cout<<pr->value <<"  "<<RHS[i][0]->value<<"\n";
                } else {
                    for (int k = 0; k < pr->RHS.size(); k++) {
                        st.push(pr->RHS[k][0]);
                    }
                }
            }
        }
    }
}
int main() {

//    DfaGraph* dfa= phaseOne();
//    ReadRules::getInstance()->ReadRuleFile("rules.txt", &mp_prio);

//    ReadGrammars *k=new ReadGrammars();
//    k->ReadGrammarFile("grammar.txt");
    map<string, production *> m=ReadGrammars::getInstance()->ReadGrammarFile("grammar.txt");

    SetFirst(m);

    cout <<"-----------"<<endl;
    map<string, production *>::iterator it;
    int i=1;
    for(it=m.begin();it!=m.end();it++){
        cout<<"nonTerminal "<<it->first<<" has first :\n ";
        for(auto itr : it->second->first ){
            cout<<itr.first<<" map to: ";
            for(auto itr2 : itr.second){
                cout<<itr2->value;
            }cout<<"\n";
        }cout<<"\n";
    }


//    for(it=m.begin();it!=m.end();it++){
//        cout <<i++<<" - "<<it->second->temp<<endl;
//        cout <<it->first<<" == "<<it->second->value<<endl;
//        vector< vector< production *> > RHS=it->second->RHS;
//        cout <<"size = " <<RHS.size() <<endl;
//        for(int i=0;i<RHS.size();i++){
//            for(int j=0;j<RHS[i].size();j++){
//                cout<<RHS[i][j]->value<<"----";
//            }
//            cout <<endl;
//        }
//        cout <<"eps == "<<it->second->eps<<endl;
//        cout <<"-----------"<<endl;
//    }


    //read the test program
/*    ReadProg *read=ReadProg::getInstance();
    const string word;
//    fstream file=read->openFile("TestProgram.txt");
    fstream file;
    string fileName="TestProgram.txt";
    file.open(fileName.c_str());
    vector< pair<string, string>> *tokens = read->ReadProgFile(file, word, dfa);
    ofstream opfile;
    opfile.open("output.txt");
    while(tokens!=NULL){
        for(const pair<string, string>&token : *tokens){
            cout <<token.first<<" --> "<<token.second << "\n";
            opfile << token.second<<"\n";
        }
        tokens = read->ReadProgFile(file, word, dfa);
    }
    opfile.close();
    file.close();
    //print the output file
//    ofstream opfile;
//    opfile.open("output.txt");
//    for(const pair<string, string>&token : token){
//        cout <<token.first<<" --> "<<token.second << "\n";
//        opfile << token.second<<"\n";
//    }
//    opfile.close();
*/
    return 0;
}