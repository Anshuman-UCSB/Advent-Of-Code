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

bool isBlocked(const vector<vector<char>>& grid, set<pii>& moveSet, int x,
               int y, const int dx, const int dy, bool neighborCall = false) {
    if (grid[y][x] != '[' && grid[y][x] != ']' && grid[y][x] != '@') {
        return grid[y][x] != '.';
    } else {
        moveSet.emplace(x, y);
        return ((!neighborCall && dy) &&
                ((grid[y][x] == '[' && isBlocked(grid, moveSet, x + 1, y, dx,
                                                 dy, neighborCall = true)) ||
                 (grid[y][x] == ']' && isBlocked(grid, moveSet, x - 1, y, dx,
                                                 dy, neighborCall = true)))) ||
               isBlocked(grid, moveSet, x + dx, y + dy, dx, dy);
    }
}

pii shift_p2(vector<vector<char>>& grid, int px, int py, char d) {
    int dx, dy;
    set<pii> moveSet;
    auto oldGrid(grid);

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

    if (!isBlocked(grid, moveSet, px, py, dx, dy)) {
        for (const auto& [x, y] : moveSet) {
            grid[y][x] = '.';
        }
        for (const auto& [x, y] : moveSet) {
            grid[y + dy][x + dx] = oldGrid[y][x];
        }
        px += dx;
        py += dy;
    }

    return pii(px, py);
}

ull part2(const input_t& p1board, string instrs, int px, int py) {
    ull p2(0);
    vector<vector<char>> board;

    for (const auto& row : p1board) {
        board.emplace_back();
        for (char c : row) {
            switch (c) {
                case '#':
                    board.back().push_back('#');
                    board.back().push_back('#');
                    break;
                case 'O':
                    board.back().push_back('[');
                    board.back().push_back(']');
                    break;
                case '.':
                    board.back().push_back('.');
                    board.back().push_back('.');
                    break;
                default:  // @
                    board.back().push_back('@');
                    board.back().push_back('.');
                    break;
            }
        }
    }

    px *= 2;

    for (auto& d : instrs) {
        // cout << d << endl;
        tie(px, py) = shift_p2(board, px, py, d);
        // for (auto& r : board) {
        //     for (auto c : r) {
        //         cout << c;
        //     }
        //     cout << endl;
        // }
        // break;
    }

    for (int y = 0; y < board.size(); y++) {
        for (int x = 0; x < board[0].size(); x++) {
            if (board[y][x] == '[') {
                p2 += y * 100 + x;
            }
        }
    }

    return p2;
}

chrono::time_point<std::chrono::steady_clock> day15(input_t& inp) {
    ull p1(0);

    int i, j;
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

    ull p2 = part2(inp, instrs, px, py);

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