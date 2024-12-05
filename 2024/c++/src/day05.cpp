#include "AOC.h"

int part1(vector<int>& nums, set<int>& consider, map<int, set<int>>& deps) {
    for (int i = 0; i < nums.size(); i++) {
        int cur = nums[i];
        for (auto& d : deps[cur]) {
            if (consider.count(d)) {
                for (int j = i + 1; j < nums.size(); j++) {
                    if (nums[j] == d) {
                        return 0;
                    }
                }
            }
        }
    }
    return nums[nums.size() / 2];
}

bool areDisjoint(const std::set<int>& set1, const std::set<int>& set2) {
    std::vector<int> intersection;
    std::set_intersection(set1.begin(), set1.end(), set2.begin(), set2.end(),
                          std::back_inserter(intersection));
    return intersection.empty();
}

int part2(set<int>& consider, map<int, set<int>>& deps) {
    int targetInd = consider.size() / 2;
    for (int i = 0; i <= targetInd; i++) {
        for (auto& v : consider) {
            if (areDisjoint(deps[v], consider)) {
                if (i == targetInd) return v;
                consider.erase(v);
                break;
            }
        }
    }
    return 0;
}

chrono::time_point<std::chrono::steady_clock> day05(input_t& inp) {
    int p1(0), p2(0);

    map<int, set<int>> deps;
    int i, a, b;
    for (i = 0; inp[i] != ""; i++) {
        sscanf(inp[i].c_str(), "%d|%d", &a, &b);
        deps[b].emplace(a);
    }
    for (i++; i < inp.size(); i++) {  // skipping null line
        const string& line = inp[i];
        stringstream ss(line);
        vector<int> nums;
        set<int> consider;
        string token;
        while (getline(ss, token, ',')) {
            nums.emplace_back(stoi(token));
            consider.emplace(nums.back());
        }
        int p1res = part1(nums, consider, deps);
        p1 += p1res;
        if (p1res == 0) {
            p2 += part2(consider, deps);
        }
    }

    auto done = chrono::steady_clock::now();
    cout << "[P1] " << p1 << "\n[P2] " << p2 << endl;
    return done;
}