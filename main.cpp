#include <iostream>
#include "Helper/ReadRules.h"
#include "Helper/MakeGraph.h"
#include "Helper/NfaToDfa.h"
#include "Helper/Minimiztion.h"
#include "Helper/ReadProg.h"
#include "Helper/ReadGrammars.h"
#include "Helper/ParserTable.h"
void calcFollow(production *pProduction, vector<production *> vector);

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



int main() {

//    DfaGraph* dfa= phaseOne();
//    ReadRules::getInstance()->ReadRuleFile("rules.txt", &mp_prio);

//    ReadGrammars *k=new ReadGrammars();
//    k->ReadGrammarFile("grammar.txt");
    vector<production *> m=ReadGrammars::getInstance()->ReadGrammarFile("grammar.txt");

     ParserTable *table = ParserTable::getInstance();
     table->SetFirst(m);
     table->SetFollow(m);
     map<pair<production *,string>,vector<production *>> symtable = table->getTable(m);

    cout <<"-----------"<<endl;
    cout <<"-----------"<<endl;

    map<string, production *>::iterator it;
    for(auto it : symtable){
        cout<<it.first.first->value << ": "<<it.first.second <<": ";
        for(auto itr : it.second ){
            cout<<itr->value;
        }cout<<"\n";
    }

    cout <<"-----------"<<endl;
    cout <<"-----------"<<endl;

    for(auto it : m){
        cout<<"nonTerminal "<<it->value<<" has PrFirst :\n ";
        for(auto itr : it->PrFirst ){
            cout<<itr.first<<" map to: ";
            for(auto itr2 : itr.second){
                cout<<itr2->value;
            }cout<<"\n";
        }cout<<" eps=" <<it->eps<<"\n";
    }

    for(auto it : m){
        cout<<"nonTerminal "<<it->value<<" has follow :\n ";
        for(auto itr : it->follow ){
            cout<<itr.first<<" map to: ";
            for(auto itr2 : itr.second){
                cout<<itr2->value;
            }cout<<"\n";
        }cout<<"\n";
    }



//    cout <<"-------************************----"<<endl;
//    int i=1;
//    for(auto it : m){
//        cout <<i++<<" - "<<it->temp<<endl;
//        cout <<it->value<<" == "<<it->value<<endl;
//        vector< vector< production *> > RHS=it->RHS;
//        cout <<"size = " <<RHS.size() <<endl;
//        for(int i=0;i<RHS.size();i++){
//            for(int j=0;j<RHS[i].size();j++){
//                cout<<RHS[i][j]->value<<"----";
//            }
//            cout <<endl;
//        }
//        cout <<"eps == "<<it->eps<<endl;
//        cout <<"-----------"<<endl;
//    }

//    cout <<"-------&&&&&&&&&&&&&&&&&&&&&&&&&*=------"<<endl;
//    for(auto it : m){
//        cout<<"nonTerminal "<<it->value<<" appeared in  :\n ";
//        for(auto itr : it->appearance ){
//            cout<<itr->value<<" ";
//        }cout<<"\n";
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
            cout <<token.PrFirst<<" --> "<<token.second << "\n";
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
//        cout <<token.PrFirst<<" --> "<<token.second << "\n";
//        opfile << token.second<<"\n";
//    }
//    opfile.close();
*/
    return 0;
}