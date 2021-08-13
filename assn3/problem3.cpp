#include <iostream>
#include <string>
#include <queue>
using namespace std;

struct State {
    string ss[3];
    int forbidden = 0;
    int stage = 0;
    int allsize = 0;
    State(string s1, string s2, string s3, int forbidden = 0, int stage = 0) : forbidden(forbidden), stage(stage) {
        ss[0] = s1;
        ss[1] = s2;
        ss[2] = s3;
    }
    int getAllSize() {
        return ss[0].size() + ss[1].size() + ss[2].size();
    }
};
bool operator<(State a, State b) {
    return a.allsize > b.allsize;
}

int main() {
    int T; cin >> T;
    vector<int> res;
    for (int t = 0; t < T; t++) {
        int c1, c2, c3;
        string a, b, c;
        cin >> c1 >> c2 >> c3 >> a >> b >> c;
        State st(a, b, c, 0);
        for (int i = 1; i <= 3; i++) {
            size_t pos = 0;
            for (; pos < st.ss[i - 1].size() && st.ss[i - 1][pos] == i + '0'; pos++);
            st.ss[i - 1] = st.ss[i - 1].substr(pos);
        }
        st.allsize = st.ss[0].size() + st.ss[1].size() + st.ss[2].size();
        int minsize = st.allsize;
        int currentstage = 0;
        priority_queue<State> q;
        q.push(st);
        while (!q.empty()) {
            State st = q.top();
            //cout << st.ss[0] << " " << st.ss[1] << " " << st.ss[2] << " Forbidden : " 
            //<< st.forbidden << " Stage : " << st.stage << endl;
            q.pop();
             if (st.stage == currentstage && st.allsize > minsize)
                 continue;
            bool flag = false;
            if (st.ss[0].empty() && st.ss[1].empty() && st.ss[2].empty()) {
                res.push_back(st.stage);
                break;
            }
            for (int i = 1; i <= 3; i++) {
                if (!st.ss[i - 1].empty()) continue;
                for (int j = 1; j <= 3; j++) {
                    if (i == j || st.ss[j - 1].empty()) continue;
                    if (st.forbidden != j && st.ss[j - 1].back() == i + '0') {
                        State tmp(st);
                        tmp.ss[j - 1] = tmp.ss[j - 1].substr(0, tmp.ss[j - 1].size() - 1);
                        tmp.forbidden = i;
                        tmp.stage += 1;
                        tmp.allsize -= 1;
                        minsize = tmp.allsize;
                        currentstage = tmp.stage;
                        q.push(tmp);
                        flag = true;
                    }
                }
            } if (flag) continue;
            for (int i = 1; i <= 3; i++) {
                if (st.forbidden == i) continue;
                for (int j = 1; j <= 3; j++) {
                    if (i == j || st.ss[i - 1].empty()) continue;
                    State tmp(st);
                    tmp.ss[j - 1] += tmp.ss[i - 1][tmp.ss[i - 1].size() - 1];
                    tmp.ss[i - 1] = tmp.ss[i - 1].substr(0, tmp.ss[i - 1].size() - 1);
                    tmp.forbidden = j;
                    tmp.stage = st.stage + 1;
                    q.push(tmp);
                }
            }
        }
    }
    for (auto a : res)
        cout << a << endl;
}