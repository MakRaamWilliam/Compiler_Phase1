#ifndef READPROG_H

#include "DfaGraph.h"

class ReadProg {
public:
    static ReadProg *getInstance();

    vector< pair<string, string>> *ReadProgFile( fstream &file,string word, DfaGraph *recognizer);
//    fstream openFile(const string &fileName);
private:
    ReadProg() = default;

    static ReadProg *instance;

    vector< pair<string, string>> *scanWord(string &word);

    DfaGraph *recognizer;

};


#endif
