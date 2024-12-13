#include "AOC.h"

bool almostInt(double n) {
    int t = round(n);
    double diff = n - t;
    const double EPS = .05;
    return abs(diff) < EPS;
}

int part1(int a1, int a2, int b1, int b2, int c1, int c2) {
    double det = a1 * b2 - b1 * a2;
    if (det != 0) {
        double a = (c1 * b2 - b1 * c2) / det;
        double b = (a1 * c2 - c1 * a2) / det;
        // cout << a << " & " << b << '\t' << c1 << ", " << c2;
        int mult = 1;

        double baseA(a), baseB(b);
        while (!almostInt(a) || !almostInt(b)) {
            a += baseA;
            b += baseB;
            if (a > 100 || b > 100 || a < 0 || b < 0) {
                cout << "Could not make, invalid nums" << endl;
                return 0;
            }
        }
        if (a > 100 || b > 100 || a < 0 || b < 0) {
            cout << "Could not make, invalid nums" << endl;
            return 0;
        }
        cout << "Adding " << a << "*3 and " << b << " tokens" << endl;
        return a * 3 + b;
    } else {
        cout << "Failed" << endl;
        return 0;
    }
}

chrono::time_point<std::chrono::steady_clock> day13(input_t& inp) {
    int p1(0), p2(0);

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
        p1 += part1(ax, ay, bx, by, tx, ty);
    }

    auto done = chrono::steady_clock::now();
    cout << "[P1] " << p1 << "\n[P2] " << p2 << endl;
    return done;
}