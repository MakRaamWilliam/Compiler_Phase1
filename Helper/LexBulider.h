#ifndef LEXICALBUILDER_H

#include "LexicalRule.h"

class LexBulider {
public:
    virtual ~LexBulider();

    static LexBulider *getInstance();

    LexicalRule *buildPost(const pair<string, vector<string>> &rule, enum LexicalType ruleType);

    vector<LexicalRule *> buildRules(const vector<string> &rules, enum LexicalType rulesType);

private:
    LexBulider() = default;

    static LexBulider *instance;
    map<string, vector<LexicalRuleTerm *>> mpTerms;
    vector<LexicalRuleTerm *> buildTerms(const vector<string> &rule);
    static bool isOper(const string &s);
    static bool isExpen(LexicalRuleTerm *currTerm, LexicalRuleTerm *nextTerm);

};

#endif
