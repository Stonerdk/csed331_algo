#include <iostream>
#include <map>
#include <vector>
using namespace std;

struct Node {
    int index;
    int value = 0;
    Node* prev;
    Node* next;
    Node(int index) : index(index), value(0), prev(nullptr), next(nullptr) {}
};

int main() {
    int T;
    cin >> T;
    map<int, Node*> hash;
    vector<string> res;

    for (int i = 0; i < T; i++) {

        //initialization
        int N, C, x;
        bool flag = false;
        cin >> N >> C;
        Node* last = new Node(-1);

        for (int j = 0; j < N * C; j++) {
            cin >> x;
            if (flag)
                continue;
            if (hash.find(x) == hash.end()) {
                Node* temp = new Node(x);
                temp->prev = last;
                last->next = temp;
                last = temp;
                hash[x] = temp;
            } else {
                int prevIndex = hash[x]->prev->index;
                if (prevIndex != -1 && hash[prevIndex]->value == hash[x]->value) {
                    flag = true;
                    continue;
                }
                hash[x]->value++;
            }
        }
        
        //print
        if (flag)
            res.push_back("YES");
        else
            res.push_back("NO");

        //delete
        for (std::pair<int, Node*> n : hash) {
            delete hash[n.first];
        } hash.clear();
    }

    for (auto c : res) {
        cout << c << endl;
    }
}