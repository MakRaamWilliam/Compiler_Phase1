#include "production.h"

production::production(string val,productionType type){
    this->value=val;
    this->type=type;
    this->eps=false;
}
void production::print() {
//    for(int i=0;i<RHS->size();i++){
//        for(int j=0;j<RHS[i].size();j++){
//            cout<<RHS->at(i)->at(j)->value<<"----";
//        }
//        cout <<endl;
//    }
}
//void production::SetFirst(map<string,production *> nonTerminal){
//    cout<<"Firrrrst\n";
//    for (auto it : nonTerminal)
//    {
//        string value = it.first;
//        vector<vector<production*>> RHS = it.second->RHS;
//        for(int i =0;i<RHS.size();i++){
//            stack<production*> st;
//            st.push(RHS[i][0]);
//            while(!st.empty()){
//                production *pr = st.top();
//                st.pop();
//                if(pr->type == terminal){
//                    first[pr->value] = RHS[i];
//                }
//                else{
//                    for(int k=0;k<pr->RHS.size();k++){
//                        st.push(pr->RHS[k][0]);
//                    }
//                }
//            }
//        }
//    }
//}
#include "production.h"