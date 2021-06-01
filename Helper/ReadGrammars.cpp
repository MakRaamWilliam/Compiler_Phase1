#include "ReadGrammars.h"



ReadGrammars *ReadGrammars::instance = nullptr;

ReadGrammars::ReadGrammars() {
    this->form = regex(R"((\w+) *= *((\S|\s)+))");
//    this->expression = regex(R"((\w+) *: *((\S|\s)+))");
//    this->keyword = regex(R"(\{ *((\w+ *)+) *})");
//    this->punctuation = regex(R"(\[ *(([^\d\w] *)+) *\])");
}

void ReadGrammars::ReadGrammarFile(const string &grammarfile) {
    std::ifstream file(grammarfile);
    std::string str;

    while (std::getline(file, str)) {
        if (regex_search(str, match, form)) {
            cout << str <<endl;
            pair<string, vector<string>> temp;
            temp.first = match.str(1);
            string set_string = match.str(2);

            set_string = removeSpaces(set_string);
            temp.second = split(set_string);
            nonTerminal *t=new nonTerminal(temp.first,temp.second);
            size_t found = set_string.find("\\L");
            if(found != string::npos)t->eps=true;
//            cout << temp.first << "---";
            for(string s : t->terms){
                cout <<t->value<<"-->"<< s<<endl;
            }
            cout<<t->value<<" is eps ="<< t->eps<<endl;
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

vector<string> ReadGrammars::split(const string &str) {
    vector<string> after_split;
    string ans;
    for (auto i : str) {
        if (!ans.empty() && (i == '|' )) {
            after_split.push_back(ans);
            ans = "";
//            ans += i;
//            after_split.push_back(ans);
//            ans = "";
        } else {
            ans += i;
        }
    }
    if (!ans.empty()) {
        after_split.push_back(ans);
    }
    return after_split;
}