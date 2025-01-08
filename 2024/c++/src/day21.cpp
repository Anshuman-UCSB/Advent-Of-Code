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

map<pair<char, char>, string> keypad_cache;
string calc_step(char from, char to) {
    if (keypad_cache.count(make_pair(from, to))) {
        return keypad_cache[make_pair(from, to)];
    }
    string full_str = solve_pad(KEYPAD, string(1, from) + string(1, to));
    string delta_str = full_str.substr(full_str.find('A') + 1);

    keypad_cache[make_pair(from, to)] = delta_str;
    return delta_str;
}

map<tuple<int, char, char>, ull> day21_cache;
ull required_num_chars(int level, char f, char t) {
    if (level == 0) {
        return 1;
    }
    if (day21_cache.count(make_tuple(level, f, t))) {
        return day21_cache[make_tuple(level, f, t)];
    }

    string seq = calc_step(f, t);
    ull req = 0;
    char prev = 'A';
    for (auto c : seq) {
        req += required_num_chars(level - 1, prev, c);
        prev = c;
    }

    day21_cache[make_tuple(level, f, t)] = req;
    return req;
}

ull solve(string target, int level) {
    ull ans = 0;
    string l0_keypad = solve_pad(NUMPAD, target);

    char prev = 'A';
    for (auto c : l0_keypad) {
        ans += required_num_chars(level, prev, c);
        prev = c;
    }

    return ans * stoi(target.substr(0, 3));
}

chrono::time_point<std::chrono::steady_clock> day21(input_t& inp) {
    ull p1(0), p2(0);
    for (auto& l : inp) {
        p1 += solve(l, 2);
        p2 += solve(l, 25);
    }

    auto done = chrono::steady_clock::now();
    cout << "[P1] " << p1 << "\n[P2] " << p2 << endl;
    return done;
}