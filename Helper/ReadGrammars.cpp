#include "ReadGrammars.h"



ReadGrammars *ReadGrammars::instance = nullptr;

ReadGrammars::ReadGrammars() {
    this->form = regex(R"((\w+) *= *((\S|\s)+))");
}

map<string, production *> ReadGrammars::ReadGrammarFile(const string &grammarfile) {
    std::ifstream file(grammarfile);
    std::string str;
    map<string, production *> nonterminals;
    map<string, production *> terminals;
    while (std::getline(file, str)) {
        if (regex_search(str, match, form)) {
//            cout << str <<endl;
            pair<string, vector<string>> temp;
            temp.first = match.str(1);
            string set_string = match.str(2);
            temp.first = removeSpaces(temp.first);

            production *t=findNonTerminal(temp.first,nonterminals);
            t->temp=str;


            split(set_string,t,nonterminals,terminals);
//            std::map<int, int> &temp_map

//            for(string s : t->RHS){
//                cout <<t->value<<"-->"<< s<<endl;
//            }
//            cout<<t->value<<" is eps ="<< t->eps<<endl;
//            cout<<endl;
//            rules.push_back(LexBulider::getInstance()->buildPost(temp, RegularDefinition));
        }

    }
    return nonterminals;
}
ReadGrammars *ReadGrammars::getInstance() {
    if (instance == nullptr) {
        instance = new ReadGrammars;
    }
    return instance;
}

string ReadGrammars::removeSpaces(string str) {
    str.erase(remove(str.begin(), str.end(), ' '), str.end());
    return str;
}

vector< vector< production *> >  ReadGrammars::split(const string &str,production *t,map<string, production *> &nonterminals,map<string, production *> &terminals) {
    vector< vector< production *> >  vec;
    vector<production* > tempVec;
    string ans;
    bool secondCout=false;
//    bool backSlash=false;
    for (auto i : str) {
        if (!ans.empty() && (i == '|' )) {
            tempVec.push_back(findNonTerminal(ans, nonterminals));
            t->RHS.push_back(tempVec);
            tempVec.clear();
            ans = "";
        }else if(ans.empty() && (i == ' ' )){continue;}
        else if(!ans.empty() && (i == ' ' )){
            tempVec.push_back(findNonTerminal(ans, nonterminals));
            ans = "";
        }else if (ans.empty() && (i == '|' )) {
            t->RHS.push_back(tempVec);
            tempVec.clear();
        }
        else if((i == '\'' )){
            if(secondCout==0){
                if(!ans.empty()){
                    tempVec.push_back(findNonTerminal(ans, nonterminals));
                    ans = "";
                }
            }else{
                if(!ans.empty()){
                    if(ans=="\\L"){
                        t->eps = true;
                        ans = "";
                    }else{
                        tempVec.push_back(findTerminal(ans, terminals));
                        ans = "";
                    }
                }
            }
            secondCout=1-secondCout;
        }
        else {
            ans += i;
        }
    }
    if (!ans.empty()) {
        tempVec.push_back(findNonTerminal(ans,nonterminals));
        t->RHS.push_back(tempVec);
        tempVec.clear();
    }
    if(!tempVec.empty())t->RHS.push_back(tempVec);

    return vec;
}

production* ReadGrammars::findNonTerminal(string name,map<string, production *> &nonterminals){
    production* t;
    name = removeSpaces(name);
    map<string, production *>::iterator it;
    it = nonterminals.find(name);
    if(it == nonterminals.end()) {
        t = new production(name, non_terminal);
//                size_t found = set_string.find("\\L");
//                if (found != string::npos)t->eps = true;
        nonterminals.insert({name, t});
    }else{
        t=it->second;
    }
    return t;
}
production* ReadGrammars::findTerminal(const string &name,map<string, production *> &terminals){
    production* t;
    map<string, production *>::iterator it;
    it = terminals.find(name);
    if(it == terminals.end()) {
        t = new production(name, terminal);
        terminals.insert({name, t});
    }else{
        t=it->second;
    }
    return t;
}