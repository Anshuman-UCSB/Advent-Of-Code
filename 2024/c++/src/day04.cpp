#include "AOC.h"

bool check_match(const input_t& inp, int x, int y, int d) {
    int dx[] = {0, 1, 0, -1, 1, 1, -1, -1};
    int dy[] = {1, 0, -1, 0, 1, -1, 1, -1};
    int w(inp.size()), h(inp[0].size());
    string target = "XMAS";

    for (int i = 0; i < 4; i++) {
        int ty = y + dy[d] * i;
        int tx = x + dx[d] * i;
        if (ty >= h || ty < 0) return false;
        if (tx >= h || tx < 0) return false;
        if (inp[ty][tx] != target[i]) {
            return false;
        }
    }
    return true;
}

bool check_match_p2(const input_t& inp, int x, int y) {
    int w(inp.size()), h(inp[0].size());
    if (x < 1 || x >= w - 1) return false;
    if (y < 1 || y >= h - 1) return false;
    if (inp[y][x] != 'A') return false;
    string corners;
    corners += inp[y - 1][x - 1];
    corners += inp[y - 1][x + 1];
    corners += inp[y + 1][x + 1];
    corners += inp[y + 1][x - 1];
    return (corners == "MMSS" || corners == "MSSM" || corners == "SSMM" ||
            corners == "SMMS");
}

chrono::time_point<std::chrono::steady_clock> day04(input_t& inp) {
    int p1(0), p2(0);

    int w(inp.size()), h(inp[0].size());

    for (int y = 0; y < h; y++) {
        for (int x = 0; x < w; x++) {
            p2 += check_match_p2(inp, x, y);
            for (int d = 0; d < 8; d++) {
                p1 += check_match(inp, x, y, d);
            }
        }
    }

    auto done = chrono::steady_clock::now();
    cout << "[P1] " << p1 << "\n[P2] " << p2 << endl;
    return done;
}