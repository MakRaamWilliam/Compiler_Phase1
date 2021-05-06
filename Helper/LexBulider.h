#ifndef LEXICALBUILDER_H

#include "LexicalRule.h"

class LexBulider {
public:
    virtual ~LexBulider();

    static LexBulider *getInstance();

    LexicalRule *buildPostFixRule(const pair<string, vector<string>> &rule, enum LexicalType ruleType);

    vector<LexicalRule *> buildRules(const vector<string> &rules, enum LexicalType rulesType);


private:
    LexBulider() = default;

    static LexBulider *instance;
    map<string, vector<LexicalRuleTerm *>> mapOfTerms;

    vector<LexicalRuleTerm *> buildTerms(const vector<string> &rule);

    static bool isOperation(const string &s);

    static bool checkExpanding(LexicalRuleTerm *curTerm, LexicalRuleTerm *nextTerm);

};


#endif
