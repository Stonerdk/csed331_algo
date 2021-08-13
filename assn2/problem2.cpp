#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int main() {
	int T; cin >> T;
	vector<int> res;
	for (int i = 0; i < T; i++) {
		int N, x, dp, mx; 
		cin >> N >> x;
		dp = x;
		mx = x;
		for (int j = 0; j < N - 1; j++) {
			cin >> x;
			dp = max(dp, 0) + x;
			mx = max(dp, mx);
		}
		res.push_back(mx);
	}
	for (auto p : res) {
		cout << p << endl;
	}
}