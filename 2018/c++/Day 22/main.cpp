#include "../aoc.h"
#define Coord tuple<int, int, int>
#define MOD 20183
#define x first
#define y second

map<pair<int, int>, int> m;
int depth;
pair<int, int> target;

int modMult(int a,int b){
	int out = 0;
	a%=MOD;
	while(b){
		if(b&1)
			out = (out+a)%MOD;
		a = (2*a)%MOD;
		b>>=1;
	}
	return out;
}

int& at(int x, int y){
	if(auto it = m.find(make_pair(x,y)); it!=m.end())
		return (*it).second;
	if(x == 0 && y == 0){
		m[make_pair(x, y)] = 0;
	}
	if(x == 0 || y == 0){
		m[make_pair(x, y)] = (modMult(x, 16807) + modMult(y, 48271) + depth)%MOD;
		return m[make_pair(x, y)];
	}
	m[make_pair(x, y)] = (modMult(at(x-1, y), at(x, y-1)) + depth)%MOD;
	return m[make_pair(x, y)];
}

int main(){
	fstream file("Day 22/input");
	string t;
	char tr;
	file>>t>>depth;
	file>>t>>target.x>>tr>>target.y;
	// 0 		1 		2
	// rock 	wet 	narrow
	// nothing	torch	climbing
	at(target.x, target.y);
	int p1 = 0;
	for(auto& [k, v]: m){
		p1+=v%3;
	}
	p1-=m[target]%3;
	cout<<"[P1] "<<p1<<endl;
}