#include "AOC.h"

class Wire {
    string name;
    bool val;
    bool defined;
    set<Wire> connections;

   public:
    Wire() {}
    Wire(string name) : name(name), defined(false) {}
    friend ostream& operator<<(ostream& os, const Wire& w);
};

ostream& operator<<(ostream& os, const Wire& w) {
    os << "(" << w.name << "-";
    if (!w.defined) {
        os << "X";
    } else {
        os << w.val ? "1" : "0";
    }
    os << " <";

    string delim;
    for (auto& e : w.connections) {
        os << delim << e.name;
        delim = ", ";
    }

    os << ">";
    return os;
}

map<string, Wire> wires;
void registerWire(string name) { wires[name] = Wire(name); }

chrono::time_point<std::chrono::steady_clock> day24(input_t& inp) {
    int p1(0), p2(0);

    registerWire("x00");
    registerWire("y00");
    cout << wires << endl;

    auto done = chrono::steady_clock::now();
    cout << "[P1] " << p1 << "\n[P2] " << p2 << endl;
    return done;
}