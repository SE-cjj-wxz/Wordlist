#ifndef __GRAPH_H__
#define __GRAPH_H__

#include <vector>
#include "node.h"
using namespace std; 

class Graph {
public:
    explicit Graph(char* words[], int len);

private:
    vector<vector<Node> > hNodes;
};


#endif