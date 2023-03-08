#include "graph.h"

void lower(string& str) {
    for (auto &c: str) {
        if (c >= 'A' && c <= 'Z') {
            c = c - 'A' + 'a';
        }
    }
}

Graph::Graph(char* words[], int len) {
    hNodes = vector< vector<Node> > (26);
    for (int i = 0; i < len; i++) {
        string word = words[i];
        lower(word);
        Node node(word);
        hNodes[word.at(0) - 'a'].push_back(node); 
    }
}