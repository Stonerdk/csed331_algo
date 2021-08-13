#include <iostream>
#include <vector>
#include <cmath>
using namespace std;

class Grid {
public:
	int width;
	int height;
	vector<string> content;
	Grid(int height);
};
Grid::Grid(int height) {
	this->width = 0;
	this->height = height;
	for (int i = 0; i < height; i++)
		content.push_back("");
}

Grid append(Grid g) {
	Grid res = Grid(g.height * 2);
	for (int i = 0; i < g.height; i++) {
		res.content[i].insert(0, (g.width + 1) / 2, ' ');
		res.content[i] += g.content[i];
	}
	for (int i = 0; i < g.height; i++) {
		res.content[g.height + i].insert(0, g.width + 1, ' ');
		res.content[g.height + i].replace(0, g.content[i].size(), g.content[i]);
		res.content[g.height + i] += g.content[i];
	}
	res.width = 2 * g.width + 1;
	return res;
}

int main() {
	int T, N;
	cin >> T;
	Grid u = Grid(3);
	u.content[0] = "*****";
	u.content[1] = " * *";
	u.content[2] = "  *";
	u.width = 5;
	for (int i = 0; i < T; i++) {
		cin >> N;
		int k = (int)(log2(N / 3));
		Grid r = u;
		for (int j = 0; j < k; j++) {
			r = append(r);
		}
		for (int j = 0; j < r.height; j++) {
			cout << r.content[j] << endl;
		}
	}
}