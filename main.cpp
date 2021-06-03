#include <iostream>
#include "Helper/ReadRules.h"
#include "Helper/MakeGraph.h"
#include "Helper/NfaToDfa.h"
#include "Helper/Minimiztion.h"
#include "Helper/ReadProg.h"
#include "Helper/ReadGrammars.h"

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

void SetFirst(vector<production *> nonTerminal) {
    cout << "Firrrrst\n";
    for (auto it : nonTerminal) {
//        string value = it.first;
        cout<<it->value<<"\n";
        vector<vector<production *>> RHS = it->RHS;
        for (int i = 0; i < RHS.size(); i++) {
            stack<production *> st;
            st.push(RHS[i][0]);
            while (!st.empty()) {
                production *pr = st.top();
                st.pop();
                if (pr->type == terminal) {
                    it->first[pr->value] = RHS[i];
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

void SetFollow(vector<production *> nonTerminal){  // E  K  T  P  F
    int i=0;
    vector<production* >vec;
//    production *f=new production("$",terminal);
    for (auto it : nonTerminal){
        if(i++==0) {
            vec.push_back(it);
            it->follow["$"] = vec;
        }
        calcFollow(it,nonTerminal);
    }
}

void calcFollow(production *t, vector<production *> nonTerminal) {
    vector<production* >vec;
    for (auto it : t->appearance){
        for(int i=0;i<it->RHS.size();i++){
            for(int j=0;j<it->RHS[i].size();j++){
                if(t==it->RHS[i][j]){
                    if(j==it->RHS[i].size()-1){
                        // case 3
                        if(it->follow.empty()){
                            calcFollow(it,nonTerminal);
                        }
                        t->follow.insert(it->follow.begin(),it->follow.end());
                    }else{
                        if(it->RHS[i][j+1]->type==terminal){
                            t->follow.insert({it->RHS[i][j+1]->value,it->RHS[i]});
                        }else{
                            t->follow.insert(it->RHS[i][j+1]->first.begin(),it->RHS[i][j+1]->first.end());
                            if((j+1==it->RHS[i].size()-1)&&it->eps== true){
                                //special case 3
                                if(it->follow.empty()){
                                    calcFollow(it,nonTerminal);
                                }
                                t->follow.insert(it->follow.begin(),it->follow.end());
                            }
                        }
                        j++;
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
    vector<production *> m=ReadGrammars::getInstance()->ReadGrammarFile("grammar.txt");

    SetFirst(m);
    SetFollow(m);
    cout <<"-----------"<<endl;
    map<string, production *>::iterator it;

    for(auto it : m){
        cout<<"nonTerminal "<<it->value<<" has first :\n ";
        for(auto itr : it->first ){
            cout<<itr.first<<" map to: ";
            for(auto itr2 : itr.second){
                cout<<itr2->value;
            }cout<<"\n";
        }cout<<"\n";
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