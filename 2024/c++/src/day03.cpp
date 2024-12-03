#include <regex>

#include "AOC.h"

chrono::time_point<std::chrono::steady_clock> day03(input_t& inp) {
    int p1(0), p2(0);

    smatch match;
    regex r("mul\\((\\d{1,3}),(\\d{1,3})\\)|do\\(\\)|don't\\(\\)");

    int a, b;
    bool enabled = true;
    for (auto& line : inp) {
        while (regex_search(line, match, r)) {
            if (match.str() == "do()")
                enabled = true;
            else if (match.str() == "don't()")
                enabled = false;
            else {
                a = stoi(match[1]);
                b = stoi(match[2]);
                p1 += a * b;
                if (enabled) {
                    p2 += a * b;
                }
            }
            line = match.suffix().str();
        }
    }

    auto done = chrono::steady_clock::now();
    cout << "[P1] " << p1 << "\n[P2] " << p2 << endl;
    return done;
}