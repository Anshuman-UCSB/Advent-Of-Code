#include "AOC.h"

void DFS(int& p2ans, const input_t& inp, int x, int y, char level) {
    if (x < 0 || x >= inp[0].size() || y < 0 || y >= inp.size()) return;

    char val = inp[y][x];
    if (val != level) return;

    if (val == '0') {
        p2ans++;
        return;
    }

    DFS(p2ans, inp, x - 1, y, level - 1);
    DFS(p2ans, inp, x + 1, y, level - 1);
    DFS(p2ans, inp, x, y - 1, level - 1);
    DFS(p2ans, inp, x, y + 1, level - 1);
}

bool inbounds(pii point, const input_t& inp) {
    int x, y;
    tie(x, y) = point;
    return (x >= 0 && x < inp[0].size() && y >= 0 && y < inp.size());
}

void BFS(map<pii, int>& trailheads, const input_t& inp, pii peak) {
    pii p;
    char l;

    set<pii> seen;
    queue<pair<pii, char>> q({make_pair(peak, '9')});

    while (!q.empty()) {
        tie(p, l) = q.front();
        q.pop();
        // cout << p << "\t" << l << endl;
        if ((!inbounds(p, inp)) || (inp[p.y][p.x] != l) ||
            (!seen.insert(p).second)) {  // Make sure not in seen
            continue;
        }

        if (l == '0') {
            // cout << peak << " can see " << p << endl;
            trailheads[p]++;
            continue;
        }

        q.push(make_pair(pii(p.x + 1, p.y), l - 1));
        q.push(make_pair(pii(p.x, p.y + 1), l - 1));
        q.push(make_pair(pii(p.x - 1, p.y), l - 1));
        q.push(make_pair(pii(p.x, p.y - 1), l - 1));
    }
}

chrono::time_point<std::chrono::steady_clock> day10(input_t& inp) {
    int p1(0), p2(0);

    map<pii, int> trailheads;
    vector<pii> peaks;

    for (int y = 0; y < inp.size(); y++) {
        for (int x = 0; x < inp[0].size(); x++) {
            if (inp[y][x] == '0') {
                trailheads[pii(x, y)] = 0;
            } else if (inp[y][x] == '9') {
                peaks.emplace_back(x, y);
            }
        }
    }

    // cout << trailheads << endl;
    // cout << peaks << endl;

    for (auto& p : peaks) {
        BFS(trailheads, inp, p);
        DFS(p2, inp, p.x, p.y, '9');
        // cout << trailheads << endl;
    }
    for (auto& [k, v] : trailheads) {
        p1 += v;
    }

    auto done = chrono::steady_clock::now();
    cout << "[P1] " << p1 << "\n[P2] " << p2 << endl;
    return done;
}