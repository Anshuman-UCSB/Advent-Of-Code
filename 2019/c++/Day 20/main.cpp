#include <iostream>
#include <vector>
#include <set>
#include <fstream>
#include <tuple>
#include <queue>
#include <utility>
#include "../prints.h"
#include <map>
#define x first
#define y second
#define coord pair<int, int>
#define print(m) for(auto& r: (m)){for(auto& ch:r)cout<<ch;cout<<endl;}

using namespace std;

struct Portal{
	string id;
	coord inner, outer;
	Portal(string id=""):id(id){}
	
	void reg(coord pos, bool in){
		if(in){
			inner = pos;
		}else if(outer==coord()){
			outer = pos;
		}else{
			throw("too many registered.");
		}
	}

	pair<int, coord> step(coord portal){
		if(portal != inner && portal != outer)
			return make_pair(0, coord());
		if(portal == inner)
			return make_pair(1, outer);
		return make_pair(-1, inner);
	}

	bool containsSpot(coord spot){
		if(inner == coord() || outer == coord())
			return false;
		return spot == inner || spot == outer;
	}
	bool containsSpot2(coord spot, int level){
		if(inner == coord() || outer == coord())
			return false;
		if (level == 0){
			return spot == inner;
		}else{
			return spot == inner || spot == outer;
		}
	}
};
map<string, Portal> portals;

vector<vector<char>> m;

int dx[4] = {0,1,0,-1};
int dy[4] = {1,0,-1,0};

coord getNearest(coord c){
	if(m[c.y][c.x] == '.'){
		return c;
	}
	for(int i = 0;i<4;i++){
		if(m[c.y+dy[i]][c.x+dx[i]] == '.')
			return coord(c.x+dx[i], c.y+dy[i]);
	}
	return coord(-1,-1);
}

vector<coord> getStep(coord c){
	vector<coord> out;
	for(int i = 0;i<4;i++){
		coord t(c.x+dx[i], c.y+dy[i]);
		if(m[t.y][t.x] == '.'){
			out.push_back(t);
		}else if(isupper(m[t.y][t.x])){
			for(auto& p: portals){
				if(p.second.containsSpot(t)){
					out.push_back(getNearest(p.second.step(t).second));
					break;
				}
			}
		}
	}
	return out;
}

vector<pair<coord, int>> getStep2(coord c, int level){
	vector<pair<coord, int>> out;
	for(int i = 0;i<4;i++){
		coord t(c.x+dx[i], c.y+dy[i]);
		if(m[t.y][t.x] == '.'){
			// cout<<"Valid regular step"<<endl;
			out.push_back(make_pair(t, level));
		}else if(isupper(m[t.y][t.x])){
			for(auto& p: portals){
				if(p.second.containsSpot2(t, level)){
					out.push_back(make_pair(getNearest(p.second.step(t).second), p.second.step(t).first+level));
					break;
				}
			}
		}
	}
	return out;
}

int getAdjWalls(coord c){
	int adj = 0;
	for(int i = 0;i<4;i++){
		if(m[c.y+dy[i]][c.x+dx[i]] == '#')
			adj++;
	}
	return adj;
}

void cleanMap(){
	queue<coord> toClean;
	for(int y = 2;y<m.size()-2;y++){
		for(int x = 2; x<m[y].size()-2;x++){
			if(getAdjWalls(coord(x,y))>=3){
				toClean.push(coord(x, y));
			}
		}
	}
	coord cl;
	while(!toClean.empty()){
		cl = toClean.front();
		toClean.pop();
		if(getAdjWalls(cl)<3)
			continue;
		
		m[cl.second][cl.first] = '#';
		for(int i = 0; i<4;i++){
			coord temp(cl.first+dx[i], cl.second+dy[i]);
			if(m[temp.second][temp.first] != '#'){
				toClean.push(temp);
			}
		}
	}
}

void tryRegister(coord a, coord b, coord closer, bool inner){
	if(!(isupper(m[a.y][a.x])&&isupper(m[b.y][b.x])))
		return;
	
	string name;
	name+=m[a.y][a.x];
	name+=m[b.y][b.x];
	portals[name].id = name;
	portals[name].reg(closer, inner);
}

void p1(){
	coord start = getNearest(portals["AA"].outer);
	// coord start = getNearest(portals["FG"].outer);
	vector<vector<int>> dist(m.size(), vector<int>(m[0].size(), -1));
	queue<pair<coord, int>> q;
	q.push(make_pair(start, 0));
	pair<coord, int> p;

	coord zz = getNearest(portals["ZZ"].outer);

	while(!q.empty()){
		p = q.front();
		q.pop();
		if(dist[p.first.y][p.first.x] != -1 || m[p.first.y][p.first.x] !='.')
			continue;
		// cout<<"at "<<p<<endl;
		if(p.first == zz){
			cout<<"[P1] "<<p.second<<endl;
			break;
		}
		dist[p.first.y][p.first.x] = p.second;
		// cout<<p.first<<endl;
		for(auto& c: getStep(p.first)){
			// cout<<"."<<c<<endl;
			if(c.x>0 && c.y>0)
				q.push(make_pair(c, p.second+1));
		}
	}
	// vector<string> colors = {BOLD,RED, YELLOW, CYAN, GREEN};
	// for(int y = 0;y<dist.size();y++){
	// 	for(int x =0;x<dist[0].size();x++){
	// 		int val = dist[y][x];
	// 		if(val == -1){
	// 			cout<<m[y][x];
	// 		}else{
	// 			cout<<colors[(val/10)%colors.size()]<<val%10<<RESET;
	// 			// cout<<".";
	// 		}
	// 	}cout<<endl;
	// }

	// cout<<"[P1] "<<dist[zz.y][zz.x]<<endl;
}
void p2(){
	coord start = getNearest(portals["AA"].outer);
	// coord start = getNearest(portals["FG"].outer);
	set<pair<coord, int>> visited;
	queue<tuple<coord,int, int>> q;
	q.push(make_tuple(start, 0, 0)); //coord, time, level
	tuple<coord,int, int> p;

	coord zz = getNearest(portals["ZZ"].outer);

	coord c;
	int time, level;
	while(!q.empty()){
		p = q.front();
		c = get<0>(p);
		time = get<1>(p);
		level = get<2>(p);
		// cout<<c<<" t"<<time<<" l"<<level<<endl;
		q.pop();
		if(visited.insert(make_pair(c, level)).second == false || m[c.y][c.x] !='.'){
			// cout<<"Already seen"<<endl;
			continue;
		}
		// cout<<"at "<<p<<endl;
		if(c == zz && level == 0){
			cout<<"[P2] "<<time<<endl;
			break;
		}
		// cout<<p.first<<endl;
		for(auto& val: getStep2(c, level)){
			// cout<<"	"<<val.first<<endl;
			// cout<<"."<<c<<endl;
			if(val.first.x>0 && val.first.y>0)
				q.push(make_tuple(val.first, time+1, val.second));
		}
	}
	// vector<string> colors = {BOLD,RED, YELLOW, CYAN, GREEN};
	// for(int y = 0;y<dist.size();y++){
	// 	for(int x =0;x<dist[0].size();x++){
	// 		int val = dist[y][x];
	// 		if(val == -1){
	// 			cout<<m[y][x];
	// 		}else{
	// 			cout<<colors[(val/10)%colors.size()]<<val%10<<RESET;
	// 			// cout<<".";
	// 		}
	// 	}cout<<endl;
	// }

	// cout<<"[P1] "<<dist[zz.y][zz.x]<<endl;
}

int main(){
	fstream file("Day 20/input");
	string line;
	while(getline(file, line)){
		m.emplace_back();
		for(auto c: line){
			m.back().push_back(c);
		}
	}
	
	int thickness = 0;
	for(;m[thickness+2][thickness+2]!=' ';thickness++){}
	int lx, hx, ly, hy;
	lx = 2+thickness;
	hx = m[0].size()-3-thickness;
	ly = 2+thickness;
	hy = m.size()-3-thickness;
	for(int y = 2;y<m.size()-2;y++){
		tryRegister(coord(0,y), coord(1,y), coord(1,y), false); //false cause not inner
		tryRegister(coord(m[0].size()-2,y), coord(m[0].size()-1,y), coord(m[0].size()-2,y), false); //false cause not inner
		tryRegister(coord(lx,y),coord(lx+1,y),coord(lx,y),true);
		tryRegister(coord(hx-1,y),coord(hx,y),coord(hx,y),true);
	}
	for(int x = 2;x<m[0].size()-2;x++){
		tryRegister(coord(x,0), coord(x,1), coord(x,1), false); //false cause not inner
		tryRegister(coord(x,m.size()-2), coord(x,m.size()-1), coord(x,m.size()-2), false); //false cause not inner
		tryRegister(coord(x,ly),coord(x,ly+1),coord(x,ly),true);
		tryRegister(coord(x, hy-1),coord(x,hy),coord(x,hy),true);
	}

	// print(m);
	cleanMap();
	// print(m);
	// for(auto& p: portals){
	// 	cout<<p.first<<"	"<<p.second.inner<<", 	"<<p.second.outer<<endl;
	// }
	p1();
	p2();
}