#include "AOC.h"

ull countDigits(ull i) { return i > 0 ? (ull)log10((double)i) + 1 : 1; }

map<ull, ull> iterate(const map<ull, ull>& nums) {
    map<ull, ull> next;

    for (auto& [n, c] : nums) {
        ull digits = countDigits(n);
        if (n == 0) {
            next[1] += c;
        } else if (digits % 2 == 0) {
            next[n / ((ull)pow(10, digits / 2))] += c;
            next[n % ((ull)pow(10, digits / 2))] += c;
        } else {
            next[n * 2024] += c;
        }
    }

    return next;
}

ull score(const map<ull, ull>& nums) {
    ull out(0);
    for (const auto& [c, v] : nums) {
        out += v;
    }
    return out;
}

chrono::time_point<std::chrono::steady_clock> day11(input_t& inp) {
    ull p1(0), p2(0);
    auto done = chrono::steady_clock::now();

    ull t;
    stringstream ss(inp[0]);
    map<ull, ull> nums;

    while (ss >> t) {
        nums[t]++;
    }

    // cout << nums << endl;
    for (ull i = 1; i <= 25; i++) {
        nums = iterate(nums);
    }
    p1 = score(nums);

    for (ull i = 26; i <= 75; i++) {
        nums = iterate(nums);
    }
    p2 = score(nums);

    cout << "[P1] " << p1 << "\n[P2] " << p2 << endl;
    return done;
}