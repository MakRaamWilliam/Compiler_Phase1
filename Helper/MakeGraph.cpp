#include "MakeGraph.h"

MakeGraph *MakeGraph::instance = nullptr;

MakeGraph *MakeGraph::getInstance() {

    if (!instance) {
        instance = new MakeGraph();
    }
    return instance;
}


NfaGraph *MakeGraph::makeAlphatRecogniz(char startAlphabet, char endAlphabet) {
    Node *start = new Node("0", !FINALSTATE);
    Node *end = new Node("1", FINALSTATE);
    start->addEdge(new Edge(end, startAlphabet, endAlphabet));
    return new NfaGraph(start, end);
}

NfaGraph *MakeGraph::makeOrRecogniz(NfaGraph *recognizer1, NfaGraph *recognizer2) {
    Node *start = new Node(!FINALSTATE);
    Node *end = new Node(FINALSTATE);

    recognizer1->getEnd()->setEndState(!FINALSTATE);
    recognizer2->getEnd()->setEndState(!FINALSTATE);

    start->addEdge(new Edge(recognizer1->getStart(), EPS, EPS));
    start->addEdge(new Edge(recognizer2->getStart(), EPS, EPS));

    recognizer1->getEnd()->addEdge(new Edge(end, EPS, EPS));
    recognizer2->getEnd()->addEdge(new Edge(end, EPS, EPS));

    free(recognizer1);
    free(recognizer2);

    return new NfaGraph(start, end);
}

NfaGraph *MakeGraph::makeAndRecongz(NfaGraph *recognizer1, NfaGraph *recognizer2) {

    if (recognizer1 == nullptr) {
        return recognizer2;
    } else if (recognizer2 == nullptr) {
        return recognizer1;
    }
    Node *start = recognizer1->getStart();
    Node *end = recognizer2->getEnd();

    recognizer1->getEnd()->setEndState(!FINALSTATE);
    recognizer1->getEnd()->addEdge(new Edge(recognizer2->getStart(), EPS, EPS));

    free(recognizer1);
    free(recognizer2);

    return new NfaGraph(start, end);
}

NfaGraph *MakeGraph::makeClouRecongz(NfaGraph *recognizer) {

    NfaGraph *result = makePosRecongz(recognizer);
    result->getStart()->addEdge(new Edge(result->getEnd(), EPS, EPS));

    return result;
}

NfaGraph *MakeGraph::makePosRecongz(NfaGraph *recognizer) {

    Node *start = new Node(!FINALSTATE);
    Node *end = new Node(FINALSTATE);
    start->addEdge(new Edge(recognizer->getStart(), EPS, EPS));

    recognizer->getEnd()->setEndState(!FINALSTATE);

    recognizer->getEnd()->addEdge(new Edge(recognizer->getStart(), EPS, EPS));
    recognizer->getEnd()->addEdge(new Edge(end, EPS, EPS));

    free(recognizer);

    return new NfaGraph(start, end);
}

NfaGraph *MakeGraph::makeComRecongz(vector<NfaGraph *> startsNodes) {

    Node *start = new Node(!FINALSTATE);
    for (NfaGraph *recognizer2: startsNodes) {
        start->addEdge(new Edge(recognizer2->getStart(), EPS, EPS));
        free(recognizer2);
    }
    return new NfaGraph(start, nullptr);
}

NfaGraph *MakeGraph::makeLexRule(LexicalRule *rule, map<string, int> priorities) {
    NfaGraph *result = nullptr;
    stack<NfaGraph *> stack{};
    for (LexicalRuleTerm *term:rule->getTerms()) {
        switch (term->getType()) {
            case Operation: {
                if (term->getValue() == "|") {
                    NfaGraph *b = stack.top();
                    stack.pop();
                    NfaGraph *a = stack.top();
                    stack.pop();
                    stack.push(makeOrRecogniz(a, b));

                } else if (term->getValue() == "+") {
                    NfaGraph *a = stack.top();
                    stack.pop();
                    stack.push(makePosRecongz(a));

                } else if (term->getValue() == "*") {
                    NfaGraph *a = stack.top();
                    stack.pop();
                    stack.push(makeClouRecongz(a));
                } else {
                    NfaGraph *b = stack.top();
                    stack.pop();
                    NfaGraph *a = stack.top();
                    stack.pop();
                    stack.push(makeAndRecongz(a, b));
                }
            }
                break;
            case CharGroup: {
                NfaGraph *a = makeAlphatRecogniz(term->getValue()[0], term->getValue()[2]);
                stack.push(a);
                for (char c = term->getValue()[0]; c <= term->getValue()[2]; c++) {
                    this->alphabet.insert(c);
                }
            }
                break;
            case WORD: {
                NfaGraph *a = nullptr;
                for (char c: term->getValue()) {
                    a = makeAndRecongz(a, makeAlphatRecogniz(c,c));
                    this->alphabet.insert(c);
                }
                stack.push(a);
            }
                break;
            case EPSILON: {
                NfaGraph *a = makeAlphatRecogniz(EPS,EPS);
                stack.push(a);
            }
                break;
            case parenthesis:
                break;
        }
    }
    result = stack.top();
    stack.pop();
    result->getEnd()->setName(rule->getName());
    result->getEnd()->setEndState(priorities.at(rule->getName()));
    return result;
}


const set<char> &MakeGraph::getAlphabet() const {
    return alphabet;
}
