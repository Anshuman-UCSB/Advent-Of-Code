#include "AOC.h"

void printMem(const vector<int>& mem) {
    for (auto& v : mem) {
        if (v == -1) {
            cout << ".";
        } else {
            cout << v;
        }
    }
    cout << endl;
}

ull part1(vector<int> mem) {
    int p1(0), p2(mem.size() - 1);
    ull ans(0);

    while (p1 < p2) {
        while (mem[p1] != -1) {
            p1++;
        }
        while (mem[p2] == -1) {
            p2--;
        }
        swap(mem[p1], mem[p2]);
    }
    swap(mem[p1], mem[p2]);
    for (ull i = 0; i < mem.size() && mem[i] != -1; i++) {
        ans += i * mem[i];
    }
    return ans;
}

ull part2(vector<int> mem) {
    map<int, int> free_space;
    vector<pair<int, int>> files;

    int last(0), sz(0);
    int i = 0;
    while (i < mem.size()) {
        last = i;
        sz = 0;
        while (i < mem.size() && mem[i] == mem[last]) {
            i++;
            sz++;
        }
        files.emplace_back(last, sz);

        last = i;
        sz = 0;
        while (i < mem.size() && mem[i] == -1) {
            sz += 1;
            i++;
        }

        free_space[last] = sz;
    }
    // cout << files << endl;

    for (int id = files.size() - 1; id >= 0; id--) {
        // cout << id << endl;
        int movedFromPos = -1;
        int newPos, newSize;

        for (auto& [pos, size] : free_space) {
            // cout << pos << '\t' << size << endl;
            if (size >= files[id].second && pos <= files[id].first) {
                // cout << files[id] << " can fit at " << pos << " with size "
                //      << size << endl;
                for (int j = 0; j < files[id].second; j++) {
                    swap(mem[pos + j], mem[files[id].first + j]);
                }
                movedFromPos = pos;
                newPos = pos + files[id].second;
                newSize = size - files[id].second;
                break;
            }
        }
        if (movedFromPos != -1) {
            // cout << "Actually Moved" << endl;
            // cout << free_space << endl;
            free_space.erase(movedFromPos);
            free_space[newPos] = newSize;
            // printMem(mem);
            // cout << free_space << endl;
        }
    }

    ull ans(0);
    for (ull i = 0; i < mem.size(); i++) {
        if (mem[i] != -1) {
            ans += i * mem[i];
        }
    }

    return ans;
}

chrono::time_point<std::chrono::steady_clock> day09(input_t& inp) {
    ull p1(0), p2(0);
    vector<int> mem;
    int id(0), tmp, addVal;

    for (auto& c : inp[0]) {
        tmp = c - '0';

        addVal = (id >= 0) ? id : -1;

        for (int i = 0; i < tmp; i++) {
            mem.push_back(addVal);
        }

        if (addVal == -1) {
            id *= -1;
        } else {
            id = -id - 1;
        }
    }

    p1 = part1(mem);
    p2 = part2(mem);

    auto done = chrono::steady_clock::now();
    cout << "[P1] " << p1 << "\n[P2] " << p2 << endl;
    return done;
}