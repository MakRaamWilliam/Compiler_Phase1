#include "ReadProg.h"

ReadProg *ReadProg::instance = nullptr;

ReadProg *ReadProg::getInstance(DfaGraph *DFA) {

    if (instance == nullptr) {
        instance = new ReadProg();
        instance->recognizer = DFA;
    }
    return instance;
}
string ReadProg::ReadWord(ifstream &file){
    if(this->qu.size()==0){
        this->qu = ReadProgFile(file);
        if(this->qu.size()==0)return "";

    }
    string s = this->qu.front();
    this->qu.pop();
    return s;

}

queue<string> ReadProg::ReadProgFile(ifstream &file) {
    queue<string> tokens{};
    string word;
    vector<string> words{};
    if (file >> word) {
        vector<pair<string, string>> words=scanWord(word);
        queue<string> q;
        for (pair<string, string> s : words) {
            q.push(s.second);
         }
        return q;
    }
    return tokens;
}

vector<pair<string, string>> ReadProg::scanWord(string &word) {
    vector<pair<string, string>> tokens{};
    Node *startState = this->recognizer->getStartState();
    Node *currentState = startState;
    Node *prevState = startState;
    Node *nullState = new Node("null", false);
    Node *finalState = nullState;
    int first = 0;
    int last = 0;
    for (int i = 0; i < word.size(); i++) {
        prevState = currentState;
        currentState = this->recognizer->move(currentState, word.at(i));

        // cout<<word.at(i);
        if (currentState->checkEndState()) {
            // cout<<"curr\n";
            last = i;
            finalState = currentState;
            if (i == word.size() - 1) {
                string s = word.substr(first, last - first + 1);
                tokens.emplace_back(s, finalState->getName());
                break;
            }
        } else if (currentState->getName() == "null" && finalState != nullState) {
            // cout<<"notcurr\n";
            string s = word.substr(first, last - first + 1);
            tokens.emplace_back(s, finalState->getName());
            first = last + 1;
            i = last;
            finalState = nullState;
            currentState = startState;
        }
        else if( currentState ==  this->recognizer->nullNode){
            //  cout<<"in elseeee "<< word.at(i)<<"\n";
            word=word.erase(i,1);
            i--;
            currentState = prevState;
        }
    }
    return tokens;
}
