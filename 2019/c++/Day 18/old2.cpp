#include <iostream>
#include <fstream>
#include "../prints.h"
#include <vector>
#include <set>
#include <bitset>
#include <queue>
#include <tuple>

using namespace std;

struct Coord{
	int x,y,time;
	long long keys;
	Coord():x(0),y(0),time(0),keys(0){}
	Coord(int x, int y, int time, long long keys):x(x), y(y), time(time), keys(keys){}
	tuple<int, int, long long> toTuple(){
		return make_tuple(x, y, keys);
	}
};

int solveGrid(vector<vector<char>>& inp, int x, int y, int quadr = 0){
	int lx, hx, ly, hy;
	lx = ly = 1;
	hx = inp[0].size()-1;
	hy = inp.size()-1;
	bitset<9> keys;
	// cout<<keys<<endl;
	if(quadr != 0){
		switch(quadr){
			case 1: lx = x; ly = y; break;
			case 2: hx = x; ly = y; break;
			case 3: hx = x; hy = y; break;
			case 4: lx = x; hy = y; break;
		}
		// cout<<lx<<" - > "<<hx<<", "<<ly<<" -> "<<hy<<endl;
		for(int i=ly;i<hy;i++){
			for(int j = lx;j<hx;j++){
				if(islower(inp[i][j])){
					// cout<<"Found key "<<inp[i][j]<<endl;
					// cout<<inp[i][j]-'a'<<endl;
					keys[inp[i][j]-'a']=true;
				}
			}
		}
		// cout<<keys<<endl;
		keys.flip();
	}
	Coord start(x, y, 0, keys.to_ullong()); //give all keys in non quadrant
	// cout<<keys<<endl;
	queue<Coord> q;
	set<tuple<int, int, long long>> cache;
	q.push(start);
	Coord t;
	int dx[4] = {0,1,0,-1};
	int dy[4] = {1,0,-1,0};
	while(!q.empty()){
		t = q.front();
		q.pop();
		keys = t.keys;
		if(keys.all()){
			return t.time;
		}
		cout<<"	 ("<<t.x<<", "<<t.y<<")"<<endl;
		for(int i =0;i<4;i++){
			x = t.x+dx[i];
			y = t.y+dy[i];
			cout<<"checking ("<<x<<", "<<y<<")"<<": ";
			cout<<inp[y][x]<<" ";
			if(inp[y][x] == '#' || cache.find(make_tuple(x, y, t.keys)) != cache.end()){
				cout<<"hit wall/already cached"<<endl;
				continue;
			}

			if(isupper(inp[y][x]) && !keys[inp[y][x]-'A']){
				cout<<"Don't have key for door"<<endl;
				continue; //hit door without key
			}

			if(islower(inp[y][x])){
				cout<<"Picked up "<<inp[y][x]<<endl;
				keys[inp[y][x]-'a']=true; //set
			}
			
			q.push(Coord(x, y, t.time+1, keys.to_ullong()));
			cout<<"Added ("<<x<<", "<<y<<")"<<endl;

			cache.insert(q.back().toTuple());
			
			if(islower(inp[y][x])){
				keys[inp[y][x]-'a']=false; //reset
			}
		}
	}
	return -1;
}

int main(){
	fstream file("Day 18/input");
	string line;
	vector<vector<char>> inp;
	int x, y;
	while(getline(file, line)){
		inp.emplace_back();
		for(auto c: line){
			if(c == '@'){
				x = inp.back().size();
				y = inp.size()-1;
				c = '.';
			}
			inp.back().push_back(c);
		}
	}

	for(auto& r: inp){for(auto& c: r){cout<<c;}cout<<endl;} //print map
	cout<<"[P1] "<<solveGrid(inp, x, y)<<endl;
	exit(1);
	inp[y][x] = '#';
	inp[y][x-1]='#';
	inp[y][x+1]='#';
	inp[y+1][x]='#';
	inp[y-1][x]='#';
	int p2 = 0;
	
	p2+=solveGrid(inp, x-1, y-1, 3);
	p2+=solveGrid(inp, x+1, y-1, 4);
	p2+=solveGrid(inp, x+1, y+1, 1);
	p2+=solveGrid(inp, x-1, y+1, 2);
	cout<<"[P2] "<<p2<<endl; 
	//1819 too low
	//1823 too low
}