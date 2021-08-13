#include <iostream>
#include <cmath>
#include <vector>
#include <bitset>
using namespace std;

int main() {
    int testcase;
    cin >> testcase;
    vector<string> sol;
    for(int t = 0; t < testcase; t++) {
        int N, K;
        cin >> N >> K;
        vector<int> masks, conditions, conflicts;
        for (int k = 0; k < K; k++) {
            int a[3], idx[3], conflict = 0, mask = 0, condition = 0;
            cin >> a[0] >> a[1] >> a[2];
            for (int j = 0; j < 3; j++) 
                idx[j] = 1 << (abs(a[j]) - 1);
            for (int j = 0; j < 3; j++) {
                mask |= idx[j];
                if (a[j] + a[(j + 1) % 3] == 0) conflict |= idx[j];
                if (a[j] > 0) condition |= idx[j];
            }
            conflicts.push_back(conflict);
            masks.push_back(mask);
            conditions.push_back(condition);
        }
        string flag = "NO";
        for (int i = 0; i < (1 << N); i++) {
            bool u = true;
            for (int k = 0; k < K; k++) {
                int g = (i ^ ~conditions[k] | conflicts[k]) & masks[k];
                u = u && (g != 0);
            }
            if (u == true) {
                flag = "YES";
                break;
            }
        }
        sol.push_back(flag);
    }
    for (string s : sol)
        cout << s << endl;
}