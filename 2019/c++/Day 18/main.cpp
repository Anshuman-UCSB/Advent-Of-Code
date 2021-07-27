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

int main(){
	fstream file("Day 18/input");
	string line;
	vector<vector<char>> inp;
	set<tuple<int, int, long long>> cache;
	queue<Coord> q;
	Coord start;
	while(getline(file, line)){
		inp.emplace_back();
		for(auto c: line){
			if(c == '@'){
				start = Coord(inp.back().size()-1, inp.size()-1, 0, 0);
				c = '.';
			}
			inp.back().push_back(c);
		}
	}

	q.push(start);
	// cache.insert(start.toTuple());
	
	Coord t;
	bitset<26> keys;
	int dx[4] = {0,1,0,-1};
	int dy[4] = {1,0,-1,0};
	int x, y;
	while(!q.empty()){
		t = q.front();
		q.pop();
		keys = t.keys;
		if(keys.all()){
			cout<<"[P1] "<<t.time-1<<endl;
			break;
		}
		// cout<<"	 ("<<t.x<<", "<<t.y<<")"<<endl;
		for(int i =0;i<4;i++){
			x = t.x+dx[i];
			y = t.y+dy[i];
			// cout<<"checking ("<<x<<", "<<y<<")"<<": ";
			// cout<<inp[y][x]<<" ";
			if(inp[y][x] == '#' || cache.find(make_tuple(x, y, t.keys)) != cache.end()){
				// cout<<"hit wall/already cached"<<endl;
				continue;
			}

			if(isupper(inp[y][x]) && !keys[inp[y][x]-'A']){
				// cout<<"Don't have key for door"<<endl;
				continue; //hit door without key
			}

			if(islower(inp[y][x])){
				// cout<<"Picked up "<<inp[y][x]<<endl;
				keys[inp[y][x]-'a']=true; //set
			}
			
			q.push(Coord(x, y, t.time+1, keys.to_ullong()));
			// cout<<"Added ("<<x<<", "<<y<<")"<<endl;

			cache.insert(q.back().toTuple());
			
			if(islower(inp[y][x])){
				keys[inp[y][x]-'a']=false; //reset
			}
		}
	}

	// for(auto& r: inp){for(auto& c: r){cout<<c;}cout<<endl;} //print map

}