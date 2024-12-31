#include "AOC.h"

ull can_build(string line, const vector<string>& components) {
    vector<ull> DP(line.size() + 1);
    DP[0] = true;

    // cout << line << endl;
    for (int i = 0; i < DP.size(); i++) {
        if (DP[i] == false) continue;
        // cout << "i: " << i << endl;
        for (auto& c : components) {
            if (line.substr(i, c.size()) == c) {
                DP[i + c.size()] += DP[i];
                // cout << "Could make " << c << "\t" << DP << endl;
            }
        }
    }

    // cout << DP << endl;

    return DP.back();
}

chrono::time_point<std::chrono::steady_clock> day19(input_t& inp) {
    ull p1(0), p2(0);

    stringstream ss(inp[0]);
    vector<string> components;
    string tmp;
    while (ss >> tmp) {
        if (tmp.back() == ',') {
            tmp.pop_back();
        }
        components.push_back(tmp);
    }
    // cout << components << endl;
    for (int i = 2; i < inp.size(); i++) {
        ull ways = can_build(inp[i], components);
        // cout << inp[i] << " can be made in " << ways << " ways." << endl;
        p1 += (ways != 0);
        p2 += ways;
    }

    auto done = chrono::steady_clock::now();
    cout << "[P1] " << p1 << "\n[P2] " << p2 << endl;
    return done;
}