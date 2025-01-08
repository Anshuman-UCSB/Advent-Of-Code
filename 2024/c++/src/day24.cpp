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
    void reset();
};

class Component {
   public:
    string type;
    Wire *a, *b, *out;
    bool completed;

    Component();
    Component(string line);
    void update();
};

map<string, Wire*> wires;

Wire::Wire(string name) : name(name), defined(false) {
    // cout << "Made wire with name " << name << endl;
}
void Wire::update(bool value) {
    // if (defined) return;
    defined = true;
    val = value;
    for (auto& c : connections) {
        c.update();
    }
}
void Wire::reset() {
    defined = false;
    val = false;
    for (auto& c : connections) {
        c.update();
    }
}

Component::Component(string line) : completed(false) {
    stringstream ss(line);
    string na, nb, nout;
    ss >> na >> type >> nb >> nout >> nout;

    if (wires.find(na) == wires.end()) wires[na] = new Wire(na);
    if (wires.find(nb) == wires.end()) wires[nb] = new Wire(nb);
    if (wires.find(nout) == wires.end()) wires[nout] = new Wire(nout);

    a = wires[na];
    b = wires[nb];
    out = wires[nout];

    a->connections.push_back(*this);
    b->connections.push_back(*this);
}

ostream& operator<<(ostream& os, const Wire& w) {
    os << "(" << w.name << "-";
    if (!w.defined) {
        os << "X";
    } else {
        os << w.val ? "1" : "0";
    }
    os << ")";
    return os;
}

void Component::update() {
    completed = out->defined;
    // cout << out->defined << ", " << *a << ", " << *b << endl;
    // if (out->defined) return;
    if (a->defined && b->defined) {
        if (type == "AND") {
            out->update(a->val & b->val);
        } else if (type == "OR") {
            out->update(a->val | b->val);
        } else if (type == "XOR") {
            out->update(a->val ^ b->val);
        }
    } else {
        out->reset();
        completed = false;
    }
}

ostream& operator<<(ostream& os, const Component& c) {
    os << "<" << c.a->name << " " << c.type << " " << c.b->name << " -> "
       << c.out->name << ">";
    return os;
}

ull output(vector<Wire*>& Z) {
    ull out = 0;
    for (int i = 0; i < Z.size(); i++) {
        ull tmp = Z[i]->val;
        tmp <<= i;
        out += tmp;
    }
    return out;
}

chrono::time_point<std::chrono::steady_clock> day24(input_t& inp) {
    ull p1(0), p2(0);

    int i;
    for (i = 0; i < inp.size(); i++) {
        if (inp[i].empty()) {
            i++;
            break;
        }
    }

    vector<Component> components;
    for (; i < inp.size(); i++) {
        components.emplace_back(inp[i]);
    }

    for (int i = 0; i < inp.size() && !inp[i].empty(); i++) {
        wires[inp[i].substr(0, 3)]->update(inp[i].back() == '1');
    }

    // part 2 reset
    vector<Wire*> X, Y, Z;
    for (auto& [k, v] : wires) {
        switch (k[0]) {
            case 'x':
                X.push_back(v);
                break;
            case 'y':
                Y.push_back(v);
                break;
            case 'z':
                Z.push_back(v);
                break;
        }
    }
    p1 = output(Z);
    for (auto& v : X) v->reset();
    for (auto& v : Y) v->reset();

    // for (auto& v : Z) {
    //     cout << *v << endl;
    // }

    for (int i = 0; i < X.size(); i++) {
        if (i > 0) X[i - 1]->update(0);
        X[i]->update(1);
    }

    // cout << wires["x00"]->connections << endl;
    // cout << wires["x01"]->connections << endl;

    for (auto& [k, v] : wires) {
        delete v;
    }

    auto done = chrono::steady_clock::now();
    cout << "[P1] " << p1 << "\n[P2] " << p2 << endl;
    return done;
}