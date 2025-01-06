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
    return mapping[pos.y][pos.x];
}

// returns perfect match, partial match, and output string
tuple<bool, bool, string> checkMatch(const string MAP[], string inp,
                                     string out) {
    string gen_string = "";
    pii pos = (MAP == NUMPAD) ? pii(3, 4) : pii(3, 1);
    for (auto i : inp) {
        // cout << i << ": ";
        if (i == 'A') {
            char c = getChar(MAP, pos);
            gen_string.push_back(c);
            // cout << gen_string << endl;
            if (!out.starts_with(gen_string)) {
                return make_tuple(false, false, gen_string);
            }
        } else {
            pos = stepDir(pos, dirs[i]);
            // cout << pos << endl;
            if (getChar(MAP, pos) == '#')
                return make_tuple(false, false, gen_string);
        }
    }

    return make_tuple(gen_string == out, true, gen_string);
}

string solve_pad(const string PAD[], string target) {
    queue<string> q;
    size_t farthest = 0;
    q.emplace("");
    while (!q.empty()) {
        string inp = q.front();
        q.pop();
        auto [full, partial, gen] = checkMatch(PAD, inp, target);
        if (!partial) continue;
        farthest = max(gen.size(), farthest);
        if (gen.size() < farthest) continue;
        // cout << inp << ": " << make_tuple(full, partial, gen) << endl;
        if (full) return inp;
        if (partial) {
            for (auto& c : {'A', '<', '^', 'v', '>'}) {
                q.emplace(inp + c + c + c);
                q.emplace(inp + c + c);
                q.emplace(inp + c);
            }
        }
    }
    return "FAIL";
}

ull solve_p1(string target) {
    string numpad_sol = solve_pad(NUMPAD, target);
    // cout << numpad_sol << endl;

    string kp1_sol = solve_pad(KEYPAD, numpad_sol);
    // cout << kp1_sol << endl;

    string kp2_sol = solve_pad(KEYPAD, kp1_sol);
    // cout << kp2_sol << endl;

    return kp2_sol.size() * stoi(target.substr(0, 3));
}

chrono::time_point<std::chrono::steady_clock> day21(input_t& inp) {
    ull p1(0), p2(0);
    for (auto& l : inp) {
        p1 += solve_p1(l);
    }

    auto done = chrono::steady_clock::now();
    cout << "[P1] " << p1 << "\n[P2] " << p2 << endl;
    return done;
}