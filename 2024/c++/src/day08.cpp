#include "AOC.h"

class Point {
   public:
    int x, y;
    Point(int x, int y) : x(x), y(y) {}
    friend ostream& operator<<(ostream& os, Point const& point) {
        return os << "(" << point.x << "," << point.y << ")";
    }
    Point operator+(Point const& p) const { return Point(x + p.x, y + p.y); }
    Point operator-(Point const& p) const { return Point(x - p.x, y - p.y); }
    bool operator<(const Point& right) const {
        return (x < right.x) || ((x == right.x) && (y < right.y));
    }
};

class Condition {
   public:
    int width, height;
    Condition(int width, int height) : width(width), height(height) {};
    bool operator()(const Point& p) const {
        return (p.x >= 0 && p.x < width) && (p.y >= 0 && p.y < height);
    }
};

set<Point> calculateAntinodes(const Point& a, const Point& b) {
    set<Point> out;
    Point dx = b - a;
    out.insert(b + dx);
    out.insert(a - dx);
    return out;
}

set<Point> calculateAntinodes2(const Point& a, const Point& b,
                               const Condition& isValid) {
    set<Point> out;
    Point dx = b - a;
    Point t = b;
    while (isValid(t)) {
        out.insert(t);
        t = t + dx;
    }
    t = a;
    while (isValid(t)) {
        out.insert(t);
        t = t - dx;
    }
    return out;
}

chrono::time_point<std::chrono::steady_clock> day08(input_t& inp) {
    int p1(0);
    Condition isValid(inp.size(), inp[0].size());

    map<char, vector<Point>> frequencies;
    set<Point> antinodes, filtered, p2;
    for (int y = 0; y < inp.size(); y++) {
        for (int x = 0; x < inp[y].size(); x++) {
            if (inp[y][x] != '.') {
                frequencies[inp[y][x]].emplace_back(x, y);
            }
        }
    }

    for (auto& [c, points] : frequencies) {
        for (int i = 0; i < points.size(); i++) {
            for (int j = i + 1; j < points.size(); j++) {
                // cout << points[i] << "\t" << points[j] << "\t"
                //      << calculateAntinodes(points[i], points[j]) << endl;
                set<Point> out = calculateAntinodes(points[i], points[j]);
                antinodes.insert(out.begin(), out.end());

                set<Point> p2Temp =
                    calculateAntinodes2(points[i], points[j], isValid);
                p2.insert(p2Temp.begin(), p2Temp.end());
            }
        }
    }

    copy_if(antinodes.begin(), antinodes.end(),
            inserter(filtered, filtered.end()), isValid);

    auto done = chrono::steady_clock::now();
    cout << "[P1] " << filtered.size() << "\n[P2] " << p2.size() << endl;
    return done;
}