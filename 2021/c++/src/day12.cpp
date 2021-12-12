#include "AOC.h"
#include <tuple>
#define state tuple<string, unordered_set<string>, bool>

void dfs(unordered_map<string, vector<string>> &adj, const string& pos, const unordered_set<string> smalls, bool doublevisit, int& p1, int& p2){
	if(pos == "end"){
		if(!doublevisit)
			p1++;
		p2++;
		return;
	}

	for(auto& n: adj[pos]){
		if(islower(n[0])){
			if(smalls.find(n) != smalls.end()){
				if(!doublevisit)
					dfs(adj, n, smalls, true, p1, p2);
			}else{
				unordered_set<string> t = smalls;
				t.insert(n);
				dfs(adj, n, t, doublevisit, p1, p2);
			}
		}else
			dfs(adj, n, smalls, doublevisit, p1, p2);
	}
}

chrono::time_point<std::chrono::steady_clock> day12(input_t& inp){
	int p1(0), p2(0);
	unordered_map<string, vector<string>> adj;
	string a, b, pos;
	size_t p;
	char c;
	for(auto& l: inp){
		p = l.find('-');
		a = l.substr(0,p);
		b = l.substr(p+1);
		if(b != "start")
			adj[a].push_back(b);
		if(a != "start")
			adj[b].push_back(a);
	}
	stack<state> q({make_tuple("start", unordered_set<string>{"start"}, false)});
	string start = "start";
	unordered_set<string> small = {"start"};
	bool doublevisit = false;
	dfs(adj, start, small, doublevisit, p1, p2);
	auto done = chrono::steady_clock::now();
	cout<<"[P1] "<<p1<<"\n[P2] "<<p2<<endl;
	return done;
}