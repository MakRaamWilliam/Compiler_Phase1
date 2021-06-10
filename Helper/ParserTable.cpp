#include "ParserTable.h"
ParserTable *ParserTable::instance = nullptr;

ParserTable::ParserTable() {
   Ambiguity = false;
}

ParserTable *ParserTable::getInstance() {
    if (instance == nullptr) {
        instance = new ParserTable;
    }
    return instance;
}
void ParserTable::SetFirst(vector<production *> nonTerminal) {
    for (auto it : nonTerminal) {
//        string value = it.PrFirst;
        // cout<<it->value<<"\n";
        vector<vector<production *>> RHS = it->RHS;
        for (int i = 0; i < RHS.size(); i++) {
            stack<production *> st;
            st.push(RHS[i][0]);
            while (!st.empty()) {
                production *pr = st.top();
                st.pop();
                if (pr->type == terminal) {
                    it->PrFirst[pr->value] = RHS[i];
                    // cout<<pr->value <<"  "<<RHS[i][0]->value<<"\n";
                } else {
                    for (int k = 0; k < pr->RHS.size(); k++) {
                        st.push(pr->RHS[k][0]);
                        it->eps = it->eps || pr->eps;
                    }
                }
            }
        }
    }
}
void ParserTable::calcFollow(production *t, vector<production *> nonTerminal) {
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
//                            t->follow.insert(it->RHS[i][j+1]->PrFirst.begin(),it->RHS[i][j+1]->PrFirst.end());
//                            if((j+1==it->RHS[i].size()-1)&&it->RHS[i][j+1]->eps== true){
                            int k=j+1;
                            for(;k<it->RHS[i].size();k++){
                                //special case 3
                                if(it->RHS[i][k]->type==terminal){
                                    t->follow.insert({it->RHS[i][k]->value,it->RHS[i]});
                                    break;
                                }else{
                                    t->follow.insert(it->RHS[i][k]->PrFirst.begin(), it->RHS[i][k]->PrFirst.end());
                                    if(it->RHS[i][k]->eps== false)break;
                                }

                            }
                            if((k-1==it->RHS[i].size()-1)&&it->RHS[i][k-1]->eps== true){
                                if(it->RHS[i][k-1]->follow.empty()){
                                    calcFollow(it->RHS[i][k-1],nonTerminal);
                                }
                                t->follow.insert(it->RHS[i][k-1]->follow.begin(),it->RHS[i][k-1]->follow.end());
                            }
                        }

                    }
                }
            }
        }
    }

}

void ParserTable::SetFollow(vector<production *> nonTerminal){  // E  K  T  P  F
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

map<pair<production *,  string>, vector<production *>> ParserTable::getTable(vector<production *> nonTerminal) {
    vector<production * > syncVec;
    syncVec.push_back(new production("Sync",terminal));
    vector<production * > epsVec;
    epsVec.push_back(new production("eps",terminal));
    for(auto it : nonTerminal){
        //   cout<<"nonTerminal "<<it->value<<" has PrFirst :\n ";
        for(auto itr : it->PrFirst ){
            //  cout<<itr.first<<" map to: ";
            terminalSet.insert(itr.first);
            table[make_pair(it,itr.first)]=itr.second;
        }
        for(auto itr : it->follow){
            terminalSet.insert(itr.first);
            if(table.find(make_pair(it,itr.first)) != table.end() && it->eps ){
                Ambiguity = true;
            }
            else if(it->eps){
                table[make_pair(it,itr.first)]= epsVec;
            } else if (table.find(make_pair(it,itr.first)) == table.end()){
                table[make_pair(it,itr.first)]= syncVec;
            }
        }
    }
    return table;
}

void ParserTable::printTable(vector<production *> nonTerminal) {
    ofstream of;
    of.open(  "ParserTable.trnstb");
    streambuf *buf = of.rdbuf();
    std::ostream stream(buf);
    stream << left << setw(60) << "NonTerminal/Terminal";
    for (string str : terminalSet ) {
        stream << setw(60) << str;
    }
    stream << "\n";
    for (auto it : nonTerminal){

        stream << left << setw(60) << it->value;
        for (string str : terminalSet ) {
            if(table.find(make_pair(it,str)) != table.end()) {
                string tm= "";
                for(auto it2 : table[make_pair(it, str)] ){
                    tm+=it2->value + " ";
                }
                stream << setw(60) << tm;
            }
            else
                stream << setw(60) << "Error";
        }
        stream << endl;
    }

}


void ParserTable::getOutput(DfaGraph *dfa, production *start,ifstream &file) {
    stack<production *> stack;
    vector<string> opstack;
    stack.push(new production("$",terminal) );
    stack.push(start);
    opstack.push_back(start->value);
    ReadProg *input= ReadProg::getInstance(dfa);
    ofstream opfile;
    opfile.open("output2.txt");
    bool newOne=true;
    string currstr;
    while (!stack.empty()){
        for(auto it : opstack){
            opfile << it <<" ";
        }opfile<<"\n";

        production *currpr = stack.top();

        if(newOne) {
            currstr = input->ReadWord(file);
            if(currstr=="")currstr="$";
            newOne=false;
        }
        if(currpr->type == terminal && currpr->value == currstr){
            // opfile << "match: " << currstr <<"\n";
            cout << "match: " << currstr <<"\n";
//            ip.pop();
            newOne=true;
            stack.pop();
            if(!opstack.empty())
                opstack.pop_back();
        }else if(currpr->type == terminal){
            //opfile << "Error from terminal "<<currpr->value<<" " <<  currstr<<"\n";
            cout << "Error from terminal "<< currstr <<" "<<currpr->value<<"\n";
            stack.pop();
            opstack.pop_back();
        }else if(currpr->type == non_terminal){
            if(table.find(make_pair(currpr,currstr)) != table.end() ){
                vector<production *> vec = table[make_pair(currpr,currstr)];
                if(vec[0]->value == "Sync" && vec[0]->type == terminal ){
                    cout <<"Error from Sync "<<currpr->value <<" "<<currstr<<"\n";
                    stack.pop();
                    opstack.pop_back();
                } else{
                    stack.pop();
                    opstack.pop_back();
                    // opfile <<currpr->value << "-->" ;
                    cout <<currpr->value << "-->" ;
                    for(auto it: vec ){
                        // opfile << it->value <<" ";
                        cout << it->value <<" ";
                    }cout<<"\n";
                    reverse(vec.begin(),vec.end());
                    for(auto it: vec ){
                        if(it->value != "eps" && it->value != "Sync") {
                            stack.push(it);
                            opstack.push_back(it->value);
                        }
                    }
                }
            } else{
                cout <<"Error empty " << currstr <<" "<<currpr->value<<"\n";
//                ip.pop();
                newOne=true;
            }
        }
    }
}
bool ParserTable::isAmbiguity() {
    return Ambiguity;
}