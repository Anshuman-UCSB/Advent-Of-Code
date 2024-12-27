#include "AOC.h"

typedef tuple<int, int, int, int> state;
// no-distance state
typedef tuple<int, int, int> ndstate;
// with-from state
typedef tuple<int, int, int, int, ndstate> wfstate;

int dx[4] = {0, 1, 0, -1};
int dy[4] = {-1, 0, 1, 0};

ull solve_p1(input_t& grid, map<ndstate, pair<int, set<ndstate>>>& revPath) {
    priority_queue<wfstate, vector<wfstate>, greater<wfstate>> pq;
    ndstate nd, fnd;

    int gX(grid[1].size() - 2), gY(1);
    int tdir;

    // Start off with no direction penalty
    pq.emplace(0, 1, grid.size() - 2, 1, make_tuple(-1, -1, -1));

    int bestDist = INT32_MAX;

    while (!pq.empty()) {
        auto [dist, x, y, dir, fnd] = pq.top();
        nd = ndstate(x, y, dir);

        if (dist > bestDist) {
            pq.pop();
            continue;
        }

        if (revPath.count(nd) == 0) {
            revPath[nd].first = dist;
            assert(revPath[nd].second.empty());
            revPath[nd].second.insert(fnd);
        } else {
            // Should not later be finding better paths
            assert(dist >= revPath[nd].first);
            if (dist == revPath[nd].first) {
                // Another way to get here
                revPath[nd].second.insert(fnd);
            }
            pq.pop();
            continue;
        }
        if (bestDist == INT32_MAX && x == gX && y == gY) {
            bestDist = dist;
            continue;
        }

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

    return bestDist;
}

pii step(const pii& p, const int dir) {
    return pii(p.x + dx[dir], p.y + dy[dir]);
}

int solve_p2(input_t& grid, int target) {
    set<pii> valid;

    return valid.size();
}

chrono::time_point<std::chrono::steady_clock> day16(input_t& inp) {
    map<ndstate, pair<int, set<ndstate>>> revPath;
    int p1(solve_p1(inp, revPath)), p2(solve_p2(inp, p1));

    auto done = chrono::steady_clock::now();
    cout << "[P1] " << p1 << "\n[P2] " << p2 << endl;
    return done;
}