#include <set>
#include <iostream>
#include <fstream>
#include <vector>
#include <map>
#include <queue>
#include "../coord.h"
#include "../prints.h"
using namespace std;

struct Instance{
	vector<vector<char>> m;
	vector<vector<int>> dist;
	map<char, Coord> keys, doors;
	int time;
	Coord pos;
	Instance():time(0){}
	Instance(const Instance& inst, int t, const Coord& npos){
		for(auto& r: inst.m){
			m.emplace_back(r);
		}
		dist = vector<vector<int>>(m.size(), vector<int>(m[0].size(), -1));
		time = inst.time + t;
		keys = inst.keys;
		doors = inst.doors;
		pos = npos;
		char claimed = m[pos.y][pos.x];
		if('a'<=claimed && claimed<='z'){
			keys.erase(claimed);
			m[pos.y][pos.x] = '.';
			Coord doorLoc = doors[claimed-'a'+'A'];
			m[doorLoc.y][doorLoc.x] = '.';
		}
	}
};

void BFS(Instance &i){
	queue<Coord> q;
	i.dist[i.pos.y][i.pos.x] = 0;
	q.push(i.pos);
	Coord t;
	Coord dt;
	while(!q.empty()){
		t = q.front();
		q.pop();
		for(auto& dx: dirMod){
			dt = t+dx;
			if(i.m[dt.y][dt.x]!='#' && !('A'<=i.m[dt.y][dt.x] && 'Z'>=i.m[dt.y][dt.x]) && i.dist[dt.y][dt.x] == -1){
				// cout<<i.m[dt.y][dt.x]<<endl;
				// if not wall or door, and unseen
				q.push(dt);
				i.dist[dt.y][dt.x] = i.dist[t.y][t.x]+1;
			}
		}
	}
}

void printMap(const vector<vector<char>>& m){
	for(auto& r: m){
		for(auto& c: r){
			cout<<c;
		}cout<<endl;
	}
}
void printMap(const Instance& i){
	printMap(i.m);
}

int p1(Instance& i){
	if(i.keys.empty()){
		return i.time;
	}
	BFS(i);
	int out = 2147483647;
	for(auto& p: i.keys){
		if(i.dist[p.second.y][p.second.x] != -1){
			Instance n(i, i.dist[p.second.y][p.second.x], p.second);
			out = min(out, p1(n));
		}
	}
	return out;
}

int main(){
	string line;
	fstream file("Day 18/input");
	// map<char, Coord> keys, doors;
	Instance inp;
	while(getline(file, line)){
		inp.m.emplace_back();
		for(auto c: line){
			inp.m.back().push_back(c);
			if('a'<=c && c<='z'){
				inp.keys[c] = Coord(inp.m.back().size()-1, inp.m.size()-1);
			}
			else if('A'<=c && c<='Z'){
				inp.doors[c] = Coord(inp.m.back().size()-1, inp.m.size()-1);
			}else if(c=='@'){
				inp.pos = Coord(inp.m.back().size()-1, inp.m.size()-1);
			}
		}
	}
	inp.dist = vector<vector<int>>(inp.m.size(), vector<int>(inp.m[0].size(), -1));
	

	printMap(inp);
	// cout<<"[P1] "<<p1(inp)<<endl;
	
	// vector<vector<int>> dist = BFS(m, start);
	// cout<<dist[1]<<endl;

}