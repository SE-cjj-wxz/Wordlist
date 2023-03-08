#ifndef __NODE_H__
#define __NODE_H__

#include <string>
using namespace std;

#define WHITE 0
#define GRAY 1
#define BLACK 2

class Node {
public:
    string word; 
    int color;
    int value;
    int max;
    Node* prev; 
    int degree;
    char tail;
    vector<string> results;
    explicit Node(string& str);
    void removeSingleChain();
};


#endif 