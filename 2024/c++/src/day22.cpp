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

typedef tuple<int, int, int, int> quad;
void process(ull& n, map<quad, ull>& values) {
    // vector<set<quad>> bins(10);
    deque<int> seq;
    set<quad> seen;

    int val = n % 10, delta;
    for (int i = 0; i < 2000; i++) {
        n = evolve(n);
        delta = n % 10 - val;
        val = n % 10;

        seq.push_back(delta);
        if (seq.size() >= 5) seq.pop_front();
        if (seq.size() != 4) continue;

        // cout << seq << "\t" << val << endl;
        quad t = make_tuple(seq[0], seq[1], seq[2], seq[3]);

        if (seen.insert(t).second == false) continue;

        // bins[val].insert(t);
        values[t] += val;
    }
    // for (int i = 0; i < 10; i++) {
    //     cout << "Val " << i << ": " << bins[i] << endl;
    // }
    // cout << bins << endl;
}

chrono::time_point<std::chrono::steady_clock> day22(input_t& inp) {
    ull p1(0), p2(0);

    map<quad, ull> val;
    for (auto& l : inp) {
        ull n = stoi(l);
        process(n, val);
        p1 += n;
    }

    for (auto& [k, v] : val) {
        p2 = max(p2, v);
    }

    auto done = chrono::steady_clock::now();
    cout << "[P1] " << p1 << "\n[P2] " << p2 << endl;
    return done;
}