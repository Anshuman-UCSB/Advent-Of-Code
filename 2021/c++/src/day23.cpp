#include "AOC.h"
#define state vector<vector<int>>

ull hashState(const state& s){
	ull out = 0;
	for(auto& r: s)
		for(auto& v: r)
			out = (out<<3)+v;
	return out;
}

vector<string> pprint(const state& s){
	vector<string> base = {
		"#############",
		"#...........#",
		"###?#?#?#?###",
		"  #?#?#?#?#",
		"  #########"
	};
	base[1][1]=s[0][0]?s[0][0]+'A'-1:'.';
	for(int i = 5;i<10;i++)
		base[1][(i-5)*2+2]=s[i][0]?'A'-1+s[i][0]:'.';
	base[1][11]=s[10][0]?s[10][0]+'A'-1:'.';
	for(int i = 1;i<=4;i++)
		for(int j = 0;j<2;j++)
			base[2+j][1+2*i]=s[i][j]?s[i][j]+'A'-1:'.';
	for(auto& l: base)cout<<l<<endl;
	return base;
}

bool solved(state& s){
	for(int i = 1;i<=4;i++){
		for(auto& v: s[i])
			if(v!=i) return false;
	}
	return true;
}

inline bool inHallway(int n){
	return n<1 || n>4;
}

int canMoveRoom(state& s, int n){
	int i;
	for(i = s[n].size()-1;i>=0 && s[n][i] == n;i--);
	if(s[n][i]) return -1;
	for(int j = 0;j<i;j++)
		if(s[n][j]) return -1; //blocked
	return i;
}

set<int> reachable(state& s, int p){
	set<int> out = {p};
	//[ll, r1, r2, r3, r4, l, c1, c2, c3, c4, rr]
	const vector<int> ordering = {0,5,1,6,2,7,3,8,4,9,10};
	int pos = find(begin(ordering), end(ordering), p) - begin(ordering);
	out.insert(ordering[pos]);
	for(int t = pos+1;t<ordering.size() && (!inHallway(ordering[t]) || !s[ordering[t]][0]); t++)
		out.insert(ordering[t]);
	//						    in a room, so can pass or  room is open
	for(int t = pos-1;t>=0 && (!inHallway(ordering[t]) || !s[ordering[t]][0]); t--)
		out.insert(ordering[t]);
	return out;
}

bool correctRoom(state& s, int p){
	int i = s[p].size()-1;
	while(i>=0 && s[p][i]==p)
		i--;
	while(i>=0 && s[p][i]==0)
		i--;
	return i==-1;
}

vector<pii> getMoves(state& s, int p, int y){
	int chip = s[p][y];
	if(chip == 0) return vector<pii>();
	if(inHallway(p)){
		int targetY = canMoveRoom(s, chip);
		if(targetY == -1) return vector<pii>();
		set<int> reach = reachable(s, p);
		if(reach.count(chip)==0)
			return vector<pii>(); //in hallway but can't finish room
		return vector<pii>{pii(chip, targetY)};
	}else{
		vector<pii> out;
		if(p==chip && correctRoom(s, p)) return out;
		for(auto v: reachable(s,p)){
			if(inHallway(v))
				out.push_back(pii(v,0));
		}
		return out;
	}
}

int distance(const pii& st, const pii& en, int n){
	int out = abs(st.y-en.y)+1; // add one because one is hallway
	const vector<int> ordering = {0,5,1,6,2,7,3,8,4,9,10};
	int stpos = find(begin(ordering), end(ordering), st.x) - begin(ordering);
	int enpos = find(begin(ordering), end(ordering), en.x) - begin(ordering);
	return pow(10, n-1)*(out+abs(stpos-enpos));
}

int solve(state& s){
	int p1;
	priority_queue<pair<int,state>, vector<pair<int,state>>, greater<pair<int,state>>> q;
	q.push(make_pair(0,s));
	set<ull> seen;
	while(!q.empty()){
		tie(p1, s) = q.top();
		ull hash = hashState(s);
		q.pop();
		if(seen.insert(hash).second==false) continue; // already in set
		if(solved(s))
			return p1;
		for(int i = 0;i<11;i++){
			int y;
			for(y=0;y<s[i].size()-1 && !s[i][y]; y++);
			for(auto m: getMoves(s, i, y)){
				state t = s;
				int letter = t[i][y];
				swap(t[m.x][m.y], t[i][y]);
				q.push(make_pair(p1+distance(m, pii(i,y), letter), t));
			}
		}
	}
	return -1;
}

chrono::time_point<std::chrono::steady_clock> day23(input_t& inp){
	int p1(0), p2(0);
	state s(11, vector<int>());
	s[0].push_back(0);
	for(int i = 5;i<11;i++) s[i].push_back(0);
	for(int i = 1;i<5;i++) s[i] = {inp[2][1+2*i]-'A'+1, inp[3][1+2*i]-'A'+1};
	state s2(s);
	p1 = solve(s);
	s2[1].insert(begin(s2[1])+1, 4);
	s2[1].insert(begin(s2[1])+1, 4);
	s2[2].insert(begin(s2[2])+1, 2);
	s2[2].insert(begin(s2[2])+1, 3);
	s2[3].insert(begin(s2[3])+1, 1);
	s2[3].insert(begin(s2[3])+1, 2);
	s2[4].insert(begin(s2[4])+1, 3);
	s2[4].insert(begin(s2[4])+1, 1);
	p2 = solve(s2);
	
	auto done = chrono::steady_clock::now();
	cout<<"[P1] "<<p1<<"\n[P2] "<<p2<<endl;
	return done;
}