#include "AOC.h"

// dist, point, direction, from, from direction
typedef tuple<int, pii, int, pii, int> state;
class FromCache {
   public:
    int bestDist;
    set<pair<pii, int>> from;
    FromCache() { bestDist = INT32_MAX; }
    bool reg(pii p, int fromdir, int dist) {
        if (dist < bestDist) {
            bestDist = dist;
            from.clear();
            from.emplace(p, fromdir);
        } else if (dist == bestDist) {
            from.emplace(p, fromdir);
        } else {
            return false;
        }
        return true;
    }
    bool wasSeen() { return bestDist < INT32_MAX; }
};

char at(const input_t& inp, const pii& p) { return inp[p.y][p.x]; }
pii step(const pii& p, int dir) {
    const int dx[] = {0, 1, 0, -1};
    const int dy[] = {-1, 0, 1, 0};
    return pii(p.x + dx[dir], p.y + dy[dir]);
}

chrono::time_point<std::chrono::steady_clock> day16(input_t& inp) {
    int p2(0), best(INT32_MAX);
    pii start(1, inp.size() - 2), end(inp[1].size() - 2, 1);
    priority_queue<state, vector<state>, greater<state>> pq;
    pq.emplace(0, start, 1, pii(-1, -1), -1);

    map<pair<pii, int>, FromCache> fromCache;

    while (!pq.empty()) {
        auto [dist, p, dir, from, fromdir] = pq.top();
        auto pos_state = make_pair(p, dir);

        fromCache[pos_state].reg(from, fromdir, dist);
        // cout << fromCache[pos_state].bestDist << endl;
        if (dist <= best && dist <= fromCache[pos_state].bestDist) {
            // cout << dist << "\t" << p << dir << "\tfrom: " << from << fromdir
            //      << '\t' << best << endl;
            if (p == end) {
                if (best == INT32_MAX) {
                    best = dist;
                }
            } else {
                if (at(inp, step(p, dir)) != '#') {
                    pq.emplace(dist + 1, step(p, dir), dir, p, dir);
                }
                if (at(inp, step(p, (dir + 1) % 4)) != '#') {
                    pq.emplace(dist + 1000, p, (dir + 1) % 4, p, dir);
                }
                if (at(inp, step(p, (dir + 3) % 4)) != '#') {
                    pq.emplace(dist + 1000, p, (dir + 3) % 4, p, dir);
                }
            }
        }
        pq.pop();
    }

    queue<pair<pii, int>> q;
    q.emplace(end, 0);
    q.emplace(end, 1);
    set<pii> p2set;
    while (!q.empty()) {
        auto tmp = q.front();
        // cout << tmp << endl;
        q.pop();
        if (tmp.first.x == -1) continue;
        p2set.insert(tmp.first);
        for (auto& v : fromCache[tmp].from) {
            q.push(v);
        }
    }
    p2 = p2set.size();

    // for (auto& p : p2set) {
    //     inp[p.y][p.x] = 'O';
    // }
    // for (auto& r : inp) {
    //     cout << r << endl;
    // }

    // cout << fromCache[make_pair(pii(5, 7), 0)].from
    //      << fromCache[make_pair(pii(5, 7), 0)].bestDist << endl;

    auto done = chrono::steady_clock::now();
    cout << "[P1] " << best << "\n[P2] " << p2 << endl;
    return done;
}