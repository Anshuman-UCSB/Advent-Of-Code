#include <iostream>
#include <cassert>
#include <fstream>
#include <map>
#include <vector>
#include <sstream>
#include "../prints.h"
#include <algorithm>
#include <set>
#include <queue>
#include <utility>

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
string keyList;
int dx[4] = {0,1,0,-1};
int dy[4] = {1,0,-1,0};

int p1(vector<vector<char>>& m, Coord& start){
	queue<Coord> q;
	q.push(start);
	set<string> cache;
	cache.insert(start.hash());
	Coord t;
	Coord dt;
	while(!q.empty()){
		t = q.front();
		q.pop();
		for(int i =0;i<4;i++){
			int x(t.x+dx[i]), y(t.y+dy[i]);
			dt = Coord(x, y, t.time+1, t.keys);

			if(dt.keys.size() == keyCount){
				// cout<<dt.keys<<endl;
				return t.time;
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
	cout<<"Couldn't solve"<<endl;
	return -1;
}

int p2(vector<vector<char>>& m, Coord& start){
	int x, y;
	x = start.x;
	y = start.y;
	m[y][x] = '#';
	m[y][x-1] = '#';
	m[y][x+1] = '#';
	m[y+1][x] = '#';
	m[y-1][x] = '#';
	
	// for(auto& r:m){for(auto& v:r)cout<<v;cout<<endl;}
	Coord aStart(x-1, y-1);
	Coord bStart(x+1, y-1);
	Coord cStart(x-1, y+1);
	Coord dStart(x+1, y+1);

	/*   -
	A B  y
	C D  +
	- x +
	*/

	for(int j = 0;j<m.size();j++){
		for(int i = 0;i<m[j].size();i++){
			if(islower(m[j][i])){
				if(i<x){
					if(j<y){
						// cout<<"Key "<<m[j][i]<<" in A."<<endl;
						bStart.keys+=m[j][i];
						cStart.keys+=m[j][i];
						dStart.keys+=m[j][i];
					}else{
						// cout<<"Key "<<m[j][i]<<" in C."<<endl;
						aStart.keys+=m[j][i];
						bStart.keys+=m[j][i];
						dStart.keys+=m[j][i];
					}
				}else{
					if(j<y){
						// cout<<"Key "<<m[j][i]<<" in B."<<endl;
						aStart.keys+=m[j][i];
						cStart.keys+=m[j][i];
						dStart.keys+=m[j][i];
					}else{
						// cout<<"Key "<<m[j][i]<<" in D."<<endl;
						aStart.keys+=m[j][i];
						bStart.keys+=m[j][i];
						cStart.keys+=m[j][i];
					}
				}
			}
		}
	}
	int a=p1(m, aStart);
	int b=p1(m, bStart);
	int c=p1(m, cStart);
	int d=p1(m, dStart);
	cout<<"A: "<<a<<endl;
	cout<<"B: "<<b<<endl;
	cout<<"C: "<<c<<endl;
	cout<<"D: "<<d<<endl;
	return a + b + c + d;
}

bool isDeadEnd(const vector<vector<char>>& m, int x, int y){
	int neighbors = 0;
	for(int i =0;i<4;i++){
		if(m[y+dy[i]][x+dx[i]] == '#'){
			neighbors++;
		}
	}
	return neighbors>=3;
}

void cleanMaze(vector<vector<char>>& m){
	queue<pair<int, int>> q;
	for(int i =1 ;i<m.size()-1;i++){
		for(int j= 1;j<m[i].size()-1;j++){
			if(m[i][j] == '.' && isDeadEnd(m, j, i)){
				q.push(make_pair(j, i));
			}
		}
	}

	pair<int, int> p;
	int x, y;
	while(!q.empty()){
		// cout<<"|";
		p = q.front();
		q.pop();
		x = p.first;
		y = p.second;
		assert(m[y][x]=='.');
		m[y][x] = '#';
		for(int i = 0;i<4;i++){
			if(m[y+dy[i]][x+dx[i]] == '.' && isDeadEnd(m, x+dx[i], y+dy[i])){
				q.push(make_pair(x+dx[i], y+dy[i]));
			}
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
				// c = '.';
			}
			if(islower(c)){
				keyCount++;
				keyList+=c;
			}
			m.back().push_back(c);
		}
	}
	// for(auto& r:m){for(auto& v:r)cout<<v;cout<<endl;}
	cleanMaze(m);
	// for(auto& r:m){for(auto& v:r)cout<<v;cout<<endl;}
	// cout<<"Max key is "<<char(keyCount+'a'-1)<<endl;
	cout<<"[P1] "<<p1(m, start)<<endl;
	cout<<"[P2] "<<p2(m, start)<<endl;
	// for(auto& r:m){for(auto& v:r)cout<<v;cout<<endl;}
}