#include <algorithm>
#include <regex>

#include "AOC.h"

const regex pattern("p=(\\d+),(\\d+) v=(-?\\d+),(-?\\d+)");

class Robot {
   public:
    vector<int> pos, vel;
    Robot(string line) {
        smatch match;

        regex_search(line, match, pattern);
        pos.push_back(stoi(match[1]));
        pos.push_back(stoi(match[2]));
        vel.push_back(stoi(match[3]));
        vel.push_back(stoi(match[4]));

        line = match.suffix().str();
    }
    void iter(bool EXAMPLE) {
        int X = EXAMPLE ? 11 : 101;
        int Y = EXAMPLE ? 7 : 103;
        pos[0] = (pos[0] + vel[0]) % X;
        if (pos[0] < 0) pos[0] += X;
        pos[1] = (pos[1] + vel[1]) % Y;
        if (pos[1] < 0) pos[1] += Y;
    }
};

vector<int> quadrants(vector<Robot>& robots, bool EXAMPLE) {
    int X = EXAMPLE ? 11 : 101;
    int Y = EXAMPLE ? 7 : 103;
    vector<int> q(4);
    for (auto& r : robots) {
        int x(r.pos[0]), y(r.pos[1]);
        if (x == X / 2 || y == Y / 2) continue;
        if (x > X / 2) {
            if (y < Y / 2)
                q[0]++;
            else
                q[3]++;
        } else {
            if (y < Y / 2)
                q[1]++;
            else
                q[2]++;
        }
    }
    return q;
}

ll loss(const vector<Robot>& robots) {
    ll loss = 0;
    int X = 101;
    int Y = 103;
    // Dist from Y middle
    // for (auto& r : robots) {
    //     loss += abs(X / 2 - r.pos[0]);
    // }
    int best = 0;
    for (auto& r : robots) {
        loss += abs(X / 2 - r.pos[0]);
    }

    return loss;
}

ll loss(const vector<int>& quads) {
    // return -*max_element(quads.begin(), quads.end());
    return -*max_element(quads.begin(), quads.end());
}

void visualize(vector<Robot>& robots) {
    int X = 101;
    int Y = 103;
    vector<vector<int>> grid(Y, vector<int>(X));
    for (auto& r : robots) {
        grid[r.pos[1]][r.pos[0]]++;
    }

    for (auto& r : grid) {
        for (auto c : r) {
            cout << (c ? (char)('0' + c) : '.');
        }
        cout << endl;
    }
}

chrono::time_point<std::chrono::steady_clock> day14(input_t& inp) {
    int p1(0), p2(0);

    vector<Robot> robots;
    for (auto& line : inp) {
        robots.emplace_back(line);
    }
    bool EXAMPLE = robots.size() == 12;
    int i;
    for (i = 0; i < 100; i++) {
        for (auto& r : robots) r.iter(EXAMPLE);
    }
    // for (auto& r : robots) cout << r.pos << endl;
    vector<int> quads = quadrants(robots, EXAMPLE);
    p1 = quads[0] * quads[1] * quads[2] * quads[3];

    ll bestLoss(9999999999), tmp;
    while (bestLoss != -222) {
        i++;
        for (auto& r : robots) r.iter(EXAMPLE);
        // tmp = loss(robots);
        quads = quadrants(robots, EXAMPLE);
        tmp = loss(quads);
        if (tmp <= bestLoss) {
            bestLoss = tmp;
            // cout << endl << "New best loss: " << bestLoss << endl;
            // visualize(robots);
        }
        // cout << "i:" << i << endl;
    }

    // visualize(robots);
    p2 = i;

    auto done = chrono::steady_clock::now();
    cout << "[P1] " << p1 << "\n[P2] " << p2 << endl;
    return done;
}