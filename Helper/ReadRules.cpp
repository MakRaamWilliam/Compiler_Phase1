#include "ReadRules.h"

#include <utility>

ReadRules *ReadRules::instance = nullptr;

ReadRules::ReadRules() {
    this->definition = regex(R"((\w+) *= *((\S|\s)+))");
    this->expression = regex(R"((\w+) *: *((\S|\s)+))");
    this->keyword = regex(R"(\{ *((\w+ *)+) *})");
    this->punctuation = regex(R"(\[ *(([^\d\w] *)+) *\])");
}

vector<LexicalRule *> ReadRules::ReadRuleFile(const string &rulefile, map<string, int> *priorities) {
    vector<LexicalRule *> rules;
    std::ifstream file(rulefile);
    std::string str;
    vector<string> puncts;
    vector<string> keywords;
    vector<string> regularExps;
    // cout<<"IN REeegex\n";
    while (std::getline(file, str)) {
        //     cout<<"IN REgex\n";
        if (regex_search(str, match, definition)) {
            pair<string, vector<string>> temp;
            temp.first = match.str(1);
            string set_string = match.str(2);
            set_string = removeSpaces(set_string);
            temp.second = splitDefinition(set_string);
            rules.push_back(LexBulider::getInstance()->buildPost(temp, RegularDefinition));
        } else if (regex_search(str, match, expression)) {
            pair<string, vector<string>> temp;
            temp.first = match.str(1);
            string set_string = match.str(2);
            temp.second = splitExpression(set_string);
            rules.push_back(LexBulider::getInstance()->buildPost(temp, RegularExpression));
            regularExps.push_back(temp.first);
        } else if (regex_search(str, match, keyword)) {
            vector<string> words = splitSpaces(match.str(1));
            vector<LexicalRule *> temp_vec = LexBulider::getInstance()->buildRules(words, Keyword);
            rules.insert(rules.end(), temp_vec.begin(), temp_vec.end());
            keywords.insert(keywords.end(), words.begin(), words.end());
        } else if (regex_search(str, match, punctuation)) {
            string set_string = match.str(1);
            set_string = removeSpaces(set_string);
            vector<string> words = splitEachChar(set_string);
            vector<LexicalRule *> temp_vec = LexBulider::getInstance()->buildRules(words, Punctuation);
            rules.insert(rules.end(), temp_vec.begin(), temp_vec.end());
            puncts.insert(puncts.end(), words.begin(), words.end());
        }
    }
    int i = 1;
    for (const string &s: regularExps) {
        priorities->insert(pair<string, int>(s, i));
    } i++;
    for (const string &s: keywords) {
        priorities->insert(pair<string, int>(s, i));
    } i++;
    for (const string &s: puncts) {
        priorities->insert(pair<string, int>(s, i));
    } i++;
    file.close();
    return rules;
}

string ReadRules::removeSpaces(string str) {
    str.erase(remove(str.begin(), str.end(), ' '), str.end());
    return str;
}

vector<string> ReadRules::splitEachChar(const string &str) {
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

vector<string> ReadRules::splitSpaces(string splitted) {
    vector<string> returner;
    string matched = std::move(splitted);
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

vector<string> ReadRules::splitDefinition(const string &str) {
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

vector<string> ReadRules::splitExpression(const string &str) {
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

ReadRules *ReadRules::getInstance() {
    if (instance == nullptr) {
        instance = new ReadRules;
    }
    return instance;
}

void ReadRules::makeTransTable(const string &fileName, const map<Node *, map<char, Node *>> &table,
                               const set<char> &alpha) {
    ofstream of;
    of.open(fileName + ".trnstb");
    streambuf *buf = of.rdbuf();
    std::ostream stream(buf);
    stream << left << setw(20) << "curr/Next";
    for (char c : alpha) {
        stream << setw(12) << c;
    }
    stream << endl;
    unordered_set<string> states;
    for (pair<Node *, map<char, Node *>> row : table) {
        if(states.find(row.first->getName()) != states.end())
            continue;
        states.insert(row.first->getName());
        stream << left << setw(20) << row.first->getName();
        for (char c : alpha) {
            stream << setw(12) << row.second.at(c)->getName();
        }
        stream << endl;
    }

}
