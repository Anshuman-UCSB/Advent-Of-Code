#include "AOC.h"

typedef tuple<int, int, int> state;

int canSolve(input_t& inp, int bytes) {
    int GRIDSIZE = (inp.size() < 100 ? 6 : 70) + 1;
    vector<vector<bool>> grid(GRIDSIZE, vector<bool>(GRIDSIZE));
    for (int i = 0; i < (bytes); i++) {
        stringstream ss(inp[i]);
        int x, y;
        char t;
        ss >> x >> t >> y;
        grid[y][x] = 1;
    }

    priority_queue<state, vector<state>, greater<state>> pq;
    pq.emplace(0, 0, 0);
    set<pii> seen;
    int solve = -1;
    while (!pq.empty()) {
        auto [dist, x, y] = pq.top();
        pq.pop();
        if (grid[y][x]) continue;
        if (seen.emplace(x, y).second == false) continue;
        // cout << dist << ", " << pii(x, y) << endl;
        if (x == GRIDSIZE - 1 && y == GRIDSIZE - 1) {
            solve = dist;
            break;
        }
        if (x > 0) {
            pq.emplace(dist + 1, x - 1, y);
        }
        if (x < GRIDSIZE - 1) {
            pq.emplace(dist + 1, x + 1, y);
        }
        if (y > 0) {
            pq.emplace(dist + 1, x, y - 1);
        }
        if (y < GRIDSIZE - 1) {
            pq.emplace(dist + 1, x, y + 1);
        }
    }
    // for (auto& r : grid) {
    //     for (auto v : r) {
    //         cout << (v ? '#' : '.');
    //     }
    //     cout << endl;
    // }
    return solve;
}

chrono::time_point<std::chrono::steady_clock> day18(input_t& inp) {
    int p1(canSolve(inp, 1024));

    int l(0), h(inp.size()), m;
    while (l < h) {
        m = (l + h) >> 1;
        // cout << l << "\t" << m << "\t" << h << endl;
        if (canSolve(inp, m) != -1) {
            l = m + 1;
        } else {
            h = m;
        }
    }

    string p2 = inp[m];

    auto done = chrono::steady_clock::now();
    cout << "[P1] " << p1 << "\n[P2] " << p2 << endl;
    return done;
}