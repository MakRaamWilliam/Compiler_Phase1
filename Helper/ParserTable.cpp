#include "ParserTable.h"
ParserTable *ParserTable::instance = nullptr;

ParserTable::ParserTable() {

}

ParserTable *ParserTable::getInstance() {
    if (instance == nullptr) {
        instance = new ParserTable;
    }
    return instance;
}
void ParserTable::SetFirst(vector<production *> nonTerminal) {
    cout << "Firrrrst\n";
    for (auto it : nonTerminal) {
//        string value = it.PrFirst;
        cout<<it->value<<"\n";
        vector<vector<production *>> RHS = it->RHS;
        for (int i = 0; i < RHS.size(); i++) {
            stack<production *> st;
            st.push(RHS[i][0]);
            while (!st.empty()) {
                production *pr = st.top();
                st.pop();
                if (pr->type == terminal) {
                    it->PrFirst[pr->value] = RHS[i];
                    cout<<pr->value <<"  "<<RHS[i][0]->value<<"\n";
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
//                                if(it->follow.empty()){
//                                    calcFollow(it,nonTerminal);
//                                }
//                                t->follow.insert(it->follow.begin(),it->follow.end());

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
    syncVec.push_back(new production("Sync",non_terminal));
    vector<production * > epsVec;
    epsVec.push_back(new production("eps",non_terminal));
    for(auto it : nonTerminal){
        cout<<"nonTerminal "<<it->value<<" has PrFirst :\n ";
        for(auto itr : it->PrFirst ){
            cout<<itr.first<<" map to: ";
            table[make_pair(it,itr.first)]=itr.second;
        }
        for(auto itr : it->follow){
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

