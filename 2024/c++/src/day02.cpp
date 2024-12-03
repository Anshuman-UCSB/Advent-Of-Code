#include "AOC.h"

bool isSafe(const vector<int> &nums, int skip = -1) {
    int increasing(-1), diff, last(-1);
    for (int i = 0; i < nums.size(); i++) {
        if (i == skip) continue;
        if (last != -1 && increasing == -1) {
            increasing = nums[i] > last;
        }
        if (last != -1) {
            diff = nums[i] - last;
            if (!(diff && (diff > 0 == increasing) && (abs(diff) >= 1) &&
                  (abs(diff) <= 3))) {
                return false;
            }
        }
        last = nums[i];
    }
    return true;
}

chrono::time_point<std::chrono::steady_clock> day02(input_t &inp) {
    int p1(0), p2(0);

    for (auto &line : inp) {
        istringstream iss(line);
        vector<int> nums;
        int num;
        while (iss >> num) nums.push_back(num);
        p1 += isSafe(nums);
        for (int i = 0; i < nums.size(); i++) {
            if (isSafe(nums, i)) {
                p2++;
                break;
            }
        }
    }

    auto done = chrono::steady_clock::now();
    cout << "[P1] " << p1 << "\n[P2] " << p2 << endl;
    return done;
}