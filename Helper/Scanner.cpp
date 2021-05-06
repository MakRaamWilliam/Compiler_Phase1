#include "Scanner.h"

Scanner *Scanner::instance = nullptr;

Scanner *Scanner::getInstance() {

    if (instance == nullptr) {
        instance = new Scanner();
    }
    return instance;
}

vector<pair<string, string>> Scanner::scanProgramFile(const string &fileName, DFA *newRecognizer) {
    vector<pair<string, string>> tokens{};
    this->recognizer = newRecognizer;
    ifstream file(fileName);
    string line;
    vector<string> words{};
    while (getline(file, line)) {
        istringstream iss(line);
        vector<string> results((istream_iterator<string>(iss)), istream_iterator<string>());
        words.insert(words.end(), results.begin(), results.end());
    }
    for (string s : words) {
        vector<pair<string, string>> temp = scanWord(s);
        tokens.insert(tokens.end(), temp.begin(), temp.end());
    }
    return tokens;
}

vector<pair<string, string>> Scanner::scanWord(string &word) {
    vector<pair<string, string>> tokens{};
    Node *startState = this->recognizer->getStartState();
    Node *currentState = startState;
    Node *nullState = new Node("null", false);
    Node *finalState = nullState;
    int first = 0;
    int last = 0;
    for (int i = 0; i < word.size(); i++) {
        currentState = this->recognizer->move(currentState, word.at(i));
        if (currentState->isFinalState()) {
            last = i;
            finalState = currentState;
            if (i == word.size() - 1) {
                string s = word.substr(first, last - first + 1);
                tokens.emplace_back(s, finalState->getName());
                break;
            }
        } else if (currentState->getName() == "null" && finalState != nullState) {
            string s = word.substr(first, last - first + 1);
            tokens.emplace_back(s, finalState->getName());
            first = last + 1;
            i = last;
            finalState = nullState;
            currentState = startState;
        }
    }
    return tokens;
}
