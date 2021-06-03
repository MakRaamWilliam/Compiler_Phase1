#include "ReadGrammars.h"



ReadGrammars *ReadGrammars::instance = nullptr;

ReadGrammars::ReadGrammars() {
    this->form = regex(R"((\w+) *= *((\S|\s)+))");
}

void ReadGrammars::ReadGrammarFile(const string &grammarfile) {
    std::ifstream file(grammarfile);
    std::string str;
    map<string, production *> nonterminals;
    map<string, production *> terminals;
    while (std::getline(file, str)) {
        if (regex_search(str, match, form)) {
            cout << str <<endl;
            pair<string, vector<string>> temp;
            temp.first = match.str(1);
            string set_string = match.str(2);
            temp.first = removeSpaces(temp.first);

            production *t;

            map<string, production *>::iterator it;
            it = nonterminals.find(temp.first);
            if(it == nonterminals.end()) {
                t = new production(temp.first, non_terminal);
                size_t found = set_string.find("\\L");
                if (found != string::npos)t->eps = true;
                nonterminals.insert({temp.first, t});
            }else{
                t=it->second;
            }

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

void ReadGrammars::split(const string &str,production *t,map<string, production *> &nonterminals,map<string, production *> &terminals) {
    vector<string> after_split;
    string ans;
    int count=0;
    for (auto i : str) {
        if (!ans.empty() && (i == '|' )) {
            ans.erase(remove(ans.end()-1, ans.end(), ' '), str.end());
            splitSpace(ans);
//            after_split.push_back(ans);
            ans = "";

        }else if(ans.empty() && (i == ' ' )){}
        else if((i == '\'' )){
            if(count%2==0){
                ans += ' ';
                ans += i;
            }else{
                ans += i;
                ans += ' ';
            }
            count++;
        }
        else {
            ans += i;
        }
    }
    if (!ans.empty()) {
        after_split.push_back(ans);
    }

}

vector<string> ReadGrammars::splitSpace(const string &str){
    vector<string> splited;


    return splited;
}