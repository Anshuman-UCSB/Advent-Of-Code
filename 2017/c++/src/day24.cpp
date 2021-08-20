#include "AOC.h"
#include <cassert>

struct part{
	int l, r;
	int score;
	part():l(-1), r(-1), score(-1){}
	part(string line){
		stringstream ss(line);
		char t;
		ss>>l>>t>>r;
		if(l>r) swap(l, r);
		score = l+r;
	}

	part(const part& p){
		l = p.l;
		r = p.r;
		score = p.score;
	}

	void join(const part& p){
		score+=p.score;
		if(l == p.l)
			l = p.r;
		else if(l == p.r)
			l = p.l;
		else if(r == p.r)
			r = p.l;
		else if(r == p.l)
			r = p.r;
		else
			cout<<"ERROR"<<endl;	
		if(l>r) swap(l, r);	
	}

	bool operator<(const part& p) const {
		return make_pair(l, r)<make_pair(p.l, p.r);
	}
	bool operator==(const part& p) const {
		return make_tuple(l, r, score) == make_tuple(p.l, p.r, p.score);
	}
};

ostream& operator<<(ostream& os, const part& p){
	os<<p.l<<"/"<<p.r;
	return os;
}

struct bridge{
	int score;
	int edge;
	set<part> components;
	bridge():score(0), edge(0){}

	vector<part> validParts(const vector<part>& parts){
		vector<part> out;
		for(auto& p: parts){
			if(p.l == edge || p.r == edge){
				if(components.count(p)==0)
					out.push_back(p);
			}
		}
		return out;
	}
};

bridge append(bridge b, part p) {
		// cout<<b.components<<" "<<p<<endl;
		assert(p.l == b.edge || p.r == b.edge);
		b.score+=p.score;
		if(p.l == b.edge)
			b.edge = p.r;
		else
			b.edge = p.l;
		b.components.insert(p);
		return b;
	}

chrono::time_point<std::chrono::steady_clock> day24(input_t& inp){
	vector<part> parts;
	for(auto& l: inp){
		parts.emplace_back(l);
	}
	map<int, int> m;
	for(auto& p: parts){
		m[p.l]++; m[p.r]++;
	}
	for(auto& [k, v]: m){
		if(v == 2 && k){
			// cout<<"Looking for "<<k<<endl;
			for(int i = 0;i<parts.size()-1;i++){
				if(parts[i].l == k){
					if(parts[i].r == k) parts.erase(parts.begin()+i);
					else{
						for(int j = i+1;j<parts.size();j++){
							if(parts[j].r == k || parts[j].l == k){
								// cout<<"Combining "<<parts[i]<<" and "<<parts[j]<<endl;
								parts[i].join(parts[j]);
								parts.erase(parts.begin()+j);
								break;
							}
						}
					}
					v-=2;
					break;
				}else if(parts[i].r == k){
					if(parts[i].l == k) parts.erase(parts.begin()+i);
					else{
						for(int j = i+1;j<parts.size();j++){
							if(parts[j].r == k || parts[j].l == k){
								// cout<<"Combining "<<parts[i]<<" and "<<parts[j]<<endl;
								parts[i].join(parts[j]);
								parts.erase(parts.begin()+j);
								break;
							}
						}
					}
					v-=2;
					break;
				}
			}
		}
	}
	queue<bridge> bridges;
	bridge empty;
	bridges.emplace();
	// cout<<parts<<endl;
	int p1 = 0;
	while(!bridges.empty()){
		auto b = bridges.front();
		bridges.pop();
		for(auto p: b.validParts(parts)){
			// cout<<"appending "<<p<<" to "<<"("<<b.components<<")"<<endl;
			bridges.push(append(b,p));
		}
		p1 = max(p1, b.score);
	}

	auto done = chrono::steady_clock::now();
	cout<<"[P1] "<<p1<<endl;
	//1642 too low
	return done;
}