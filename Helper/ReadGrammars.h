#ifndef PHASE1_READGRAMMARS_H
#define PHASE1_READGRAMMARS_H

#include <iostream>
#include <bits/stdc++.h>
#include <regex>
#include <algorithm>

using namespace std;

class ReadGrammars {

public:
    virtual ~ReadGrammars() = default;

    void ReadGrammarFile(const string &grammerfile);

//    void makeTransTable(const string &fileName, const map<Node *, map<char, Node *>> &table, const set<char> &alpha);

    static ReadGrammars *getInstance();

private:
    regex form;
    smatch match;

private:
    ReadGrammars();

    static ReadGrammars *instance;

//
//    static vector<string> splitSpaces(string splitted);
//
//    static string removeSpaces(string str);
//
//    static vector<string> splitDefinition(const string &str);
//
//    static vector<string> splitExpression(const string &str);
//
//    static vector<string> splitEachChar(const string &str);


};

#endif //PHASE1_READGRAMMARS_H
