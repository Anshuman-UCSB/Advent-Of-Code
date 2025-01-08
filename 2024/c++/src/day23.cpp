#include "AOC.h"

void calc_cliques(const map<string, vector<string>>& adj,
                  set<set<string>>& cliques, string n1) {
    const auto adj_n1 = adj.at(n1);
    int sz = adj_n1.size();
    string n2, n3;
    for (int i = 0; i < sz; i++) {
        n2 = adj_n1[i];
        const auto adj_n2 = adj.at(n2);
        for (int j = i + 1; j < sz; j++) {
            n3 = adj.at(n1)[j];
            if (find(adj_n2.begin(), adj_n2.end(), n3) == adj_n2.end())
                continue;

            // cout << n1 << ", " << n2 << ", " << n3 << endl;
            cliques.insert(set<string>{n1, n2, n3});
        }
    }
}

string find_13_clique(const map<string, vector<string>>& adj,
                      const set<string>& nodes) {
    map<string, set<string>> adj_s;
    for (auto& [k, v] : adj) {
        adj_s[k] = set<string>(v.begin(), v.end());
        // cout << k << ",  " << adj_s[k] << endl;
    }

    for (auto& n : nodes) {
        set<string> cq = {n};
        set<string> candidates(adj.at(n).begin(), adj.at(n).end());
        // cout << cq << ", " << candidates << endl;
        for (auto& e : adj.at(n)) {
            if (candidates.count(e) == 0) continue;
            set<string> tmp;
            set_intersection(candidates.begin(), candidates.end(),
                             adj_s[e].begin(), adj_s[e].end(),
                             inserter(tmp, tmp.begin()));
            candidates = tmp;
            // cout << candidates << endl;
            cq.insert(e);
        }
        if (cq.size() >= 13) {
            // cout << "we made: " << cq << " with size " << cq.size() << endl;
            stringstream ss;
            string delim = "";
            for (auto v : cq) {
                ss << delim << v;
                delim = ",";
            }
            return ss.str();
        }
    }
    return "failed";
}

chrono::time_point<std::chrono::steady_clock> day23(input_t& inp) {
    int p1(0);

    map<string, vector<string>> adj;
    set<string> nodes;

    for (auto& l : inp) {
        string a = l.substr(0, 2);
        string b = l.substr(3, 2);

        adj[a].push_back(b);
        adj[b].push_back(a);
        nodes.insert(a);
        nodes.insert(b);
    }
    // for (auto& [k, v] : adj) {
    //     cout << k << " : " << v << endl;
    // }
    set<set<string>> cliques;
    for (auto& v : nodes) {
        if (v[0] != 't') continue;
        // cout << v << endl;
        calc_cliques(adj, cliques, v);
    }
    // cout << cliques << endl;
    p1 = cliques.size();

    string p2 = find_13_clique(adj, nodes);

    auto done = chrono::steady_clock::now();
    cout << "[P1] " << p1 << "\n[P2] " << p2 << endl;
    return done;
}