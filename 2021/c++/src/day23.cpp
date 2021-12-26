#include "AOC.h"
#include <cstdint>
#define num uint_fast8_t
#define hallway array<num, 7>
#define toNum(x) (x+1-'A')
#define toChr(x) (x?x-1+'A':'.')


struct state{
	hallway hw{};
	array<array<num,4>, 4> rooms;
	ull hash() const {
		ull out = 0;
		for(auto& v: hw)
			out = (out<<3)+v;
		for(auto& r: rooms)
			for(auto& v: r)
				out = (out<<3)+v;
		return out;
	}
};
ostream& operator<<(ostream& os, const state& s){
	vector<string> base = {
		"#############",
		"#...........#",
		"###?#?#?#?###",
		"  #?#?#?#?#",
		"  #?#?#?#?#",
		"  #?#?#?#?#",
		"  #########"
	};
	for(int i = 0;i<4;i++)
		for(int j = 0;j<4;j++)
			base[2+j][3+i*2]=toChr(s.rooms[i][j]);
	base[1][1]=toChr(s.hw[0]);
	base[1][11]=toChr(s.hw[6]);
	for(int i = 1;i<6;i++)
		base[1][i*2]=toChr(s.hw[i]);
	for(auto& l:base)
		os<<l<<endl;
	return os;
}
struct comp{
	bool operator() (const pair<int, state>& a, const pair<int, state>& b){
		return a.first>b.first;
	}
};

bool correctRoom(state& s, int r){
	for(auto& v: s.rooms[r])
		if(v != 0 && v != r+1)
			return false;
	return true;
}

bool solved(state& s){
	for(int i = 0;i<4;i++)
		for(auto& v: s.rooms[i])
			if(v != i+1)	return false;
	return true;
}

int roomPosY(state& s, int room){
	assert(correctRoom(s, room));
	for(int i = 0;i<4;i++)
		if(s.rooms[room][i]) return i-1;
	return 3;
}

bitset<7> visitable(state& s, int p, bool room){
	bitset<7> out;
	num t;
	if(!room){
		t = s.hw[p];
		s.hw[p] = 0;
	}else
		p++;
	for(int i = p;i>=0 && s.hw[i]==0;i--)
		out[i]=true;
	for(int i = p+1;i<7 && s.hw[i]==0;i++)
		out[i]=true;
	s.hw[p] = t;
	return out;
}

static int multiplier[5] = {-1,1,10,100,1000};
static int rm2hw[4][7] = {
	{3,2,2,4,6,8,9},
	{5,4,2,2,4,6,7},
	{7,6,4,2,2,4,5},
	{9,8,6,4,2,2,3}
};
int getDistance(const pii& st, const pii& en, num letter){
	// assert(st.x>=10 != en.x >= 10); //moving from room to hallway or vice versa
	int offset = abs(st.y-en.y);
	if(st.x>=10) // first one is a room
		return multiplier[letter]*(rm2hw[st.x-10][en.x]+offset);
	return multiplier[letter]*(rm2hw[en.x-10][st.x]+offset);
}

vector<pii> getMoves(state& s, int pos, bool room){
	vector<pii> out;
	if(room){
		bitset<7> hwVisitable = visitable(s, pos, true);
		for(int i = 0;i<7;i++)
			if(hwVisitable[i])
				out.emplace_back(i, 0);
	}else{
		num letter = s.hw[pos];
		if(!correctRoom(s, letter-1)) return out;
		bitset<7> hwVisitable = visitable(s, pos, false);
		if(hwVisitable[letter] || hwVisitable[letter+1]){
			int targetY = roomPosY(s, letter-1);
			if(targetY != -1)
				out.emplace_back(letter+9, targetY); // rooms are x-10
		}
	}
	return out;
}

int solve(state& s){
	priority_queue<pair<int, state>, vector<pair<int, state>>, comp> q;
	unordered_set<ull> seen;
	q.push(make_pair(0,s));
	int cost;
	num letter;
	while(!q.empty()){
		tie(cost, s) = q.top();
		q.pop();
		if(seen.insert(s.hash()).second==false) continue;
		if(solved(s))	return cost;
		for(int i = 0;i<7;i++){
			letter = s.hw[i];
			if(letter)
				for(auto& m: getMoves(s, i, false)){
					state t(s);
					swap(t.hw[i], t.rooms[m.x-10][m.y]);
					q.push(make_pair(cost+getDistance(pii(i,0),m, letter), t));
				}
		}
		for(int i = 0;i<4;i++){
			int j;
			for(j=0;j<4&&(s.rooms[i][j]==0);j++);
			letter = s.rooms[i][j];
			if(letter)
				for(auto& m: getMoves(s, i, true)){
					state t(s);
					swap(t.hw[m.x], t.rooms[i][j]);
					q.push(make_pair(cost+getDistance(pii(i+10,j), m, letter), t));
				}
		}
	}
	return -1;
}

chrono::time_point<std::chrono::steady_clock> day23(input_t& inp){
	state s, s2;
	for(int i = 0;i<4;i++)
		s.rooms[i][2]=s.rooms[i][3]=i+1;
	for(int i = 0;i<4;i++){
		s.rooms[i][0]=toNum(inp[2][3+2*i]);		s.rooms[i][1]=toNum(inp[3][3+2*i]);
		s2.rooms[i][0]=toNum(inp[2][3+2*i]);	s2.rooms[i][3]=toNum(inp[3][3+2*i]);
	}
		// #D#C#B#A#
		// #D#B#A#C#
	s2.rooms[0][1]=4;	s2.rooms[0][2]=4;
	s2.rooms[1][1]=3;	s2.rooms[1][2]=2;
	s2.rooms[2][1]=2;	s2.rooms[2][2]=1;
	s2.rooms[3][1]=1;	s2.rooms[3][2]=3;
	
	int p1(solve(s)), p2(solve(s2));

	auto done = chrono::steady_clock::now();
	cout<<"[P1] "<<p1<<"\n[P2] "<<p2<<endl;
	return done;
}