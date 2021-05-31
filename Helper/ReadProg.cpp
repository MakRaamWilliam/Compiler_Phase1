#include "ReadProg.h"

ReadProg *ReadProg::instance = nullptr;

ReadProg *ReadProg::getInstance() {

    if (instance == nullptr) {
        instance = new ReadProg();
    }
    return instance;
}

//fstream ReadProg::openFile(const string &fileName){
//    fstream file;
//    file.open(fileName.c_str());
//    return file;
//}

vector< pair<string, string>> *ReadProg::ReadProgFile( fstream &file,string word, DfaGraph *recognizer) {
//    pair<string, string> *token=NULL;
    this->recognizer = recognizer;
//    ifstream file(fileName);
//    string line;
//    vector<string> words{};
//    while (getline(file, line)) {
//        istringstream iss(line);
//        vector<string> results((istream_iterator<string>(iss)), istream_iterator<string>());
//        words.insert(words.end(), results.begin(), results.end());
//    }
        if(file >> word) { //take word and print
//            words.push_back(word);
        }else return NULL;


//    for (string s : words) {
//        pair<string, string> temp = scanWord(s);
//        tokens.insert(tokens.end(), temp.begin(), temp.end());
//    }

    return scanWord(word);
}

vector< pair<string, string>> *ReadProg::scanWord(string &word) {
    vector< pair<string, string>> *tokens=new vector< pair<string, string>>;
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

                tokens->emplace_back(s, finalState->getName());
                break;
            }
        } else if (currentState->getName() == "null" && finalState != nullState) {
           // cout<<"notcurr\n";
            string s = word.substr(first, last - first + 1);
//            token->first=s;
//            token->second=finalState->getName();
            tokens->emplace_back(s, finalState->getName());
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
