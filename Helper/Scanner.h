#ifndef LEXICAL_ANALYZER_GENERATOR_SCANNER_H
#define LEXICAL_ANALYZER_GENERATOR_SCANNER_H

#include "DFA.h"

class Scanner {
public:
    static Scanner *getInstance();

    vector<pair<string, string>> scanProgramFile(const string &fileName, DFA *recognizer);

private:
    Scanner() = default;

    static Scanner *instance;

    vector<pair<string, string>> scanWord(string &word);

    DFA *recognizer;

};


#endif //LEXICAL_ANALYZER_GENERATOR_SCANNER_H