#include "AOC.h"

// dist, pos
typedef tuple<int, pii> rev_state;
namespace day20_ns {
vector<pii> dirs = {pii(-1, 0), pii(0, -1), pii(1, 0), pii(0, 1)};
};  // namespace day20_ns

bool inBounds(const input_t& inp, pii p) {
    return 0 < p.x && p.x < inp[0].size() - 1 && 0 < p.y &&
           p.y < inp.size() - 1;
}

chrono::time_point<std::chrono::steady_clock> day20(input_t& inp) {
    int p1(0), p2(0);

    pii start, end;
    for (int y = 0; y < inp.size(); y++) {
        for (int x = 0; x < inp[0].size(); x++) {
            switch (inp[y][x]) {
                case 'S':
                    start = pii(x, y);
                    break;
                case 'E':
                    end = pii(x, y);
                    break;
            }
        }
    }

    queue<rev_state> q;
    q.emplace(0, end);

    map<pii, int> rev_dist;
    while (!q.empty()) {
        auto [d, p] = q.front();
        q.pop();
        if (rev_dist.count(p)) continue;
        rev_dist[p] = d;
        for (auto& dir : day20_ns::dirs) {
            pii t(p.x + dir.x, p.y + dir.y);
            if (inp[t.y][t.x] != '#') {
                q.emplace(d + 1, t);
            }
        }
    }
    // cout << rev_dist[start] << endl;

    // need 2 clear spaces to jump regardless
    for (int y = 1; y < inp.size() - 1; y++) {
        for (int x = 1; x < inp.size() - 1; x++) {
            if (inp[y][x] != '#') {
                for (int dx = -20; dx <= 20; dx++) {
                    for (int dy = -20; dy <= 20; dy++) {
                        int dist = abs(dx) + abs(dy);
                        if (dist > 20) continue;
                        pii skip(x + dx, y + dy);
                        if (!inBounds(inp, skip)) continue;
                        if (inp[skip.y][skip.x] == '#') continue;
                        int timeSave =
                            rev_dist[pii(x, y)] - rev_dist[skip] - dist;
                        if (dist == 2 && (x == skip.x || y == skip.y) &&
                            timeSave >= 100) {
                            p1++;
                        }

                        // if (timeSave == 76) {
                        //     cout << "Shortcut from " << pii(x, y) << " to "
                        //          << skip << " saves " << timeSave << endl;
                        // }
                        // -2 because you need to cheat through wall

                        if (timeSave >= 100) {
                            p2++;
                        }
                    }
                }
            }
        }
    }

    // for (int y = 0; y < inp.size(); y++) {
    //     for (int x = 0; x < inp[0].size(); x++) {
    //         if (inp[y][x] == '#') {
    //             cout << "## ";
    //         } else {
    //             cout << (rev_dist[pii(x, y)] < 10 ? " " : "")
    //                  << rev_dist[pii(x, y)] << " ";
    //         }
    //     }
    //     cout << endl;
    // }

    auto done = chrono::steady_clock::now();
    cout << "[P1] " << p1 << "\n[P2] " << p2 << endl;
    return done;
}