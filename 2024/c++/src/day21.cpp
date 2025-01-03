#include "AOC.h"
// 10 = A
map<int, pii> pos = {{0, pii(1, 3)}, {1, pii(0, 2)}, {2, pii(1, 2)},
                     {3, pii(2, 2)}, {4, pii(0, 1)}, {5, pii(1, 1)},
                     {6, pii(2, 1)}, {7, pii(0, 0)}, {8, pii(1, 0)},
                     {9, pii(2, 0)}, {10, pii(2, 3)}};

string get_paths(int from, int to) {
    const pii fp(pos[from]), tp(pos[to]);
    string out;
    if (fp.y == tp.y) {
        for (int i = fp.x; i < tp.x; i++) {
            out += ">";
        }
        for (int i = fp.x; i > tp.x; i--) {
            out += "<";
        }
        return out;
    }
    if (fp.x == tp.x) {
        string out;
        for (int i = fp.y; i < tp.y; i++) {
            out += "v";
        }
        for (int i = fp.y; i > tp.y; i--) {
            out += "^";
        }
        return out;
    }
    if (fp.y > tp.y) {
        for (int i = fp.y; i > tp.y; i--) {
            out += "^";
        }
        for (int i = fp.x; i < tp.x; i++) {
            out += ">";
        }
        for (int i = fp.x; i > tp.x; i--) {
            out += "<";
        }
        return out;
    }
    if (fp.y < tp.y) {
        for (int i = fp.x; i < tp.x; i++) {
            out += ">";
        }
        for (int i = fp.x; i > tp.x; i--) {
            out += "<";
        }
        for (int i = fp.y; i < tp.y; i++) {
            out += "v";
        }
        return out;
    }
    return "?";
}

vector<string> phase1(string code) {
    vector<vector<string>> paths;
    for (int f = 0; f <= 10; f++) {
        paths.emplace_back();
        for (int t = 0; t <= 10; t++) {
            paths.back().push_back(get_paths(f, t));
        }
    }
    cout << paths << endl;
    return vector<string>();
}

chrono::time_point<std::chrono::steady_clock> day21(input_t& inp) {
    int p1(0), p2(0);
    phase1("029A");

    auto done = chrono::steady_clock::now();
    cout << "[P1] " << p1 << "\n[P2] " << p2 << endl;
    return done;
}

/*
+---+---+---+
| 7 | 8 | 9 |
+---+---+---+
| 4 | 5 | 6 |
+---+---+---+
| 1 | 2 | 3 |
+---+---+---+
    | 0 | A |
    +---+---+

    +---+---+
    | ^ | A |
+---+---+---+
| < | v | > |
+---+---+---+
*/