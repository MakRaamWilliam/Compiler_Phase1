#include <iostream>
#include "Helper/ReadLexicalRulesFile.h"
#include "Helper/Node.h"
#include "Helper/DFA.h"
#include "Helper/Builder.h"
#include "Helper/Converter.h"
#include "Helper/Minimizer.h"
#include "Helper/Scanner.h"
using namespace std;

int main() {

    //----------------- parsing file and build -----------
    map<string, int> priorities{};
    vector<LexicalRule*>rules = ReadLexicalRulesFile::getInstance()->read_from_file("test.txt", &priorities);
    NFA* nfa = Builder::getInstance()->buildNFAFromLexicalRules(rules, priorities);

    //------------------------------
    cout <<"DOOneeeee Pars\n";
    DFA* dfa = Converter::getInstance()->convert(nfa, Builder::getInstance()->getAlphabet());
    map<Node *, map<char, Node *>> ans = dfa->getDTable();



    Minimizer::getInstance()->DFAMinimize(dfa);
    ans = dfa->getDTable();

    ReadLexicalRulesFile::getInstance()->printTable("table", ans, Builder::getInstance()->getAlphabet());



    vector<pair<string, string>> tokens = Scanner::getInstance()->scanProgramFile("prog.txt",  dfa);
    for(const pair<string, string>&token : tokens){
        cout << token.second << endl;
    }

    return 0;
}
/*
 * int sum , count , pass , mnt;
while (pass !=10)
{
if(pass <= 50)
pass = pass + 1 ;
else
pass = pass --;
}

 */