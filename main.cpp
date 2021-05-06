#include <iostream>
#include "Helper/LexRules.h"
#include "Helper/Builder.h"
#include "Helper/Converter.h"
#include "Helper/Minimiztion.h"
#include "Helper/Scanner.h"
using namespace std;

int main() {

    // parsing file and build
    map<string, int> mp_prio{};

    vector<LexicalRule*>vec_rule = LexRules::getInstance()->read_from_file("rules.txt", &mp_prio);
    NFA* nfa = Builder::getInstance()->buildNFAFromLexicalRules(vec_rule, mp_prio);

    //convert  from nfa to dfa
    cout <<"DOOneeeee Pars\n";
    DFA* dfa = Converter::getInstance()->convert(nfa, Builder::getInstance()->getAlphabet());
    map<Node *, map<char, Node *>> op = dfa->getDTable();


    //minimize dfa
    Minimiztion::getInstance()->DFAMinimize(dfa);
    op = dfa->getDTable();
    LexRules::getInstance()->printTable("table", op, Builder::getInstance()->getAlphabet());


    vector<pair<string, string>> tokens = Scanner::getInstance()->scanProgramFile("test.txt",  dfa);
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