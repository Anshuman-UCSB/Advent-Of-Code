#include "AOC.h"
#include <cassert>

struct part{
	int l, r, score;
	part(int a, int b){
		l = min(a,b);
		r = max(a,b);
		score = l+r;
	}

	bool operator==(const part& p) const{
		return (l == p.l && r == p.r && score == p.score);
	}

	bool operator<(const part& p) const{
		if(l<p.l) return true;
		if(l == p.l && r<p.r) return true;
		if(l == p.l && r == p.r && score< p.score) return true;
		return false;
	}
};

ostream& operator<<(ostream& os, const part& p){
	os<<p.l<<"/"<<p.r;
	return os;
}

struct bridge{
	int score;
	vector<part> components;
	int edge;
	bridge():score(0), edge(0){}
};

ostream& operator<<(ostream& os, const bridge& b){
	string delim = "";

	for(auto& v: b.components){
		os<<delim<<v;
		delim = "--";
	}
	os<<" ("<<b.score<<")";
	return os;
}

void build(queue<bridge>& q, const vector<part>& parts, int& p1, pii& p2){
	auto base = q.front();
	p1 = max(p1, base.score);
	if(base.components.size()>p2.first || (base.components.size() == p2.first && base.score >p2.second)){
		p2 = pii(base.components.size(), base.score);
	}
	for(auto& p: parts){
		if(p.l == base.edge || p.r == base.edge){
			if(find(base.components.begin(), base.components.end(), p) == base.components.end()){
				bridge temp(base);
				temp.components.push_back(p);
				temp.score+=p.score;
				temp.edge = (p.l == base.edge?p.r:p.l);
				q.push(temp);
			}
		}
	}
	q.pop();
}

chrono::time_point<std::chrono::steady_clock> day24(input_t& inp){
	vector<part> parts;
	for(auto& l : inp){
		stringstream ss(l);
		int a, b;
		char c;
		ss>>a>>c>>b;
		parts.emplace_back(a,b);
	}
	// cout<<parts<<endl;
	queue<bridge> q;
	int p1 = 0;
	pii p2(0,0);
	q.push(bridge());
	while(!q.empty()){
		// cout<<q.front()<<endl;
		build(q, parts, p1, p2);
	}
	
	auto done = chrono::steady_clock::now();
	cout<<"[P1] "<<p1<<endl;
	cout<<"[P2] "<<p2.second<<endl;
	return done;
}