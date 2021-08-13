#include <iostream>
#include <string>
#include <queue>
#include <sstream>
using namespace std;

struct State {
    vector<char> ss[3];
    int forbidden = 0;
    int stage = 0;
    bool reduced = false;
    State(string s1, string s2, string s3, int forbidden, int stage, bool reduced = false) : forbidden(forbidden), stage(stage), reduced(reduced) {
        for (char& c : s1)
            ss[0].push_back(c);
        for (char& c : s2)
            ss[1].push_back(c);
        for (char& c : s3)
            ss[2].push_back(c);
    }
    State(const State& base, int forbidden, int stage, bool reduced) : forbidden(forbidden), stage(stage), reduced(reduced) {
        ss[0] = base.ss[0];
        ss[1] = base.ss[1];
        ss[2] = base.ss[2];
    }
    int getAllSize() {
        return ss[0].size() + ss[1].size() + ss[2].size();
    }
    vector<char>& operator[](int index) {
        return ss[index - 1];
    }
    string toString() {
        stringstream tmp;
        for (int i = 0; i < 3; i++) {
            for (char& c : ss[i]) tmp << c;
            tmp << " ";
        }
        tmp << "Forbidden : " << forbidden << "Stage : " << stage;
        return tmp.str();
    }
};

int main() {
    int T; cin >> T;
    vector<int> res;
    for (int t = 0; t < T; t++) {
        int c1, c2, c3; string a, b, c;
        cin >> c1 >> c2 >> c3 >> a >> b >> c;
        State st(a, b, c, 0, 0, false);
        for (int i = 1; i <= 3; i++)
            for (; !st[i].empty() && st[i].front() == i + '0'; st[i].erase(st[i].begin()));

        queue<State> q;
        q.push(st);
        int current_stage = 0;
        bool reduced = false;
        while (!q.empty()) {
            State st = q.front();
            
            q.pop();
            //if (current_stage != st.stage) {
            //    current_stage = st.stage;
             //   reduced = false;
            //}
            //if (reduced && st.reduced == false)
              //  continue;
            //cout << st.toString() << endl;
            bool flag = false;
            if (st.getAllSize() == 0) {
                res.push_back(st.stage);
                break;
            }
            for (int i = 1; i <= 3; i++) {
                if (!st[i].empty()) continue;
                for (int j = 1; j <= 3; j++) {
                    if (i == j || st[j].empty()) continue;
                    if (st.forbidden != j && st[j].back() == i + '0') {
                        //reduced = true;
                        State tmp(st, i, st.stage + 1, true);
                        tmp[j].pop_back();
                        q.push(tmp);
                        flag = true;
                    }
                }
            }// if (flag || reduced) continue;

            for (int i = 1; i <= 3; i++) {
                if (st.forbidden == i) continue;
                for (int j = 1; j <= 3; j++) {
                    if (i == j || st[i].empty()) continue;
                    State tmp(st, j, st.stage + 1, false);
                    tmp[j].push_back(tmp[i].back());
                    tmp[i].pop_back();
                    q.push(tmp);
                }
            }
        }
    }
    for (auto a : res)
        cout << a << endl;
}