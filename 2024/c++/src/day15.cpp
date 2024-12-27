#include "AOC.h"

pii shift(input_t& grid, int px, int py, char d) {
    int dx, dy;
    switch (d) {
        case '>':
            dx = 1;
            dy = 0;
            break;
        case '<':
            dx = -1;
            dy = 0;
            break;
        case '^':
            dx = 0;
            dy = -1;
            break;
        case 'v':
            dx = 0;
            dy = 1;
            break;
    }
    int x(px), y(py), stack(0);
    while (grid[y][x] != '#' && grid[y][x] != '.') {
        grid[y][x] = '.';
        stack++;
        x += dx;
        y += dy;
    }
    if (grid[y][x] == '#') {
        x -= dx;
        y -= dy;
    }
    while (stack-- > 1) {
        grid[y][x] = 'O';
        x -= dx;
        y -= dy;
    }
    grid[y][x] = '@';
    return pii(x, y);
}

chrono::time_point<std::chrono::steady_clock> day15(input_t& inp) {
    ull p1(0), p2(0);

    int i, j;
    vector<vector<char>> board;

    // Cursed syntax lol
    do i++;
    while (!inp[i].empty());
    j = i;

    // for (int y = 0; y < inp.size(); y++) {
    //     for (int x = 0; x < inp[0].size(); x++) {
    //         if (inp[y][x] != '.') {
    //             p1 += y * 100 + x;
    //         }
    //     }
    // }

    string instrs;
    for (i++; i < inp.size(); i++) {
        instrs += inp[i];
    }
    inp.resize(j);

    int px(0), py;
    for (int y = 0; y < inp.size() && px == 0; y++) {
        for (int x = 0; x < inp[0].size(); x++) {
            if (inp[y][x] == '@') {
                px = x;
                py = y;
                break;
            }
        }
    }
    for (auto& c : instrs) {
        tie(px, py) = shift(inp, px, py, c);
        // break;
        // for (auto& l : inp) cout << l << endl;
        // cout << endl;
    }

    for (int y = 0; y < inp.size(); y++) {
        for (int x = 0; x < inp[0].size(); x++) {
            if (inp[y][x] == 'O') {
                p1 += y * 100 + x;
            }
        }
    }

    auto done = chrono::steady_clock::now();
    cout << "[P1] " << p1 << "\n[P2] " << p2 << endl;
    return done;
}