#include "AOC.h"

class Component;
class Wire {
   public:
    string name;
    bool val;
    bool defined;
    vector<Component> connections;

    Wire() {}
    Wire(string name);

    void update(bool value);
};

class Component {
   public:
    string type;
    Wire *a, *b, *out;
    bool completed;

    Component(string line);
    void update();
};

map<string, Wire*> wires;

Wire::Wire(string name) : name(name), defined(false) {
    // cout << "Made wire with name " << name << endl;
}
void Wire::update(bool value) {
    if (defined) return;
    defined = true;
    val = value;
}

Component::Component(string line) {
    stringstream ss(line);
    string na, nb, nout;
    ss >> na >> type >> nb >> nout >> nout;

    if (wires.find(na) == wires.end()) wires[na] = new Wire(na);
    if (wires.find(nb) == wires.end()) wires[nb] = new Wire(nb);
    if (wires.find(nout) == wires.end()) wires[nout] = new Wire(nout);

    a = wires[na];
    b = wires[nb];
    out = wires[nout];
    completed = out->defined;

    a->connections.push_back(*this);
    b->connections.push_back(*this);
}

void Component::update() {
    if (completed) return;
    if (a->defined && b->defined) {
        if (type == "AND") {
            out->update(a->val & b->val);
        } else if (type == "OR") {
            out->update(a->val | b->val);
        } else if (type == "XOR") {
            out->update(a->val ^ b->val);
        }
    }
}

ostream& operator<<(ostream& os, const Wire& w) {
    os << "(" << w.name << "-";
    if (!w.defined) {
        os << "X";
    } else {
        os << w.val ? "1" : "0";
    }
    // os << " <";

    // string delim;
    // for (auto& e : w.connections) {
    //     os << delim << e.a->name << e.type << e.b->name << " -> "
    //        << e.out->name;
    //     os << e.type << endl;
    //     delim = ", ";
    // }

    // os << ">";
    os << ")";
    return os;
}

chrono::time_point<std::chrono::steady_clock> day24(input_t& inp) {
    int p1(0), p2(0);

    // Wire("x00");
    // Wire("y00");
    Component c("x00 AND y00 -> z00");
    for (auto& [k, v] : wires) {
        cout << k << "\t" << *v << endl;
    }

    // cout << c.completed << endl;
    // wires["x00"].update(1);
    // cout << c.completed << endl;
    // wires["y00"].update(1);
    // cout << c.completed << endl;

    auto done = chrono::steady_clock::now();
    cout << "[P1] " << p1 << "\n[P2] " << p2 << endl;
    return done;
}