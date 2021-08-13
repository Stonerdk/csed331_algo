#include <iostream>
#include <string>
#include <vector>
#include <queue>
#include <algorithm>
#include <unordered_set>
#include <sstream>
using namespace std;

class Optimized {
public:
    vector<string> v{ "", "", "" };
    int stage = 0;
    int forbidden = -1;
    bool isEmpty();
    Optimized(vector<string> raw, int stage = 0, int forbidden = -1);
    Optimized();
    int hash(bool verbose = false);
    Optimized act(char src, char dest);
    string toString();
};

int Optimized::hash(bool verbose) {
    vector<pair<string, char>> pr({ {v[0], 0}, {v[1], 1}, {v[2], 2} });
    sort(pr.begin(), pr.end());
    int res = 0;
    for (char i = 0; i < 3; i++) {
        for (char& c : v[pr[i].second]) {
            res <<= 2;
            char pl = pr[c - 49].second;
            res += pl;
            //if (verbose) cout << (int)pl << " ";
        }
        if (i != 2) {
            res <<= 2;
            res += 3;
            //if (verbose) cout << "\t";
        }
    }
    //if (verbose) cout << endl;
    return res;
}

Optimized::Optimized() {

}

Optimized::Optimized(vector<string> raw, int stage, int forbidden) : stage(stage), forbidden(forbidden) {
    for (char i = 0; i < 3; i++) {
        v[i] = raw[i];
        while (!v[i].empty() && v[i].front() == i + 49)
            v[i].erase(v[i].begin());
    }
}


Optimized Optimized::act(char src, char dest) {
    Optimized tmp(v, stage + 1, dest);
    char last = tmp.v[src].back();
    tmp.v[src].pop_back();
    if (!(v[dest].empty() && last - 49 == dest))
        tmp.v[dest].push_back(last);
    return tmp;
}

bool Optimized::isEmpty() {
    return v[0].empty() && v[1].empty() && v[2].empty();
}

string Optimized::toString() {
    stringstream ss;
    ss << v[0] << "\t" << v[1] << "\t" << v[2] << "\thash : " << hash() << " stage : " << stage << " forb : " << forbidden;
    return ss.str();
}

int main() {
    int T; cin >> T;
    vector<pair<int, int>> looplist{ {0, 1}, {0, 2}, {1, 0}, {1, 2}, {2, 0}, {2, 1} };
    vector<int> res;
    for (int t = 0; t < T; t++) {

        int l1, l2, l3;
        string x, y, z;
        queue<Optimized> q;
        unordered_set<int> hset;
        bool flag = false;
        cin >> l1 >> l2 >> l3;
        if (l1 != 0) cin >> x;
        if (l2 != 0) cin >> y;
        if (l3 != 0) cin >> z;
        Optimized start(vector<string>({ x, y, z }));
        //cout << start.toString() << endl;

        q.push(start);


        while (!q.empty() && !flag) {
            Optimized top = q.front();
            q.pop();
            if (top.isEmpty()) {
                flag = true;
                res.push_back(top.stage);
            }
            for (auto x : looplist) {
                int i = x.first, j = x.second;
                if (i == top.forbidden || top.v[i].empty()) continue;
                Optimized op = top.act(i, j);
                //cout << op.toString() << endl;
                int hsh = op.hash(true);
                if (hset.find(hsh) == hset.end()) {
                    if (op.isEmpty()) {
                        flag = true;
                        res.push_back(op.stage);
                        break;
                    }
                    q.push(op);
                    hset.insert(hsh);
                }
                else {
                    //cout << " : founded" << endl;
                }
            }
        }
    }

    for (auto r : res)
        cout << r << endl;
}