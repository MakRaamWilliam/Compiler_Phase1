#ifndef LEXICAL_ANALYZER_GENERATOR_LEXICALRULEBUILDER_H
#define LEXICAL_ANALYZER_GENERATOR_LEXICALRULEBUILDER_H

#include "LexicalRule.h"

class LexicalRuleBuilder {
public:
    virtual ~LexicalRuleBuilder();

    static LexicalRuleBuilder *getInstance();

    LexicalRule *buildPostFixRule(const pair<string, vector<string>> &rule, enum LexicalType ruleType);

    vector<LexicalRule *> buildRules(const vector<string> &rules, enum LexicalType rulesType);


private:
    LexicalRuleBuilder() = default;

    static LexicalRuleBuilder *instance;
    map<string, vector<LexicalRuleTerm *>> mapOfTerms;

    vector<LexicalRuleTerm *> buildTerms(const vector<string> &rule);

    static bool isOperation(const string &s);

    static bool checkExpanding(LexicalRuleTerm *curTerm, LexicalRuleTerm *nextTerm);

};


#endif //LEXICAL_ANALYZER_GENERATOR_LEXICALRULEBUILDER_H
