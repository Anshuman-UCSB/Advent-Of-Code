#include "AOC.h"

void prune(ull& num) { num %= 16777216; }
ull evolve(ull num) {
    num ^= num << 6;
    prune(num);

    num ^= num >> 5;
    prune(num);

    num ^= num << 11;
    prune(num);

    return num;
}

ull evolve_iters(ull initial, int rounds) {
    while (rounds--) {
        initial = evolve(initial);
    }
    return initial;
}

chrono::time_point<std::chrono::steady_clock> day22(input_t& inp) {
    ull p1(0), p2(0);

    for (auto& l : inp) {
        p1 += evolve_iters(stoi(l), 2000);
    }

    auto done = chrono::steady_clock::now();
    cout << "[P1] " << p1 << "\n[P2] " << p2 << endl;
    return done;
}