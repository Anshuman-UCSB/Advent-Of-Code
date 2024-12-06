#include "AOC.h"

bool inBounds(const pii& pos, const pii& highbound) {
    return (0 <= pos.x && pos.x < highbound.x) &&
           (0 <= pos.y && pos.y < highbound.y);
}

pii rotate_dir(const pii& dir) { return pii(-dir.y, dir.x); }

bool part2(const input_t& inp, const set<pii>& blocks, const pii& high_bound,
           set<pair<pii, pii>>& looping_states, pii pos, pii dir,
           pii test_block) {
    set<pair<pii, pii>> seen;
    dir = rotate_dir(dir);

    while (inBounds(pos, high_bound)) {
        if (seen.count(make_pair(pos, dir)) ||
            looping_states.count(make_pair(pos, dir))) {
            looping_states.insert(seen.begin(), seen.end());
            return true;
        }
        seen.insert(make_pair(pos, dir));
        pii candidate(pos.x + dir.x, pos.y + dir.y);
        if (blocks.count(candidate) || candidate == test_block) {
            dir = rotate_dir(dir);
        } else {
            pos = candidate;
        }
    }
    return false;
}

chrono::time_point<std::chrono::steady_clock> day06(input_t& inp) {
    int p2(0);

    set<pii> blocks, visited;
    set<pair<pii, pii>> looping_states;
    pii dir(0, -1);
    pii pos;
    pii high_bound(inp[0].size(), inp.size());

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
    set<pii> p2parts;

    while (inBounds(pos, high_bound)) {
        visited.insert(pos);
        pii candidate(pos.x + dir.x, pos.y + dir.y);
        if (blocks.count(candidate)) {
            dir = rotate_dir(dir);
        } else {
            if (part2(inp, blocks, high_bound, looping_states, pos, dir,
                      candidate)) {
                p2parts.insert(candidate);
                p2++;
            }
            pos = candidate;
        }
    }
    cout << p2parts.size() << endl;
    // not 3324 lmao

    auto done = chrono::steady_clock::now();
    cout << "[P1] " << visited.size() << "\n[P2] " << p2 << endl;
    return done;
}