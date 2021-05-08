#ifndef READRULES_H

#include <iostream>
#include <bits/stdc++.h>
#include <regex>
#include <algorithm>
#include "LexBulider.h"
#include "DfaGraph.h"

using namespace std;

class ReadRules {

public:
    virtual ~ReadRules() = default;

    vector<LexicalRule *> ReadRuleFile(const string &rulefile, map<string, int> *priorities);

    void makeTransTable(const string &fileName, const map<Node *, map<char, Node *>> &table, const set<char> &alpha);

    static ReadRules *getInstance();

private:
    regex definition, punctuation, keyword, expression;
    smatch match;

private:
    ReadRules();

    static ReadRules *instance;

    static vector<string> splitSpaces(string splitted);

    static string removeSpaces(string str);

    static vector<string> splitDefinition(const string &str);

    static vector<string> splitExpression(const string &str);

    static vector<string> splitEachChar(const string &str);


};


#endif
