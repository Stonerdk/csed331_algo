#include <iostream>
#include <vector>
#include <map>
#include <queue>
#include <algorithm>
using namespace std;

struct Node {
    int index;
    Node* parent = nullptr;
    int topology = 30001;
    vector<Node*> dests;
    Node(int index) : index(index) {}
};

struct Edge {
    int start;
    int end;
    int weight;
    bool visited = false;
    bool cycle = false;
    bool limit = false;
    Edge(int start, int end, int weight) : start(start), end(end), weight(weight) {}
};

vector<Node*> nodes;
map<pair<int, int>, Edge*> edgemap;

Edge* getEdge(Node* start, Node* end) {
    if (edgemap.find({ start->index, end->index }) == edgemap.end())
        return nullptr;
    return edgemap[{start->index, end->index}];
}

void setEdgeVisited(Node* start, Node* end) {
    Edge* e = getEdge(start, end);
    if (e != nullptr) e->visited = true;
}

void setEdgeCycled(Node* start, Node* end) {
    Edge* e = getEdge(start, end);
    if (e != nullptr) {
        e->cycle = true;
        //cout << start->index << " --> " << end->index << " cycled " << endl;
    }
}
int main() {
    int testcase; cin >> testcase;
    vector<int> res;
    for (int t = 0; t < testcase; t++) {
        int N, M; cin >> N >> M;
        nodes.clear();
        for (int i = 0; i < N; i++)
            nodes.push_back(new Node(i));
        for (int i = 0; i < M; i++) {
            int src, dest, dist;
            cin >> src >> dest >> dist;
            if (edgemap.find({ src, dest }) != edgemap.end()) {
                edgemap[{src, dest}]->limit = true;
            }
            else {
                Edge* edge = new Edge(src, dest, dist);
                nodes[src]->dests.push_back(nodes[dest]);
                nodes[dest]->dests.push_back(nodes[src]);
                edgemap[{src, dest}] = edge;
                edgemap[{dest, src}] = edge;
            }
        }
        nodes[0]->topology = 0;
        queue<pair<Node*, Node*>> q;
        for (auto d : nodes[0]->dests)
            q.push({ d, nodes[0] });

        while (!q.empty()) {
         
            Node* current = q.front().first;
            Node* parent = q.front().second;
            //cout << "current : " << current->index << " parent : " << parent->index << " visited? : " << getEdge(current, parent)->visited << endl;
            q.pop();
            if (getEdge(current, parent)->visited == true)
                continue;
            setEdgeVisited(current, parent);
            current->topology = min(current->topology, parent->topology + 1);
            if (current->parent == nullptr)
                current->parent = parent;
            else if (parent != current->parent) {
                //cout << "cycle occured : current : " << current->index << " parent : " << parent->index << " current parent : " << current->parent->index << endl;
                Node* source = parent, * dest = current;
                while (source != dest->parent) {
                    setEdgeCycled(dest->parent, dest);
                    setEdgeCycled(source, dest);
                    dest = dest->parent;
                    if (dest->topology < source->topology)
                        swap(source, dest);
                    if (getEdge(source, dest) != nullptr && getEdge(source, dest)->cycle == true)
                        break;
                }
                setEdgeCycled(source, dest);
            }

            for (auto d : current->dests) {
                if (getEdge(current, d)->visited == false) {
                    q.push({ d, current });
                }
            }
        }
        int mindist = -1;
        for (auto const& key : edgemap) {
            if (key.second->cycle == false && key.second->limit == false) {
                if (mindist == -1 || mindist > key.second->weight)
                    mindist = key.second->weight;
            }
        }
        res.push_back(mindist);
        edgemap.clear();
        for (auto n : nodes)
            delete n;
    }
    for (auto r : res)
        cout << r << endl;
}