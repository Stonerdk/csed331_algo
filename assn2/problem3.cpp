#include <iostream>
#include <cmath>
#include <vector>
#include <map>
#include <algorithm>
#include <string>
using namespace std;
map<int, pair<int, int>> blocks;

void addBlock(int key, int value) {
	if (blocks.find(key) == blocks.end())
		blocks[key] = make_pair(0, 0);
	blocks[key].first += value;
}

void dnc(int n, int m, int k) {
	int minv = min(min(n, m), k);
	if (minv == 0) return;
	if (minv == 1) {
		addBlock(1, n * m * k);
		return;
	}
	int ms = (int)(log2(minv));
	int msk = (1 << ms) - 1;
	addBlock(msk + 1, (n >> ms) * (m >> ms) * (k >> ms));
	dnc(n & msk, m, k & ~msk);
	dnc(n, m & ~msk, k & msk);
	dnc(n & ~msk, m & msk, k);
	dnc(n & msk, m & msk, k & msk);
}

int main() {
	int T, bcnt, tmp, n, m, k;
	cin >> T;
	vector<string> res;
	for (int i = 0; i < T; i++) {
		cin >> bcnt;
		vector<int> entries;
		for (int j = 0; j < bcnt; j++) {
			cin >> tmp;
			entries.push_back(tmp);
		} for (int j = 0; j < bcnt; j++) {
			cin >> tmp;
			blocks[entries[j]] = make_pair(0, tmp);
		}
		cin >> n >> m >> k;
		int mxkey = 1 << (int)(log2(min(min(n, m), k)));
		for (int key = mxkey; key >= 1; key >>= 1) {
			if (blocks.find(key) == blocks.end())
				blocks[key] = make_pair(0, 0);
		}
		dnc(n, m, k);
		for (int key = mxkey; key > 1; key >>= 1) {
			if (blocks[key].first > blocks[key].second) {
				int sub = blocks[key].first - blocks[key].second;
				blocks[key].first = blocks[key].second;
				blocks[key >> 1].first += sub * 8;
			}
		}
		
		if (blocks[1].first > blocks[1].second) {
			res.push_back("-1");
		}
		else {
			string s = "";
			for (auto e : entries) {
				s += to_string(blocks[e].first) + " ";
			}
			res.push_back(s);
		}
		blocks.clear();
	}
	for (auto r : res) {
		cout << r << endl;
	}
}