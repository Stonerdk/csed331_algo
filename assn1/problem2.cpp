#include <iostream>
#include <vector>
#include <cmath>
#include <functional>
#include <string>
#include <algorithm>

using namespace std;

struct Point {
	int x;
	int y;
	Point(int x, int y) : x(x), y(y) {}
};

double steepness(Point a, Point b) {
	return abs((double)(b.y - a.y) / (double)(b.x - a.x));
}

bool pointComp(const Point p, const Point q) {
	return p.x < q.x;
}

int main() {
	int t;
	cin >> t;
	vector<Point> points;
	vector<pair<Point, Point>> res;
	for (int i = 0; i < t; i++) {
		int n;
		cin >> n;
		for (int j = 0; j < n; j++) {
			int x, y;
			cin >> x >> y;
			points.push_back(Point(x, y));
		}
		sort(points.begin(), points.end(), pointComp);
		double maxsteepness = 0;
		int maxindex = 1;
		for (int j = 1; j < n; j++) {
			double steep = steepness(points[j], points[j - 1]);
			if (steep > maxsteepness) {
				maxsteepness = steep;
				maxindex = j;
			}
		}
		res.push_back(make_pair(points[maxindex - 1], points[maxindex]));
		points.clear();
	}

	for (auto r : res) {
		cout << r.first.x << " " << r.first.y << " " << r.second.x << " " << r.second.y << endl;
	}
}