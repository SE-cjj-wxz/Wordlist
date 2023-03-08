#ifndef __GRAPH_H__
#define __GRAPH_H__

#include <vector>
#include "node.h"
#include <string.h>
#include <queue>
using namespace std; 

class Graph {
public:
    explicit Graph(char* words[], int len);
    
    int countChains(vector<string>& results);

    int getLongestChain(vector<string>& results);

    void dfsCountChains(Node& node);

private:
    vector<vector<Node> > hNodes;
};


#endif