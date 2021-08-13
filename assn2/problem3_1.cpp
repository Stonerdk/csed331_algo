#include <iostream>
#include <cmath>
#include <vector>
#include <map>
#include <algorithm>
#include <string>
using namespace std;
map<int, pair<int, int>> blocks;
vector<long long int> currentBlocks;
vector<long long int> maxBlocks;

void dnc(int n, int m, int k) {
	int minv = min(min(n, m), k);
	if (minv == 0) return;
	if (minv == 1) {
		currentBlocks[0] += (long long)n * (long long)m * (long long)k;
		return;
	}
	int ms = (int)(log2(minv));
	int msk = (1 << ms) - 1;
	currentBlocks[ms] += (long long)(n >> ms) * (long long)(m >> ms) * (long long)(k >> ms);
	dnc(n & msk, m, k & ~msk);
	dnc(n, m & ~msk, k & msk);
	dnc(n & ~msk, m & msk, k);
	dnc(n & msk, m & msk, k & msk);
}

int main() {
	int T, bcnt, tmp, n, m, k;
	cin >> T;
	vector<string> res;
	for (int i = 0; i < 25; i++) {
		currentBlocks.push_back(0);
		maxBlocks.push_back(0);
	}
	for (int i = 0; i < T; i++) {
		cin >> bcnt;
		vector<int> entries;
		for (int j = 0; j < bcnt; j++) {
			cin >> tmp;
			entries.push_back((int)(log2(tmp)));
		} for (int j = 0; j < bcnt; j++) 
			cin >> maxBlocks[entries[j]];
		cin >> n >> m >> k;
		dnc(n, m, k);
		for (int j = (int)(log2(min(min(n, m), k))); j >= 1; j--) 
			if (maxBlocks[j] < currentBlocks[j]) {
				currentBlocks[j - 1] += (currentBlocks[j] - maxBlocks[j]) * 8;
				currentBlocks[j] = maxBlocks[j];
			}
		if (currentBlocks[0] > maxBlocks[0]) 
			res.push_back("-1");
		else {
			string s = "";
			for (auto e : entries) 
				s += to_string(currentBlocks[e]) + " ";
			res.push_back(s);
		}
		for (int i = 0; i < 25; i++) {
			currentBlocks[i] = 0;
			maxBlocks[i] = 0;
		}
	}
	for (auto r : res) {
		cout << r << endl;
	}
}