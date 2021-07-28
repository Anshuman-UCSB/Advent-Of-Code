#include <iostream>
#include <fstream>
#include <map>
#include <vector>
#include <sstream>
#include "../prints.h"
#include <algorithm>
#include <set>
#include <queue>


using namespace std;

struct Coord{
	int x, y, time;
	string keys;
	Coord(int x = 0, int y = 0, int time = 0, string keys = ""):x(x), y(y), time(time), keys(keys){};

	bool hasKey(char key){
		char look = tolower(key);
		for(auto& c: keys)
			if(c == look)
				return true;
		return false;
	}

	string hash(){
		string temp = keys;
		sort(temp.begin(), temp.end());
		return to_string(x)+","+to_string(y)+"-"+temp;
	}

	void print(){
		cout<<"("<<x<<", "<<y<<"), "<<time<<" - \""<<keys<<"\""<<endl;
	}
};
int keyCount(0);
void p1(vector<vector<char>>& m, Coord& start){
	queue<Coord> q;
	q.push(start);
	set<string> cache;
	cache.insert(start.hash());
	Coord t;
	Coord dt;
	int dx[4] = {0,1,0,-1};
	int dy[4] = {1,0,-1,0};
	while(!q.empty()){
		t = q.front();
		q.pop();
		for(int i =0;i<4;i++){
			int x(t.x+dx[i]), y(t.y+dy[i]);
			dt = Coord(x, y, t.time+1, t.keys);

			if(dt.keys.size() == keyCount){
				// cout<<dt.keys<<endl;
				cout<<"[P1] "<<t.time<<endl;
				return;
			}

			if(cache.count(dt.hash()))
				continue;		//Seen before earlier
			if(m[y][x] == '#')
				continue;		//Wall
			if(isupper(m[y][x]))
				if(!dt.hasKey(m[y][x]))
					continue; 	//Can't go here, no key
			
			if(islower(m[y][x]) && !dt.hasKey(m[y][x])){
				dt.keys += m[y][x];
			}
			q.push(dt);
			cache.insert(dt.hash());
		}
	}
}

int main(){
	fstream file("Day 18/input");
	string line;
	vector<vector<char>> m;
	keyCount = 0;
	Coord start;
	while(getline(file, line)){
		m.emplace_back();
		for(auto c: line){
			if(c == '@'){
				start = Coord(m.back().size(), m.size()-1);
				c = '.';
			}
			if(islower(c)){
				keyCount = max(keyCount, c-'a'+1);
			}
			m.back().push_back(c);
		}
	}
	// cout<<"Max key is "<<char(keyCount+'a'-1)<<endl;
	p1(m, start);
	// for(auto& r:m){for(auto& v:r)cout<<v;cout<<endl;}
}