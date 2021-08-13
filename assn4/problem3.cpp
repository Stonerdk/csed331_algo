#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;
int T, N, W;
vector<int> heights, positions;
long long dnq(int start, int end) {
    if (end <= start) return 0;
    if (end == start + 1) return (positions[end] - positions[start]) * heights[start];
    int minidx = start, minheight = heights[start];
    for(int i = start; i < end; i++) {
        if (heights[i] < minheight) {
            minheight = heights[i];
            minidx = i;
        }
    }
    long long ret = (long long)(positions[end] - positions[start]) * (long long)minheight;
    long long left = dnq(start, minidx);
    long long right = dnq(minidx + 1, end);
    long long mx = left > right ? left : right;
    mx = ret > mx ? ret : mx;
    return mx;
}
int main() {
    cin >> T;
    vector<long long> solution;
    for (int i = 0; i < T; i++) {
        heights.clear();
        positions.clear();
        cin >> N >> W;
        for(int j = 0; j < N; j++) {
            int l, r, h;
            cin >> l >> r >> h;
            heights.push_back(h);
            positions.push_back(l);
        }
        positions.push_back(W);
        solution.push_back(dnq(0, N));
    }
    for(auto s : solution) {
        cout << s << endl;
    }
}