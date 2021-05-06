#include "ReadLexicalRulesFile.h"

#include <utility>

ReadLexicalRulesFile *ReadLexicalRulesFile::instance = nullptr;

ReadLexicalRulesFile::ReadLexicalRulesFile() {
    this->regular_definition_regex = regex(R"((\w+) *= *((\S|\s)+))");
    this->regular_expression_regex = regex(R"((\w+) *: *((\S|\s)+))");
    this->keywords_regex = regex(R"(\{ *((\w+ *)+) *})");
    this->punctuations_regex = regex(R"(\[ *(([^\d\w] *)+) *\])");
}

vector<LexicalRule *> ReadLexicalRulesFile::read_from_file(const string &input_file, map<string, int> *priorities) {
    vector<LexicalRule *> rules;
    std::ifstream file(input_file);
    std::string str;
    vector<string> puncts;
    vector<string> keywords;
    vector<string> regularExps;
    // cout<<"IN REeegex\n";
    while (std::getline(file, str)) {
        //     cout<<"IN REgex\n";
        if (regex_search(str, match, regular_definition_regex)) {
            pair<string, vector<string>> temp;
            temp.first = match.str(1);
            string set_string = match.str(2);
            set_string = removeSpaces(set_string);
            temp.second = split_for_regular_definition(set_string);
            rules.push_back(LexicalRuleBuilder::getInstance()->buildPostFixRule(temp, RegularDefinition));
        } else if (regex_search(str, match, regular_expression_regex)) {
            pair<string, vector<string>> temp;
            temp.first = match.str(1);
            string set_string = match.str(2);
            //set_string = removeSpaces(set_string);
            temp.second = split_for_regular_expression(set_string);
            rules.push_back(LexicalRuleBuilder::getInstance()->buildPostFixRule(temp, RegularExpression));
            regularExps.push_back(temp.first);
        } else if (regex_search(str, match, keywords_regex)) {
            vector<string> words = split_by_spaces(match.str(1));
            vector<LexicalRule *> temp_vec = LexicalRuleBuilder::getInstance()->buildRules(words, Keyword);
            rules.insert(rules.end(), temp_vec.begin(), temp_vec.end());
            keywords.insert(keywords.end(), words.begin(), words.end());
        } else if (regex_search(str, match, punctuations_regex)) {
            string set_string = match.str(1);
            set_string = removeSpaces(set_string);
            vector<string> words = split_each_char(set_string);
            vector<LexicalRule *> temp_vec = LexicalRuleBuilder::getInstance()->buildRules(words, Punctuation);
            rules.insert(rules.end(), temp_vec.begin(), temp_vec.end());
            puncts.insert(puncts.end(), words.begin(), words.end());
        }
    }
    int i = 1;
    for (const string &s: regularExps) {
        priorities->insert(pair<string, int>(s, i));
        i++;
    }
    for (const string &s: keywords) {
        priorities->insert(pair<string, int>(s, i));
        i++;
    }
    for (const string &s: puncts) {
        priorities->insert(pair<string, int>(s, i));
        i++;
    }
    file.close();
    return rules;
}

string ReadLexicalRulesFile::removeSpaces(string str) {
    str.erase(remove(str.begin(), str.end(), ' '), str.end());
    return str;
}

vector<string> ReadLexicalRulesFile::split_each_char(const string &str) {
    vector<string> after_split;
    string temp;
    for (auto i : str) {
        if (i != '\\') {
            temp += i;
            after_split.push_back(temp);
            temp = "";
        }
    }
    return after_split;
}

vector<string> ReadLexicalRulesFile::split_by_spaces(string to_be_splitted) {
    vector<string> returner;
    string matched = std::move(to_be_splitted);
    string ans;
    bool exist = false;
    for (auto i : matched) {
        if (i == ' ' && ans != "") {
            returner.push_back(ans);
            ans = "";
            exist = false;
        } else {
            ans += i;
            exist = true;
        }
    }
    if (exist) {
        returner.push_back(ans);
    }
    return returner;
}

vector<string> ReadLexicalRulesFile::split_for_regular_definition(const string &str) {
    vector<string> after_split;
    string ans;
    for (auto i : str) {
        if (!ans.empty() && (i == '|' || i == '+' || i == '*' || i == '?' || i == '(' || i == ')')) {
            after_split.push_back(ans);
            ans = "";
            ans += i;
            after_split.push_back(ans);
            ans = "";
        } else {
            ans += i;
        }
    }
    if (!ans.empty()) {
        after_split.push_back(ans);
    }
    return after_split;
}

vector<string> ReadLexicalRulesFile::split_for_regular_expression(const string &str) {
    vector<string> after_split;
    string ans;
    for (auto i : str) {
        if (ans == "\\") {
            ans += i;
            after_split.push_back(ans);
            ans = "";
        } else if (ans.empty() && (i == '|' || i == '+' || i == '*' || i == '?' || i == '.' || i == '(' || i == ')')) {
            ans += i;
            after_split.push_back(ans);
            ans = "";
        } else if (!ans.empty() && (i == '|' || i == '+' || i == '*' || i == '?' || i == '.' || i == '(' || i == ')')) {
            after_split.push_back(ans);
            ans = "";
            ans += i;
            after_split.push_back(ans);
            ans = "";
        } else if (i == ' ') {
            after_split.push_back(ans);
            ans = "";
        } else {
            ans += i;
        }
    }
    if (!ans.empty()) {
        after_split.push_back(ans);
    }
    return after_split;
}

ReadLexicalRulesFile *ReadLexicalRulesFile::getInstance() {
    if (instance == nullptr) {
        instance = new ReadLexicalRulesFile;
    }
    return instance;
}

void ReadLexicalRulesFile::printTable(const string &fileName, const map<Node *, map<char, Node *>> &table,
                                      const set<char> &alphabet) {
    ofstream of;
    of.open(fileName + ".trnstb");
    streambuf *buf = of.rdbuf();
    std::ostream stream(buf);
    stream << left << setw(20) << "states\\input";
    for (char c : alphabet) {
        stream << setw(12) << c;
    }
    stream << endl;
    for (pair<Node *, map<char, Node *>> row : table) {
        stream << left << setw(20) << row.first->getName();
        for (char c : alphabet) {
            stream << setw(12) << row.second.at(c)->getName();
        }
        stream << endl;
    }

}
