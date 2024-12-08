#include "AOC.h"

ull concat(ull a, ull b) { return a * pow(10, 1 - int(-log10(b))) + b; }

bool solve(const ull target, const vector<ull>& nums, bool p1,
           ull running_total = 0, ull pos = 0) {
    if (pos == nums.size()) {
        return running_total == target;
    }
    if (running_total > target) {
        return false;
    }
    return (!p1 && solve(target, nums, p1, concat(running_total, nums[pos]),
                         pos + 1)) ||
           solve(target, nums, p1, running_total * nums[pos], pos + 1) ||
           solve(target, nums, p1, running_total + nums[pos], pos + 1);
}

chrono::time_point<std::chrono::steady_clock> day07(input_t& inp) {
    ull p1(0), p2(0);
    ull target, tmp;
    char junk;

    for (const auto& l : inp) {
        stringstream ss(l);
        ss >> target >> junk;
        vector<ull> nums;
        while (ss >> tmp) {
            nums.push_back(tmp);
        }
        p1 += target * solve(target, nums, true);
        p2 += target * solve(target, nums, false);
    }

    auto done = chrono::steady_clock::now();
    cout << "[P1] " << p1 << "\n[P2] " << p2 << endl;
    return done;
}