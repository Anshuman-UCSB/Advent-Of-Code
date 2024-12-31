#include "AOC.h"

// dist, pos
typedef tuple<int, pii> rev_state;
vector<pii> dirs = {pii(-1, 0), pii(0, -1), pii(1, 0), pii(0, 1)};

bool inBounds(const input_t& inp, pii p) {
    return 0 <= p.x && p.x < inp[0].size() && 0 <= p.y && p.y < inp.size();
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
        for (auto& dir : dirs) {
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
                for (const auto& dir : dirs) {
                    pii step2(pii(x + dir.x * 2, y + dir.y * 2));
                    if (inp[y + dir.y][x + dir.x] == '#' &&
                        inBounds(inp, step2) && inp[step2.y][step2.x] != '#') {
                        // skip found
                        int timeSave =
                            rev_dist[pii(x, y)] -
                            rev_dist[pii(x + dir.x * 2, y + dir.y * 2)] - 2;

                        // -2 because you need to cheat through wall
                        // if (timeSave >= 0) {
                        //     cout << "Shortcut from " << pii(x, y) << " to "
                        //          << pii(x + dir.x * 2, y + dir.y * 2)
                        //          << " saves " << timeSave << endl;
                        // }

                        if (timeSave >= 100) {
                            p1++;
                        }
                    }
                }
            }
        }
    }

    // for (int y = 0; y < inp.size(); y++) {
    //     for (int x = 0; x < inp[0].size(); x++) {
    //         if (inp[y][x] == '#') {
    //             cout << '#';
    //         } else {
    //             cout << rev_dist[pii(x, y)] % 10;
    //         }
    //     }
    //     cout << endl;
    // }

    auto done = chrono::steady_clock::now();
    cout << "[P1] " << p1 << "\n[P2] " << p2 << endl;
    return done;
}