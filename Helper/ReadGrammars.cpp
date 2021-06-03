#include "ReadGrammars.h"



ReadGrammars *ReadGrammars::instance = nullptr;

ReadGrammars::ReadGrammars() {
    this->form = regex(R"((\w+) *= *((\S|\s)+))");
}

vector<production *> ReadGrammars::ReadGrammarFile(const string &grammarfile) {
    std::ifstream file(grammarfile);
    std::string str;
    map<string, production *> nonterminals;
    map<string, production *> terminals;
    vector<production *> vec;
    while (std::getline(file, str)) {
        if (regex_search(str, match, form)) {
            pair<string, vector<string>> temp;
            temp.first = match.str(1);
            string set_string = match.str(2);
            temp.first = removeSpaces(temp.first);

            production *t= findNonTerminalLHS(temp.first, nonterminals);
            t->temp=str;


            split(set_string,t,nonterminals,terminals);
            vec.push_back(t);
        }

    }
    return vec;
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
            tempVec.push_back(findNonTerminalRHS(ans, nonterminals, t));
            t->RHS.push_back(tempVec);
            tempVec.clear();
            ans = "";
        }else if(ans.empty() && (i == ' ' )){continue;}
        else if(!ans.empty() && (i == ' ' )){
            tempVec.push_back(findNonTerminalRHS(ans, nonterminals, t));
            ans = "";
        }else if (ans.empty() && (i == '|' )) {
            t->RHS.push_back(tempVec);
            tempVec.clear();
        }
        else if((i == '\'' )){
            if(secondCout==0){
                if(!ans.empty()){
                    tempVec.push_back(findNonTerminalRHS(ans, nonterminals, t));
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
        tempVec.push_back(findNonTerminalRHS(ans, nonterminals, t));
        t->RHS.push_back(tempVec);
        tempVec.clear();
    }
    if(!tempVec.empty())t->RHS.push_back(tempVec);

    return vec;
}

production* ReadGrammars::findNonTerminalRHS(string name, map<string, production *> &nonterminals, production *t){
    production* wanted;
    name = removeSpaces(name);
    map<string, production *>::iterator it;
    it = nonterminals.find(name);
    if(it == nonterminals.end()) {
        wanted = new production(name, non_terminal);

        nonterminals.insert({name, wanted});
    }else{
        wanted=it->second;
    }
    wanted->appearance.push_back(t);
    return wanted;
}

production* ReadGrammars::findNonTerminalLHS(string name, map<string, production *> &nonterminals){
    production* t;
    name = removeSpaces(name);
    map<string, production *>::iterator it;
    it = nonterminals.find(name);
    if(it == nonterminals.end()) {
        t = new production(name, non_terminal);

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