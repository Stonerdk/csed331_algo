#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
#define MAXINT 2147483647
using namespace std;

class Node {
public:
    int dist = MAXINT;
    int parent = -1;
    vector<int> dests;
    Node();
    void addDest(int u);
    void set(int dist, int parent);
};

Node::Node() {
    this->dist = MAXINT;
    this->parent = -1;
}

void Node::addDest(int u) {
    this->dests.push_back(u);
}

void Node::set(int dist = MAXINT, int parent = -1) {
    this->dist = dist;
    this->parent = parent;
}


int main() {
    int T;
    cin >> T;
    vector<int> res;
    for (int t = 0; t < T; t++) {
        int N, M, minlen = MAXINT;
        queue<int> q;

        cin >> N >> M;
        vector<Node*> graph(N);
        for (int i = 0; i < N; i++)
            graph[i] = new Node();
        for (int j = 0; j < M; j++) {
            int u, v;
            cin >> u >> v;
            graph[u]->addDest(v);
            graph[v]->addDest(u);
        }

        for (int i = 0; i < N; i++) {
            for (auto np : graph) 
                np->set();
            q.push(i);
            graph[i]->set(0);
            while (!q.empty()) {
                int x = q.front();
                q.pop();
                for (auto d : graph[x]->dests) {
                    if (graph[d]->dist == MAXINT) {
                        graph[d]->set(graph[x]->dist + 1, x);
                        q.push(d);
                    }
                    else if (graph[x]->parent != d)
                        minlen = min(minlen, graph[d]->dist + graph[x]->dist + 1);             
                }
            }
        }
        res.push_back(minlen == MAXINT ? -1 : minlen);
    }
    for (int& r : res)
        cout << r << endl;
}