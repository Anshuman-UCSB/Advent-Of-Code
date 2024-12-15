#include "AOC.h"

ull solve(int a1, int a2, int b1, int b2, ull c1, ull c2, bool part1) {
    const ull TARGET = 10000000000000;
    if (!part1) {
        c1 += TARGET;
        c2 += TARGET;
    }

    ll det = a1 * b2 - b1 * a2;
    if (det != 0) {
        ll numA = (c1 * b2 - b1 * c2);
        ll numB = (a1 * c2 - c1 * a2);
        if (numA % det != 0 || numB % det != 0) {
            return 0;
        }
        ll a = numA / det;
        ll b = numB / det;

        if (part1 && (a > 100 || b > 100)) {
            return 0;
        }
        return a * 3 + b;
    } else {
        return 0;
    }
}

chrono::time_point<std::chrono::steady_clock> day13(input_t& inp) {
    ull p1(0), p2(0);

    int ax, ay, bx, by, tx, ty;
    char _;
    string tmp;

    for (int i = 0; i < inp.size(); i += 4) {
        stringstream ss(inp[i]);
        ss >> tmp >> tmp >> _ >> ax >> _ >> _ >> _ >> ay;
        ss = stringstream(inp[i + 1]);
        ss >> tmp >> tmp >> _ >> bx >> _ >> _ >> _ >> by;
        ss = stringstream(inp[i + 2]);
        ss >> tmp >> _ >> _ >> tx >> _ >> _ >> _ >> ty;
        p1 += solve(ax, ay, bx, by, tx, ty, true);
        p2 += solve(ax, ay, bx, by, tx, ty, false);
    }

    auto done = chrono::steady_clock::now();
    cout << "[P1] " << p1 << "\n[P2] " << p2 << endl;
    return done;
}

// 18446743665687658496 Too high
// 18446743878288539648 Too high