#ifndef LEXICAL_ANALYZER_GENERATOR_READLEXICALRULESFILE_H
#define LEXICAL_ANALYZER_GENERATOR_READLEXICALRULESFILE_H

#include <iostream>
#include <bits/stdc++.h>
#include <regex>
#include <algorithm>
#include "LexicalRuleBuilder.h"
#include "DFA.h"

using namespace std;

class ReadLexicalRulesFile {

public:
    virtual ~ReadLexicalRulesFile() = default;

    vector<LexicalRule *> read_from_file(const string &input_file, map<string, int> *priorities);

    void printTable(const string &fileName, const map<Node *, map<char, Node *>> &table, const set<char> &alphabet);

    static ReadLexicalRulesFile *getInstance();

private:
    regex regular_definition_regex;
    regex regular_expression_regex;
    regex keywords_regex;
    regex punctuations_regex;
    smatch match;

private:
    ReadLexicalRulesFile();

    static ReadLexicalRulesFile *instance;

    static vector<string> split_by_spaces(string to_be_splitted);

    static string removeSpaces(string str);

    static vector<string> split_each_char(const string &str);

    static vector<string> split_for_regular_definition(const string &str);

    static vector<string> split_for_regular_expression(const string &str);

};


#endif //LEXICAL_ANALYZER_GENERATOR_READLEXICALRULESFILE_H
