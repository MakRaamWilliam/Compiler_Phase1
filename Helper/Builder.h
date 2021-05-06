
#ifndef LEXICAL_ANALYZER_GENERATOR_BUILDER_H
#define LEXICAL_ANALYZER_GENERATOR_BUILDER_H
#include "NFA.h"
#include "LexicalRule.h"
class NFA;
class Builder {
public:
    virtual ~Builder() = default;
    static Builder* getInstance();
    NFA* buildNFAFromLexicalRule(LexicalRule* rule, map<string, int> priorities);
    NFA* buildNFAFromLexicalRules(const vector<LexicalRule*>& rules, const map<string, int>& priorities);
    const set<char> &getAlphabet() const;

private:
    Builder() = default;
    static Builder* instance;
    set<char>alphabet;

    NFA* buildLetterRecognizer(char letter);
    NFA* buildEPSRecognizer();
    NFA* buildAlphabetRecognizer(char startAlphabet , char endAlphabet);
    NFA* buildORRecognizer(NFA* recognizer1, NFA* recognizer2);
    NFA* buildCombineRecognizer(NFA* recognizer1, NFA* recognizer2);
    NFA* buildANDRecognizer(NFA* recognizer1, NFA* recognizer2);
    NFA* buildClosureRecognizer(NFA* recognizer);
    NFA* buildPositiveClosureRecognizer(NFA* recognizer);
};


#endif //LEXICAL_ANALYZER_GENERATOR_BUILDER_H
