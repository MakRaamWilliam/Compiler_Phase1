#include "LexBulider.h"

LexBulider *LexBulider::instance = nullptr;

LexBulider::~LexBulider() {
    this->mpTerms.clear();
}

LexBulider *LexBulider::getInstance() {
    if (!instance) {
        instance = new LexBulider();
    }
    return instance;
}

LexicalRule *LexBulider::buildPost(const pair<string, vector<string>> &rule, enum LexicalType ruleType) {
    vector<LexicalRuleTerm *> terms = buildTerms(rule.second);
    vector<LexicalRuleTerm *> postFixTerms{};
    stack<LexicalRuleTerm *> stack{};
    for (LexicalRuleTerm *term : terms) {
        if (term->getType() == parenthesis) {
            if (term->getValue() == ")") {
                while (!stack.empty() && stack.top()->getValue() != "(" && stack.top()->getType() != parenthesis) {
                    postFixTerms.push_back(stack.top());
                    stack.pop();
                }
                stack.pop();
            } else {
                stack.push(term);
            }
        } else if (term->getType() == Operation) {
            if (term->getValue() == "$" || term->getValue() == "|") {
                while (!stack.empty() && (stack.top()->getType() == Operation && !(stack.top()->getValue() == "|"))
                       && !(stack.top()->getType() == parenthesis && stack.top()->getValue() == "(")) {
                    postFixTerms.push_back(stack.top());
                    stack.pop();
                }
            }
            stack.push(term);
        } else if (term->getType() == WORD && this->mpTerms.find(term->getValue()) != this->mpTerms.end()) {
            vector<LexicalRuleTerm *> tempTerms = this->mpTerms.at(term->getValue());
            postFixTerms.insert(postFixTerms.end(), tempTerms.begin(), tempTerms.end());
        } else {
            postFixTerms.push_back(term);
        }
    }
    while (!stack.empty()) {
        postFixTerms.push_back(stack.top());
        stack.pop();
    }
    this->mpTerms.insert(pair<string, vector<LexicalRuleTerm *>>(rule.first, postFixTerms));
    return new LexicalRule(rule.first, ruleType, postFixTerms);
}

vector<LexicalRule *> LexBulider::buildRules(const vector<string> &rules, enum LexicalType rulesType) {
    vector<LexicalRule *> results;
    for (const string &word: rules) {
        auto *LRule = new LexicalRule(word, rulesType);
        LRule->addTerm(new LexicalRuleTerm(word, WORD));
        results.push_back(LRule);
    }
    return results;
}

vector<LexicalRuleTerm *> LexBulider::buildTerms(const vector<string> &rule) {
    vector<LexicalRuleTerm *> terms{};
    for (string s:rule) {
        if (isOper(s)) {
            terms.push_back(new LexicalRuleTerm(s, Operation));
        } else if (s.find('-') == 1 && s.size() == 3) {
            terms.push_back(new LexicalRuleTerm(s, CharGroup));
        } else if (s.find('\\') < s.size()) {
            s.erase(remove(s.begin(), s.end(), '\\'), s.end());
            if (s == "L") {
                terms.push_back(new LexicalRuleTerm(s, EPSILON));
            } else {
                terms.push_back(new LexicalRuleTerm(s, WORD));
            }
        } else if (s == "(" || s == ")") {
            terms.push_back(new LexicalRuleTerm(s, parenthesis));
        } else if (!s.empty() && s != " ") {
            terms.push_back(new LexicalRuleTerm(s, WORD));
        }
    }
    vector<LexicalRuleTerm *> expandedTerms{};
    for (int i = 0; i < terms.size() - 1; i++) {
        LexicalRuleTerm *curTerm = terms.at(i);
        LexicalRuleTerm *nextTerm = terms.at(i + 1);
        expandedTerms.push_back(curTerm);

        if (isExpen(curTerm, nextTerm)) {
            expandedTerms.push_back(new LexicalRuleTerm("$", Operation));
        }
    }
    expandedTerms.push_back(terms.back());
    terms.clear();
    return expandedTerms;
}

bool LexBulider::isOper(const string &s) {
    return s == "+" || s == "*" || s == "|";
}

bool LexBulider::isExpen(LexicalRuleTerm *currTerm, LexicalRuleTerm *nextTerm) {

    bool checkCur = (currTerm->getType() == WORD || currTerm->getType() == CharGroup || currTerm->getType() == EPSILON) ||
                    (currTerm->getType() == Operation && (currTerm->getValue() == "+" || currTerm->getValue() == "*")) ||
                    (currTerm->getType() == parenthesis && currTerm->getValue() == ")");

    bool checkNext =
            (nextTerm->getType() == WORD || nextTerm->getType() == CharGroup || nextTerm->getType() == EPSILON) ||
            (nextTerm->getType() == parenthesis && nextTerm->getValue() == "(");

    return checkCur && checkNext;
}
