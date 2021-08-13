#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int main() {
	int T;
	cin >> T;
	vector<int> houses;
	vector<int> res;
	for (int i = 0; i < T; i++) {
		int N, acc = 0, x;
		cin >> N;
		for (int j = 0; j < N; j++) {
			cin >> x;
			houses.push_back(x);
		}
		sort(houses.begin(), houses.end());
		for (int j = 1; j < N; j++) {
			acc += (houses[j] - houses[j - 1]) * (N - abs(N - 2 * j)) / 2;
		}
		res.push_back(acc);
		houses.clear();
	}
	for (auto a : res) {
		cout << a << endl;
	}
}