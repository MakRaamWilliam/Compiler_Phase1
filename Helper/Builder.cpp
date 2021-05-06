#include "Builder.h"
Builder* Builder::instance = nullptr;

Builder* Builder::getInstance()  {

    if(!instance){
        instance = new Builder();
    }
    return instance;
}

NFA* Builder::buildEPSRecognizer() {
    return Builder::buildLetterRecognizer(EPS);
}

NFA* Builder::buildLetterRecognizer(char letter) {

    return buildAlphabetRecognizer(letter, letter);
}

NFA *Builder::buildAlphabetRecognizer(char startAlphabet, char endAlphabet) {
    Node* start = new Node("0" , !FINALSTATE);
    Node* end = new Node("1" , FINALSTATE);
    start->addEdge(new Edge(end, startAlphabet, endAlphabet));
    return new NFA(start, end);
}

NFA *Builder::buildORRecognizer(NFA *recognizer1, NFA *recognizer2) {
    Node* start = new Node(!FINALSTATE);
    Node* end = new Node (FINALSTATE);

    recognizer1->getEnd()->setIsFinal(!FINALSTATE);
    recognizer2->getEnd()->setIsFinal(!FINALSTATE);

    start->addEdge(new Edge(recognizer1->getStart(), EPS, EPS));
    start->addEdge(new Edge(recognizer2->getStart(), EPS, EPS));

    recognizer1->getEnd()->addEdge(new Edge(end, EPS, EPS));
    recognizer2->getEnd()->addEdge(new Edge(end, EPS, EPS));

    free(recognizer1);
    free(recognizer2);

    return new NFA(start, end);
}

NFA *Builder::buildANDRecognizer(NFA *recognizer1, NFA *recognizer2) {

    if(recognizer1 == nullptr){
        return recognizer2;
    }else if(recognizer2 == nullptr){
        return recognizer1;
    }
    Node* start = recognizer1->getStart();
    Node* end = recognizer2->getEnd();

    recognizer1->getEnd()->setIsFinal(!FINALSTATE);
    recognizer1->getEnd()->addEdge(new Edge(recognizer2->getStart(), EPS, EPS));

    free(recognizer1);
    free(recognizer2);

    return new NFA(start, end);
}

NFA *Builder::buildClosureRecognizer(NFA *recognizer) {

    NFA* result = buildPositiveClosureRecognizer(recognizer);
    result->getStart()->addEdge(new Edge(result->getEnd(), EPS, EPS));

    return result;
}

NFA *Builder::buildPositiveClosureRecognizer(NFA *recognizer) {

    Node* start = new Node(!FINALSTATE);
    Node* end = new Node (FINALSTATE);
    start->addEdge(new Edge(recognizer->getStart(), EPS, EPS));

    recognizer->getEnd()->setIsFinal(!FINALSTATE);

    recognizer->getEnd()->addEdge(new Edge(recognizer->getStart(), EPS, EPS));
    recognizer->getEnd()->addEdge(new Edge(end, EPS, EPS));

    free(recognizer);

    return new NFA(start, end);
}

NFA *Builder::buildCombineRecognizer(NFA *recognizer1, NFA *recognizer2) {

    if(recognizer1 == nullptr){
        return recognizer2;
    }else if(recognizer2 == nullptr){
        return recognizer1;
    }
    Node* start = new Node(!FINALSTATE);

    start->addEdge(new Edge(recognizer1->getStart(), EPS, EPS));
    start->addEdge(new Edge(recognizer2->getStart(), EPS, EPS));

    free(recognizer1);
    free(recognizer2);

    return new NFA(start, nullptr);
}

NFA *Builder::buildNFAFromLexicalRule(LexicalRule *rule, map<string, int> priorities) {
    NFA* result = nullptr;
    stack<NFA*> stack{};
    for(LexicalRuleTerm* term:rule->getTerms()){
        switch(term->getType()){
            case Operation:{
                if(term->getValue() == "|"){
                    NFA* b = stack.top();stack.pop();
                    NFA* a = stack.top();stack.pop();
                    stack.push(buildORRecognizer(a, b));

                }else if(term->getValue() == "+"){
                    NFA* a = stack.top();stack.pop();
                    stack.push(buildPositiveClosureRecognizer(a));

                }else if(term->getValue() == "*"){
                    NFA* a = stack.top();stack.pop();
                    stack.push(buildClosureRecognizer(a));
                }else{
                    NFA* b = stack.top();stack.pop();
                    NFA* a = stack.top();stack.pop();
                    stack.push(buildANDRecognizer(a, b));
                }
            }break;
            case CharGroup: {
                NFA* a = buildAlphabetRecognizer(term->getValue()[0], term->getValue()[2]);
                stack.push(a);
                for(char c = term->getValue()[0]; c <= term->getValue()[2];c++){
                    this->alphabet.insert(c);
                }
            }break;
            case WORD:{
                NFA* a = nullptr;
                for(char c: term->getValue()){
                    a = buildANDRecognizer(a, buildLetterRecognizer(c));
                    this->alphabet.insert(c);
                }
                stack.push(a);
            }break;
            case EPSILON:{
                NFA* a = buildEPSRecognizer();
                stack.push(a);
            }break;
            case parenthesis:
                break;
        }
    }
    result = stack.top();stack.pop();
    result->getEnd()->setName(rule->getName());
    result->getEnd()->setIsFinal(priorities.at(rule->getName()));
    return result;
}

NFA *Builder::buildNFAFromLexicalRules(const vector<LexicalRule *>&rules, const map<string, int>& priorities) {
    NFA* nfa = nullptr;
    this->alphabet.clear();
    for(LexicalRule* rule:rules){
        if(rule->getType() != RegularDefinition){

            NFA* a = this->buildNFAFromLexicalRule(rule, priorities);
            nfa = buildCombineRecognizer(nfa, a);
        }
    }
    return nfa;
}

const set<char> &Builder::getAlphabet() const {
    return alphabet;
}
