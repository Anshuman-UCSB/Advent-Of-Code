#include "AOC.h"

bool inBounds(const pii& pos, const pii& highbound) {
    return (0 <= pos.x && pos.x < highbound.x) &&
           (0 <= pos.y && pos.y < highbound.y);
}

pii rotate_dir(const pii& dir) { return pii(-dir.y, dir.x); }

set<pii> check_loop(const input_t& inp, const set<pii>& blocks, pii pos,
                    pii dir, pii test_block = pii(-1, -1)) {
    set<pair<pii, pii>> seen;
    set<pii> visited;
    pii high_bound(inp[0].size(), inp.size());

    while (inBounds(pos, high_bound)) {
        if (seen.count(make_pair(pos, dir))) {
            return set<pii>();
        }
        seen.insert(make_pair(pos, dir));
        visited.insert(pos);
        pii candidate(pos.x + dir.x, pos.y + dir.y);
        if (blocks.count(candidate) || candidate == test_block) {
            dir = rotate_dir(dir);
        } else {
            pos = candidate;
        }
    }
    return visited;
}

chrono::time_point<std::chrono::steady_clock> day06(input_t& inp) {
    int p1, p2(0);

    set<pii> blocks, p1visited;
    pii dir(0, -1);
    pii pos;

    for (int y = 0; y < inp.size(); y++) {
        for (int x = 0; x < inp[y].size(); x++) {
            if (inp[y][x] == '#') {
                blocks.emplace(x, y);
            }
            if (inp[y][x] == '^') {
                pos = pii(x, y);
            }
        }
    }

    p1visited = check_loop(inp, blocks, pos, dir);
    p1 = p1visited.size();

    for (const auto& spot : p1visited) {
        if (check_loop(inp, blocks, pos, dir, spot).empty()) {
            p2++;
        }
    }

    auto done = chrono::steady_clock::now();
    cout << "[P1] " << p1 << "\n[P2] " << p2 << endl;
    return done;
}