#include <vector>
#include <iostream>
#include <algorithm>
using namespace std;

struct Building {
    int x1; int x2; int y;
    Building(int x1, int x2, int y) : x1(x1), x2(x2), y(y) {};
};

struct Point {
    int x; int y;
    Point(int x, int y) : x(x), y(y) {};
};

vector<Building> buildings;

vector<Point> merge(vector<Point> left, vector<Point> right) {
    vector<Point> v;
    int ly = 0, ry = 0, latest = 0, li = 0, ri = 0, xx = 0;
    while(li < left.size() || ri < right.size()) {
        if (li >= left.size()) {
            v.push_back(right[ri++]);
        }
        else if (ri >= right.size()) {
            v.push_back(left[li++]);
        }
        else {
            int X = left[li].x, Y = right[ri].x;
            if (X >= Y) {
                xx = right[ri].x;
                ry = right[ri++].y;
            }
            if (X <= Y) {
                xx = left[li].x;
                ly = left[li++].y;
            }
            if (latest != max(ly, ry))
                v.push_back(Point(xx, latest = max(ly, ry)));
        }
    }
    return v;
}

vector<Point> getVertex(int s, int e) {
    if (e == s + 1) {
        return vector<Point> {Point(buildings[s].x1, buildings[s].y), Point(buildings[s].x2, 0)};
    }
    else {
        int pivot = (s + e) / 2;
        return merge(getVertex(s, pivot), getVertex(pivot, e));
    }
}

int main() {
    int N;

    cin >> N;
    for(int i = 0; i < N; i++) {
        int x1, x2, y;
        cin >> x1 >> y >> x2;
        buildings.push_back(Building(x1, x2, y));
    }   

    vector<Point> res = getVertex(0, N);
    for (auto r : res) {
        cout << r.x << " " << r.y << " ";
    }
}