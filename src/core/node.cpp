#include "node.h"

explicit Node::Node(string& str) {
    word = str;
    color = WHITE;
    value = str.size();
    tail = word.at(word.size() - 1);
    degree = 0;
    results.push_back(word);
}

void Node::removeSingleChain() {
    for (int i = 0; i < results.size(); i++) {
        if (results[i] == word) {
            results.erase(results.begin() + i);
            break; 
        }
    }
}