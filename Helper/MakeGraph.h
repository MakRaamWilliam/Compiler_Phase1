#ifndef MAKEGRAPH_H

#include "NfaGraph.h"
#include "LexicalRule.h"

class NfaGraph;

class MakeGraph {
public:
    virtual ~MakeGraph() = default;

    static MakeGraph *getInstance();

    NfaGraph *makeLexRule(LexicalRule *rule, map<string, int> priorities);

    NfaGraph *makeComRecongz(vector<NfaGraph *> startsNodes );

    const set<char> &getAlphabet() const;

private:
    MakeGraph() = default;

    static MakeGraph *instance;
    set<char> alphabet;

    NfaGraph *makeOrRecogniz(NfaGraph *, NfaGraph *);
    NfaGraph *makeAndRecongz(NfaGraph *, NfaGraph *);
    NfaGraph *makeAlphatRecogniz(char , char );
    NfaGraph *makePosRecongz(NfaGraph *);
    NfaGraph *makeClouRecongz(NfaGraph *);

};


#endif
