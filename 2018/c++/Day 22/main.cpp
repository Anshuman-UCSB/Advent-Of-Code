#include "../aoc.h"
#include <queue>
#define Coord tuple<int, int, int>
#define state tuple<int, int, int, int>
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
//state
// min x y cannot
static int distTo(const state& a, const pair<int, int>& targ){
	return abs(get<1>(a)-targ.x)+abs(get<2>(a)-targ.y);
}

static bool compare(const state& a, const state& b){
	if(get<0>(a) < get<0>(b)) return false;
	if(get<0>(a) == get<0>(b)){
		if(distTo(a, target) < distTo(b, target)){
			return false;
		}
	}
	return true;
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
	priority_queue<state, vector<state>, decltype(&compare)> q(compare);
	Coord finish = make_tuple(target.x, target.y, 1);
	map<Coord, int> best;

	q.push(make_tuple(0,0,0,1)); //0 min, (0,0) with torch

	int dx[4] = {0,1,0,-1};
	int dy[4] = {-1,0,1,0};

	while(!q.empty()){
		auto [t, x, y, cannot] = q.top();
		q.pop();
		auto bestKey = make_tuple(x,y,cannot);
		if(best.count(bestKey) && best[bestKey]<=t)
			continue;
		best[bestKey] = t;
		if(bestKey == finish){
			cout<<"[P2] "<<t<<endl;
			return 0;
		}
		for(int i =0;i<3;i++)
			if(i!=cannot && i != at(x, y)%3)
				q.push(make_tuple(t+7,x,y,i));
		
		for(int i = 0;i<4;i++){
			auto temp = make_tuple(t+1, x+dx[i], y+dy[i], cannot);
			if(get<1>(temp)<0 || get<2>(temp)<0)
				continue;
			if(at(get<1>(temp), get<2>(temp))%3 == cannot)
				continue;
			q.push(temp);
		}
	}
}