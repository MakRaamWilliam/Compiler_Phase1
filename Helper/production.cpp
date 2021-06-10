#include "production.h"

production::production(string val, productionType type) {
    this->value = val;
    this->type = type;
    this->eps = false;
}

void production::print() {
    for(int i=0;i<RHS.size();i++){
        for(int j=0;j<RHS[i].size();j++){
            cout<<RHS.at(i).at(j)->value<<"----";
        }
        cout <<endl;
    }
}

#include "production.h"
