#include <iostream>
#include <fstream>
#include <map>
#include "../prints.h"
#include <utility>
#include <queue>
#define c pair<int, int>
#include <vector>
#define print(m) for(auto& r: (m)){for(auto& ch:r)cout<<ch;cout<<endl;}

using namespace std;

map<c, c> portals;
map<string, c> portalPos;
vector<vector<char>> m;
int dx[4] = {0,1,0,-1};
int dy[4] = {1,0,-1,0};
void registerPortalHoriz(int x, int x2, int px, int y){
	if(!isupper(m[y][x]) || !isupper(m[y][x]))
		return;
	string portalName;
	portalName += m[y][x];
	portalName += m[y][x2];
	c portalLoc = make_pair(px, y);
	if(portalPos.count(portalName)){
		portals[portalLoc] = portalPos[portalName];
		portals[portalPos[portalName]] = portalLoc;
	}else{
		portalPos[portalName] = portalLoc;
	}
}
void registerPortalVert(int y, int y2, int py, int x){
	if(!isupper(m[y][x]) || !isupper(m[y2][x]))
		return;
	string portalName;
	portalName += m[y][x];
	portalName += m[y2][x];
	// cout<<x<<", "<<y;
	// cout<<" V> "<<portalName<<endl;
	c portalLoc = make_pair(x, py);
	if(portalPos.count(portalName)){
		portals[portalLoc] = portalPos[portalName];
		portals[portalPos[portalName]] = portalLoc;
	}else{
		portalPos[portalName] = portalLoc;
	}
}

c findValidSpot(c& t){
	int x, y;
	// c t = portalPos["AA"];
	x = t.first;
	y = t.second;
	for(int i = 0;i<4;i++){
		if(m[y+dy[i]][x+dx[i]] == '.'){
			return make_pair(x+dx[i], y+dy[i]);
		}
	}
}

vector<c> getNeighbors(c& coord){
	int x(coord.first), y(coord.second);
	vector<c> out;
	for(int i = 0;i<4;i++){
		if(m[y+dy[i]][x+dx[i]] == '.'){
			out.emplace_back(x+dx[i], y+dy[i]);
		}else if(isupper(m[y+dy[i]][x+dx[i]])){
			if(portals.count(make_pair(x+dx[i],y+dy[i])))
				out.push_back(findValidSpot(portals[make_pair(x+dx[i],y+dy[i])]));
		}
	}
	return out;
}

int getAdjWalls(c coord){
	int adj = 0;
	for(int i =0;i<4;i++){
		if(m[coord.second+dy[i]][coord.first+dx[i]] == '#'){
			adj++;
		}
	}
	return adj;
}

void cleanMap(){
	queue<c> toClean;
	for(int y = 2;y<m.size()-2;y++){
		for(int x = 2; x<m[y].size()-2;x++){
			if(getAdjWalls(c(x,y))>=3){
				toClean.push(c(x, y));
			}
		}
	}
	c cl;
	while(!toClean.empty()){
		cl = toClean.front();
		toClean.pop();
		if(getAdjWalls(cl)<3)
			continue;
		
		m[cl.second][cl.first] = '#';
		for(int i = 0; i<4;i++){
			c temp(cl.first+dx[i], cl.second+dy[i]);
			if(m[temp.second][temp.first] != '#'){
				toClean.push(temp);
			}
		}
	}
}

int main(){
	fstream file("Day 20/input");
	string line;
	while(getline(file, line)){
		m.emplace_back();
		for(auto ch: line){
			m.back().push_back(ch);
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
		registerPortalHoriz(0, 1, 1, y);
		registerPortalHoriz(lx, lx+1, lx, y);
		registerPortalHoriz(hx-1, hx, hx, y);
		registerPortalHoriz(m[0].size()-2, m[0].size()-1, m[0].size()-2, y);
	}
	for(int x = 2;x<m[0].size()-2;x++){
		registerPortalVert(0,1,1,x);
		registerPortalVert(ly,ly+1,ly,x);
		registerPortalVert(hy-1,hy, hy, x);
		registerPortalVert(m.size()-2,m.size()-1,m.size()-2,x);
	}
	
	// print(m);
	// cout<<portals<<endl;
	// cout<<portalPos<<endl;

	// c start = findValidSpot(portalPos["AA"]);
	queue<pair<c, int>> q;
	vector<vector<int>> dist(m.size(), vector<int>(m[0].size(),-1));
	q.push(make_pair(findValidSpot(portalPos["AA"]), 0));
	pair<c, int> t;
	c p1Loc = findValidSpot(portalPos["ZZ"]);
	print(m);
	cleanMap();
	print(m);
	
	while(!q.empty()){
		t = q.front();
		if(t.first == p1Loc){
			cout<<"[P1] "<<t.second<<endl;
		}
		dist[t.first.second][t.first.first] = t.second;
		q.pop();
		for(auto coord: getNeighbors(t.first)){
			if(dist[coord.second][coord.first] == -1){
				q.push(make_pair(coord, t.second+1));
			}
		}
	}
	// vector<string> colors = {RED, YELLOW, CYAN, GREEN};
	// for(auto& r: dist){
	// 	for(auto val: r){
	// 		if(val == -1){
	// 			cout<<" ";
	// 		}else{
	// 			cout<<colors[(val/10)%colors.size()]<<val%10<<RESET;
	// 		}
	// 	}cout<<endl;
	// }
}