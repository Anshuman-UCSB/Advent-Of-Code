#include "AOC.h"

class Component;
class Wire {
   public:
    string name;
    string annot_in;  // this could be faulty
    string annot_out;
    bool val;
    bool defined;
    vector<Component> connections;

    Wire() {}
    Wire(string name);

    void update(bool value);
    void reset();
    string rep() const {
        if (!annot_in.empty() || !annot_out.empty())
            if (annot_in == annot_out) {
                return name + "(" + annot_in + ")";
            }
        return name + "(" + annot_in + ":" + annot_out + ")";
        return name;
    }
    bool isAnnot(string prefix) {
        return annot_in.starts_with(prefix) || annot_out.starts_with((prefix));
    }
};

class Component {
   public:
    string type;
    Wire *a, *b, *out;
    bool completed;

    Component() {}
    Component(string line);
    void update();

    bool operator<(const Component& other) {
        return make_tuple(out->name, this->type) <
               make_tuple(other.out->name, other.type);
    }
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
    if (na > nb) {
        swap(na, nb);
    }

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
    os << "(" << w.rep();

    os << "-";
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
    Wire *ca(c.a), *cb(c.b);
    if (c.a->annot_in < c.b->annot_in ||
        (c.a->annot_in == c.b->annot_in && c.a->annot_out < c.b->annot_out)) {
        swap(ca, cb);
    }
    os << "<" << ca->rep() << " " << c.type << " " << cb->rep() << " -> "
       << c.out->rep() << ">";
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

bool isLetter(Wire* w) {
    switch (w->name[0]) {
        case 'x':
        case 'y':
        case 'z':
            return true;
    }
    return false;
}

string p2Analysis(vector<Component>& components, map<string, Component> source,
                  vector<Wire*> X, vector<Wire*> Y, vector<Wire*> Z,
                  vector<Wire*> OTHER) {
    set<string> ans;

    // create map of all gates
    map<string, vector<Component>> gates;
    for (auto& c : components) {
        gates[c.type].push_back(c);
    }

    for (auto& z : Z) {
        if (z == Z.back()) continue;  // last one is an OR
        if (source[z->name].type != "XOR") ans.insert(z->name);
    }

    for (auto& g : gates["XOR"]) {
        if (!isLetter(g.out) && !isLetter(g.a) && !isLetter(g.b)) {
            ans.insert(g.out->name);
        }
    }

    for (auto& g : gates["AND"]) {
        cout << g << endl;
        Wire out = *g.out;
        cout << out.connections << endl;
    }

    // // annotate inputs, guaranteed not switched
    // for (auto& V : {X, Y}) {
    //     for (auto& c : V) {
    //         c->annot_in = "IN_" + c->name;
    //         c->annot_out = "IN_" + c->name;
    //     }
    // }

    // // Annotate the XOR from inputs, could be mislabeled
    // for (auto& c : gates["XOR"]) {
    //     if (c.a->isAnnot("IN") && c.b->isAnnot("IN")) {
    //         c.out->annot_in = "AB_SUM_" + c.a->name.substr(1);
    //         // cout << c << endl;
    //     }
    // }

    // // OR should always come from two AND gates, if not then that wire's
    // swapped for (auto& c : gates["OR"]) {
    //     c.out->annot_in = "COUT_?";
    //     for (auto& t : {c.a, c.b}) {
    //         if (source[t->name].type != "AND") {
    //             ans.insert(t->name);
    //             cout << ans << endl;
    //         }
    //     }
    // }

    // for (auto& c : gates["XOR"]) {
    //     if (!c.a->isAnnot("IN") || !c.b->isAnnot("IN")) {
    //         cout << c << endl;
    //         if (c.out->name[0] != 'z') {
    //             ans.insert(c.out->name);
    //             Wire* tmp = c.a;
    //             if (!tmp->isAnnot("AB_SUM")) {
    //                 tmp = c.b;
    //             }
    //             ans.insert("z" +
    //                        tmp->annot_in.substr(tmp->annot_in.size() - 2));
    //             // cout << c << endl;
    //         }
    //         for (auto& t : {c.a, c.b}) {
    //             if (t->annot_in.empty()) {
    //                 // must be mislabeled
    //                 ans.insert(t->name);
    //             }
    //         }
    //     }
    // }

    // // Annotate the AND from inputs, could be mislabeled
    // for (auto& c : gates["AND"]) {
    //     if (c.a->isAnnot("IN") && c.b->isAnnot("IN")) {
    //         c.out->annot_in = "AB_CARRY_" + c.a->name.substr(1);
    //         // cout << c << endl;
    //     }
    // }

    // wsg = AB_CARRY_0
    // cout << X[0]->connections << endl;
    // cout << Y[0]->connections << endl;
    // cout << Z[0]->connections << endl;
    // cout << source[Z[0]->name] << endl;

    // for (auto& [k, v] : wires) {
    //     cout << *v << endl;
    // }

    stringstream ss;
    string delim = "";
    for (auto& s : ans) {
        ss << delim << s;
        delim = ",";
    }
    return ss.str();
}

chrono::time_point<std::chrono::steady_clock> day24(input_t& inp) {
    ull p1(0);
    string p2;

    int i;
    for (i = 0; i < inp.size(); i++) {
        if (inp[i].empty()) {
            i++;
            break;
        }
    }

    vector<Component> components;
    map<string, Component> source;
    for (; i < inp.size(); i++) {
        components.emplace_back(inp[i]);
        source[components.back().out->name] = components.back();
    }

    for (int i = 0; i < inp.size() && !inp[i].empty(); i++) {
        wires[inp[i].substr(0, 3)]->update(inp[i].back() == '1');
    }
    for (auto& [k, v] : wires) {
        sort(v->connections.begin(), v->connections.end());
    }

    // part 2 reset

    sort(components.begin(), components.end());
    vector<Wire*> X, Y, Z, OTHER;

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
            default:
                OTHER.push_back(v);
                break;
        }
    }
    p1 = output(Z);

    p2 = p2Analysis(components, source, X, Y, Z, OTHER);
    // // for (auto& v : Z) {
    // //     cout << *v << endl;
    // // }

    // for (ull i = 0; i < X.size(); i++) {
    //     if (i > 0) X[i - 1]->update(0);
    //     X[i]->update(1);
    //     if ((ull)1 << i != output(Z))
    //         cout << 'X' << i << '\t' << ((ull)1 << i) << "\t" << output(Z)
    //              << endl;
    // }
    // X.back()->update(0);
    // cout << endl;

    // for (ull i = 0; i < Y.size(); i++) {
    //     if (i > 0) Y[i - 1]->update(0);
    //     Y[i]->update(1);
    //     if ((ull)1 << i != output(Z))
    //         cout << 'Y' << i << '\t' << ((ull)1 << i) << "\t" << output(Z)
    //              << endl;
    // }
    // Y.back()->update(0);
    // cout << endl;

    // for (ull i = 0; i < Y.size(); i++) {
    //     if (i > 0) {
    //         Y[i - 1]->update(0);
    //         X[i - 1]->update(0);
    //     }
    //     Y[i]->update(1);
    //     X[i]->update(1);
    //     if ((ull)1 << (i + 1) != output(Z))
    //         cout << "XY" << i << '\t' << ((ull)1 << i) << "\t" << output(Z)
    //              << endl;
    // }
    // Y.back()->update(0);
    // X.back()->update(0);
    // cout << endl;

    // // cout << wires["x00"]->connections << endl;
    // // cout << X[4]->connections << endl;
    // // cout << wires["x01"]->connections << endl;

    // for (auto& y : Y) {
    //     Component c_and = y->connections[0];
    //     Component c_xor = y->connections[1];
    //     if (c_and.type != "AND") {
    //         cout << "WTF THIS IS NOT RIGHT" << endl;
    //         swap(c_and, c_xor);
    //     }
    //     // if (c_and.out->name[0] == 'z') {
    //     //     cout << "WRONG c.out " << *c_and.out << endl;
    //     //     // Found z05 is wrong
    //     //     cout << c_and.out->connections << endl;
    //     // }
    //     c_and.out->annot = "XY_AND" + y->name.substr(1);
    //     c_xor.out->annot = "XY_XOR" + y->name.substr(1);
    //     if (c_and.out->connections.size() == 1) {
    //         c_and.out->connections[0].out->annot = "cin" + y->name.substr(1);
    //     }
    //     if (c_xor.out->connections.size() == 2) {
    //         cout << c_xor.out->connections << endl;
    //         Component c = c_xor.out->connections[0];
    //         if (c.type == "AND") {
    //             c.out->annot = "old_carry" + y->name.substr(1);
    //         }
    //     }
    // }

    // // for (auto& o : OTHER) {
    // //     cout << *o << endl;
    // // }

    // for (auto& z : Z) {
    //     cout << z->name << " comes from " << source[z->name] << endl;
    // }
    // for (auto& c : components) {
    //     if (c.type == "OR") {
    //         cout << c << endl;
    //     }
    // }

    for (auto& [k, v] : wires) {
        delete v;
    }

    auto done = chrono::steady_clock::now();
    cout << "[P1] " << p1 << "\n[P2] " << p2 << endl;
    return done;
}

/*
    NOTES
UNANNOTATED:
gqf should be Cout36
bvc should be cin05
hhh should be cin20
dkr should be XY_AND05
htp should be old_carry15



WRONGLY ANNOTATED:
z05 (XY_AND05)
z15(Cout15)
z20(Cout20)
ggk(XY_AND36)
rhv(XY_XOR36)


dkr,ggk,hhh,htp,rhv,wsg,z05,z15,z20 is wrong
*/