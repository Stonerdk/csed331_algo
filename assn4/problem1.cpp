#include <iostream>
#include <queue>
#include <algorithm>

// #define INT_MAX 0x7fffffff
std::vector<std::pair<int64_t, int64_t>> data;

int main() {
    std::cin.tie(0); std::ios::sync_with_stdio(false);
    int test_case;

    std::cin >> test_case;

    for(int i = 0; i < test_case; i++) {
        int answer = 0;
        int N;
        int64_t C, D;
        std::priority_queue<int64_t> maximum_cap;
        
        std::cin >> N >> C >> D;
        if(C >= D) {
            std::cout << answer << std::endl;
            continue;
        }

        int64_t temp_dist, temp_cap;
        for(int j = 0; j < N; j++) {
            std::cin >> temp_dist >> temp_cap;
            data.push_back(std::make_pair(temp_dist, temp_cap));
        }
        //data.push_back(std::make_tuple(D, 0));

        sort(data.begin(), data.end()); // ascending order of distance first, capacity second

        for(int j = 0; j < N; j++) {
            if(C < data[j].first) {
                while(!maximum_cap.empty()) {
                    C += maximum_cap.top();
                    maximum_cap.pop();
                    answer++;
                    if(C >= data[j].first)
                        break;
                }
                if(maximum_cap.empty() && C < data[j].first) {
                    answer = -1;
                    break;
                }
            }
            
            maximum_cap.push(data[j].second);
            
            if(C >= D) {
                break;
            }
        }

        if(C < D) {
            while(!maximum_cap.empty()) {
                C += maximum_cap.top();
                maximum_cap.pop();
                answer++;
                if(C >= D)
                    break;
            }
            if(maximum_cap.empty() && C < D) {
                answer = -1;
            }
        }

        std::cout << answer << std::endl;

        data.clear();
    }

    return 0;
}