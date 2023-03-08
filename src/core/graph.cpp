#include "graph.h"

typedef pair<int, int> pp; 

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

void Graph::dfsCountChains(Node& node) {
    node.color = GRAY; 
    int i = node.tail - 'a';
    node.results.push_back(node.word);
    for (int j = 0; j < hNodes[i].size(); j++) {
        if (hNodes[i][j].word == node.word) continue;
        if (hNodes[i][j].color == WHITE) {
            for (string chain: node.results) {
                hNodes[i][j].results.push_back(chain + " " + hNodes[i][j].word);
            }
            dfsCountChains(hNodes[i][j]);
        } 
    }
    node.color = BLACK;
}

int Graph::countChains(vector<string>& result) {
    for (int i = 0; i < 26; i++) {
        for (int j = 0; j < hNodes[i].size(); j++) {
            int idx = hNodes[i][j].tail - 'a';
            for (int k = 0; k < hNodes[idx].size(); k++) {
                if (hNodes[idx][k].word == hNodes[i][j].word) continue;
                hNodes[idx][k].degree++;
            }
        }
    }

    queue<pp> q;

    for (int i = 0; i < 26; i++) {
        for (int j = 0; j < hNodes[i].size(); j++) {
            if (hNodes[i][j].degree == 0) {
                q.push(pp(i, j));
            }
        }
    }

    while (!q.empty()) {
        pp p = q.front();
        q.pop();    
        int i = hNodes[p.first][p.second].tail - 'a'; 

        for (int j = 0; j < hNodes[i].size(); j++) {
            if (hNodes[i][j].word == hNodes[p.first][p.second].word) continue;
            hNodes[i][j].degree--; 

            for (int k = 0; k < hNodes[p.first][p.second].results.size(); k++) {
                hNodes[i][j].results.push_back(hNodes[p.first][p.second].results[k] + " " + hNodes[i][j].word);
            }

            if (hNodes[i][j].degree == 0) {
                q.push(pp(i, j));
            }
        }
    }

    for (int i = 0; i < 26; i++) {
        for (int j = 0; j < hNodes[i].size(); j++) {
            hNodes[i][j].removeSingleChain();
            result.insert(result.end(), hNodes[i][j].results.begin(), hNodes[i][j].results.end());
        }
    }
    
    return result.size(); 
}


int Graph::getLongestChain(vector<string>& result) {
    int degree[30];
    memset(degree, 0, sizeof(int) * 30);
    
    for (int i = 0; i < 26; i++) {
        for (int j = 0; j < hNodes[i].size(); j++) {
            degree[hNodes[i][j].tail - 'a']++;
        }
    }

    queue<pp> q;

    for (int i = 0; i < 26; i++) {
        if (degree[i] == 0) {
            for (int j = 0; j < hNodes[i].size(); j++) {
                q.push(pp(i, j));
                hNodes[i][j].color = GRAY; 
            }
        }
    }

    while (!q.empty()) {
        pp p = q.front();
        int i = hNodes[p.first][p.second].tail - 'a';
        for (int j = 0; j < hNodes[i].size(); j++) {
            if (hNodes[i][j].color == WHITE) {
                q.push(pp(i, j));
                hNodes[i][j].color = GRAY;
            }
        }
        q.pop();
        hNodes[p.first][p.second].color = BLACK;
    }
}
