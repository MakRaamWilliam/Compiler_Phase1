#ifndef LEXICALRULE_H
#define LEXICALRULE_H

#include <iostream>
#include <bits/stdc++.h>

using namespace std;

enum LexicalType {
    RegularExpression, Keyword, Punctuation, RegularDefinition
};
enum LexicalTermType {
    Operation, CharGroup, WORD, parenthesis, EPSILON
};

class LexicalRuleTerm {
public:
    LexicalRuleTerm(string value, LexicalTermType type) {
        this->value = std::move(value);
        this->type = type;
    }

    virtual ~LexicalRuleTerm() = default;

    const string &getValue() const {
        return this->value;
    }

    LexicalTermType getType() const {
        return this->type;
    }

private:
    string value;
    LexicalTermType type;
};

class LexicalRule {
public:
    LexicalRule(string name, LexicalType type) {
        this->name = std::move(name);
        this->type = type;
    }

    LexicalRule(string name, LexicalType type, vector<LexicalRuleTerm *> terms) {
        this->name = std::move(name);
        this->type = type;
        this->terms = std::move(terms);
    }

    virtual ~LexicalRule() {
        this->terms.clear();
    }

    const string &getName() const {
        return this->name;
    }

    LexicalType getType() const {
        return this->type;
    }

    vector<LexicalRuleTerm *> getTerms() const {
        return this->terms;
    }

    void addTerm(LexicalRuleTerm *term) {
        this->terms.push_back(term);
    }


private:
    vector<LexicalRuleTerm *> terms;
    string name;
    LexicalType type;

};

#endif