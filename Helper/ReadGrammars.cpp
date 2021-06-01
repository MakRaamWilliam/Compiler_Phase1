#include "ReadGrammars.h"



ReadGrammars::ReadGrammars() {
    this->form = regex(R"(#(\w+) *= *((\S|\s)+))");
//    this->expression = regex(R"((\w+) *: *((\S|\s)+))");
//    this->keyword = regex(R"(\{ *((\w+ *)+) *})");
//    this->punctuation = regex(R"(\[ *(([^\d\w] *)+) *\])");
}

void ReadGrammars::ReadGrammarFile(const string &grammarfile) {
//    vector<LexicalRule *> rules;
    std::ifstream file(grammarfile);
    std::string str;
//    vector<string> puncts;
//    vector<string> keywords;
//    vector<string> regularExps;
    while (std::getline(file, str)) {
        if (regex_search(str, match, form)) {
            cout << str <<endl;
//            pair<string, vector<string>> temp;
//            temp.first = match.str(1);
//            string set_string = match.str(2);
//            set_string = removeSpaces(set_string);
//            temp.second = splitDefinition(set_string);
//            rules.push_back(LexBulider::getInstance()->buildPost(temp, RegularDefinition));
        }
//        else if (regex_search(str, match, expression)) {
//            pair<string, vector<string>> temp;
//            temp.first = match.str(1);
//            string set_string = match.str(2);
//            temp.second = splitExpression(set_string);
//            rules.push_back(LexBulider::getInstance()->buildPost(temp, RegularExpression));
//            regularExps.push_back(temp.first);
//        } else if (regex_search(str, match, keyword)) {
//            vector<string> words = splitSpaces(match.str(1));
//            vector<LexicalRule *> temp_vec = LexBulider::getInstance()->buildRules(words, Keyword);
//            rules.insert(rules.end(), temp_vec.begin(), temp_vec.end());
//            keywords.insert(keywords.end(), words.begin(), words.end());
//        } else if (regex_search(str, match, punctuation)) {
//            string set_string = match.str(1);
//            set_string = removeSpaces(set_string);
//            vector<string> words = splitEachChar(set_string);
//            vector<LexicalRule *> temp_vec = LexBulider::getInstance()->buildRules(words, Punctuation);
//            rules.insert(rules.end(), temp_vec.begin(), temp_vec.end());
//            puncts.insert(puncts.end(), words.begin(), words.end());
//        }
    }
//    int i = 1;
//    for (const string &s: regularExps) {
//        priorities->insert(pair<string, int>(s, i));
//    } i++;
//    for (const string &s: keywords) {
//        priorities->insert(pair<string, int>(s, i));
//    } i++;
//    for (const string &s: puncts) {
//        priorities->insert(pair<string, int>(s, i));
//    } i++;
//    file.close();
//    return rules;
}
//ReadGrammars *ReadGrammars::getInstance() {
//    if (instance == nullptr) {
//        instance = new ReadGrammars;
//    }
//    return instance;
//}