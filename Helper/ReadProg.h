#ifndef READPROG_H

#include "DfaGraph.h"

class ReadProg {
public:
    static ReadProg *getInstance(DfaGraph *recognizer);

    queue<string> ReadProgFile(ifstream &file);
    string ReadWord(ifstream &file);

private:
    ReadProg() = default;

    static ReadProg *instance;

    queue<string> qu;

    vector<pair<string, string>> scanWord(string &word);

    DfaGraph *recognizer;

};


#endif
