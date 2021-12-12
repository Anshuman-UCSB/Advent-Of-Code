#include "AOC.h"
#include <tuple>
#define state tuple<string, unordered_set<string>, bool>

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
	queue<state> q({make_tuple("start", unordered_set<string>{"start"}, false)});
	unordered_set<string> smalls;
	bool doublevisit;
	while(!q.empty()){
		state front = q.front();
		tie(pos, smalls, doublevisit) = front;
		q.pop();
		if(pos == "end"){
			if(!doublevisit)
				p1++;
			p2++;
		}else
			for(auto& n: adj[pos]){
				if(islower(n[0])){
					if(smalls.find(n) != smalls.end()){
						if(!doublevisit)
							q.push(make_tuple(n, smalls, true));
					}else{
						unordered_set<string> t = smalls;
						t.insert(n);
						q.push(make_tuple(n, t, doublevisit));
					}
				}else
					q.push(make_tuple(n, smalls, doublevisit));
			}
	}
	auto done = chrono::steady_clock::now();
	cout<<"[P1] "<<p1<<"\n[P2] "<<p2<<endl;
	return done;
}