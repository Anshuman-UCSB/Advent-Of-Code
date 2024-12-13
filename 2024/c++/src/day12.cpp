#include "AOC.h"

void DFS(input_t& inp, int x, int y, char plant, int& perimeter,
         set<pii>& points) {
    if (y < 0 || y >= inp.size() || x < 0 || x >= inp[0].size() ||
        inp[y][x] == '.') {
        perimeter++;
        return;
    }
    if (inp[y][x] != plant && inp[y][x] != '?') {
        perimeter++;
        return;
    }
    if (inp[y][x] == plant) {
        points.emplace(x, y);
        inp[y][x] = '?';
        DFS(inp, x, y + 1, plant, perimeter, points);
        DFS(inp, x, y - 1, plant, perimeter, points);
        DFS(inp, x + 1, y, plant, perimeter, points);
        DFS(inp, x - 1, y, plant, perimeter, points);
    }
}

void clean(input_t& inp, const set<pii>& points) {
    for (auto& [x, y] : points) {
        inp[y][x] = '.';
    }
}

int countCorners(const set<pii>& points) {
    int corners = 0;

    for (auto& [x, y] : points) {
        bool edges[8] = {
            !points.contains(pii(x, y + 1)),
            !points.contains(pii(x - 1, y + 1)),
            !points.contains(pii(x - 1, y)),
            !points.contains(pii(x - 1, y - 1)),
            !points.contains(pii(x, y - 1)),
            !points.contains(pii(x + 1, y - 1)),
            !points.contains(pii(x + 1, y)),
            !points.contains(pii(x + 1, y + 1)),
        };

        for (int i = 0; i < 8; i += 2) {
            if (!edges[i] && !edges[(i + 2) % 8]) {
                corners++;
            }
            if (edges[i] && !edges[(i + 1) % 8] && edges[(i + 2) % 8]) {
                corners++;
            }
        }

        return corners;
    }
}

chrono::time_point<std::chrono::steady_clock> day12(input_t& inp) {
    int p1(0), p2(0);

    int p;
    for (int y = 0; y < inp.size(); y++) {
        for (int x = 0; x < inp[0].size(); x++) {
            if (inp[y][x] != '.') {
                p = 0;
                set<pii> points;
                DFS(inp, x, y, inp[y][x], p, points);
                cout << points << endl;
                clean(inp, points);
                p1 += points.size() * p;
                cout << "Faces on this shape: " << countCorners(points) << endl;
            }
        }
    }

    auto done = chrono::steady_clock::now();
    cout << "[P1] " << p1 << "\n[P2] " << p2 << endl;
    return done;
}