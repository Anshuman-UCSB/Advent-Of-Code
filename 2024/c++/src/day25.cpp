#include "AOC.h"

typedef vector<int> combo;

bool fits(const combo& lock, const combo& key) {
    for (int i = 0; i < 5; i++) {
        if (lock[i] + key[i] > 5) return false;
    }
    return true;
}

chrono::time_point<std::chrono::steady_clock> day25(input_t& inp) {
    int p1(0);

    vector<combo> locks, keys;
    for (int i = 0; i < inp.size(); i += 8) {
        bool lock = inp[i][0] == '#';
        combo c;
        for (int x = 0; x < 5; x++) {
            c.push_back(0);
            for (int y = 1; y < 6; y++) {
                c.back() += inp[y + i][x] == '#';
            }
        }
        (lock ? locks : keys).push_back(c);
    }

    for (auto& l : locks) {
        for (auto& k : keys) {
            p1 += fits(l, k);
        }
    }

    auto done = chrono::steady_clock::now();
    cout << "[P1] " << p1 << endl;
    return done;
}