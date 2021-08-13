#include <iostream>
#include <vector>
#include <map>
#include <queue>
#include <algorithm>
using namespace std;

struct Node {
    int index;
    Node* parent = nullptr;
    int dist = -1;
    bool visited = false;
    int dfs_order = -1;
    bool flag = false;
    vector<Node*> dests;
    Node(int index) : index(index) {}
};

struct Edge {
    Node* start;
    Node* end;
    int weight;
    bool limit = false;
    bool visited = false;
    Edge(Node* start, Node* end, int weight) : start(start), end(end), weight(weight) {}
};

vector<Node*> nodes;
map<pair<int, int>, Edge*> edgemap;
int mindist = -1;

Edge* getEdge(Node* start, Node* end) {
    if (edgemap.find({ start->index, end->index }) == edgemap.end())
        return nullptr;
    return edgemap[{start->index, end->index}];
}

void dfs(Node* node, int order) {
    node->visited = true;
    node->dfs_order = order;
    for (auto dest : node->dests) {
        if (getEdge(node, dest)->visited == false) {
            getEdge(node, dest)->visited = true;
            if (!dest->visited) {
                dest->dist = getEdge(node, dest)->weight;
                dfs(dest, order + 1);
            }
            if (dest->flag || dest->visited) {
                if (node->dfs_order > dest->dfs_order) {
                    node->dfs_order = dest->dfs_order;
                    node->flag = true;
                }
            }
        } 
    }
    if (node->flag == false) {
        if (node->dist != -1 && (mindist == -1 || mindist > node->dist))
            mindist = node->dist;
    }
}

int main() {
    int testcase; cin >> testcase;
    vector<int> res;
    for (int t = 0; t < testcase; t++) {
        int N, M; cin >> N >> M;
        for (int i = 0; i < N; i++)
            nodes.push_back(new Node(i));
        for (int i = 0; i < M; i++) {
            int src, dest, dist;
            cin >> src >> dest >> dist;
            if (edgemap.find({ src, dest }) != edgemap.end()) {
                edgemap[{src, dest}]->weight = -1;
            }
            else {
                Edge* edge = new Edge(nodes[src], nodes[dest], dist);
                nodes[src]->dests.push_back(nodes[dest]);
                nodes[dest]->dests.push_back(nodes[src]);
                edgemap[{src, dest}] = edge;
                edgemap[{dest, src}] = edge;
            }
        }
        dfs(nodes[0], 0);
        res.push_back(mindist);
        mindist = -1;
        edgemap.clear();
        for(auto n : nodes)
            delete n;
        nodes.clear();
    }
    for (auto r : res)
        cout << r << endl;
}