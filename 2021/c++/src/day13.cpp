#include "AOC.h"
#define grid unordered_set<pii, pair_hash>

struct pair_hash{
	template <class T1, class T2>
	size_t operator()(pair<T1, T2> const &pair) const{
		return hash<T1>()(pair.first) ^ hash<T2>()(pair.second);
	}
};

void foldX(grid& g, int x){
	grid n;
	for(auto c: g)
		if(c.x>x)
			n.insert(pii(x*2-c.x, c.y));
		else
			n.insert(c);
	g = n;
}
void foldY(grid& g, int y){
	grid n;
	for(auto c: g)
		if(c.y>y)
			n.insert(pii(c.x, 2*y-c.y));
		else
			n.insert(c);
	g = n;
}
chrono::time_point<std::chrono::steady_clock> day13(input_t& inp){
	int p1(0);
	grid g;
	bool coords = true;
	char tr;
	for(auto& l: inp){
		if(l.empty()){
			coords = false;
			continue;
		}
		if(coords){
			pii c;
			stringstream ss(l);
			ss>>c.x>>tr>>c.y;
			g.insert(c);
		}else{
			if(l[11] == 'x')
				foldX(g, stoi(l.substr(13)));
			else
				foldY(g, stoi(l.substr(13)));
			if(!p1) p1 = g.size();
		}
	}
	vector<string> s(6, "                                       ");
	for(auto& c: g){
		s[c.y][c.x] = '#';
	}
	
	string p2;
	for(auto& l: s){
		p2+="\n"+l;
	}
	auto done = chrono::steady_clock::now();
	cout<<"[P1] "<<p1<<"\n[P2] "<<p2<<endl;
	return done;
}