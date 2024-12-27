#include "AOC.h"

typedef tuple<int, int, int, int> state;
int dx[4] = {0, 1, 0, -1};
int dy[4] = {-1, 0, 1, 0};

ull solve_p1(input_t& grid) {
    priority_queue<state, vector<state>, greater<state>> pq;
    set<tuple<int, int, int>> seen;

    int gX(grid[1].size() - 2), gY(1);
    int dist, x, y, dir, tdir;

    // Start off with no direction penalty
    pq.emplace(0, 1, grid.size() - 2, 1);

    while (!pq.empty()) {
        tie(dist, x, y, dir) = pq.top();
        if (seen.insert(make_tuple(x, y, dir)).second) {
            // cout << dist << ", " << x << ", " << y << ", " << dir << endl;
            if (x == gX && y == gY) return dist;

            tdir = (dir + 1) % 4;
            if (grid[y + dy[tdir]][x + dx[tdir]] != '#') {
                pq.emplace(dist + 1000, x, y, tdir);
            }
            // Avoiding undefined negative mod
            tdir = (dir + 3) % 4;
            if (grid[y + dy[tdir]][x + dx[tdir]] != '#') {
                pq.emplace(dist + 1000, x, y, tdir);
            }

            if (grid[y + dy[dir]][x + dx[dir]] != '#') {
                pq.emplace(dist + 1, x + dx[dir], y + dy[dir], dir);
            }
        }
        pq.pop();
    }

    return -1;
}

int solve_p2(input_t& inp, int target) {
    set<pii> valid;

    return 1;
}

chrono::time_point<std::chrono::steady_clock> day16(input_t& inp) {
    int p1(solve_p1(inp)), p2(solve_p2(inp, p1));

    auto done = chrono::steady_clock::now();
    cout << "[P1] " << p1 << "\n[P2] " << p2 << endl;
    return done;
}