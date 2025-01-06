#include "AOC.h"

// input, numpad pos, keypad pos 1, keypad pos 2, output
typedef tuple<string, pii, pii, pii, string> state;

const string NUMPAD[] = {
    "#####", "#789#", "#456#", "#123#", "##0A#", "#####",
};
const string KEYPAD[] = {
    "#####",
    "##^A#",
    "#<v>#",
    "#####",
};
map<char, pii> dirs = {{'>', pii(1, 0)},
                       {'<', pii(-1, 0)},
                       {'^', pii(0, -1)},
                       {'v', pii(0, 1)},
                       {'A', pii(0, 0)}};

pii stepDir(pii pos, pii dir) { return pii(pos.x + dir.x, pos.y + dir.y); }

char getChar(const string mapping[], const pii pos) {
    // cout << npos << endl;
    return mapping[pos.y][pos.x];
}

pair<pii, char> sim(const string sim_mapping[], pii pos, char action) {
    pii newpos = stepDir(pos, dirs[action]);
    char c = getChar(sim_mapping, newpos);
    if (c == '#') return make_pair(pii(), '#');
    if (action == 'A') return make_pair(pos, c);
    return make_pair(newpos, '\0');
}

string solve_p1(string target) {
    queue<state> q;
    q.emplace("", pii(3, 1), pii(3, 1), pii(3, 4), "");
    while (!q.empty()) {
        auto [inp, kpos2, kpos1, numpos, out] = q.front();
        cout << inp << ',' << kpos2 << ',' << kpos1 << ',' << numpos << ','
             << out << endl;
        q.pop();

        if (!target.starts_with(out)) continue;
        for (auto& [k, v] : dirs) {
            string new_out = out;
            pii nkpos2(kpos2), nkpos1(kpos1), nnumpos(numpos);
            char na2, na1, nout;
            tie(nkpos2, na2) = sim(KEYPAD, kpos2, k);
            if (na2 == '#') continue;  // if leads to invalid
            if (na2) {
                tie(nkpos1, na1) = sim(KEYPAD, kpos1, na2);
                if (na1 == '#') continue;
                if (na1) {
                    auto [nnumpos, nout] = sim(NUMPAD, numpos, na1);
                    if (nout == '#') continue;  // if leads to invalid
                    if (nout) {
                        new_out.push_back(nout);
                    }
                }
            }
            q.emplace(inp + k, nkpos2, nkpos1, nnumpos, new_out);
        }
    }
    return "fail";
}

chrono::time_point<std::chrono::steady_clock> day21(input_t& inp) {
    int p1(0), p2(0);
    for (auto& l : inp) {
        cout << l << ": " << solve_p1(l) << endl;
    }

    auto done = chrono::steady_clock::now();
    cout << "[P1] " << p1 << "\n[P2] " << p2 << endl;
    return done;
}