#include <iostream>
#include <vector>
#include <fstream>
#include <utility>
#include <map>
#include <set>
#include "../util.h"
#include <math.h>
using namespace std;

void print(const vector<vector<bool>>& map){
	for(auto& v: map){
		for(auto c: v){
			cout<<(c?'#':'.');
		}cout<<endl;
	}
}

int gcd(int a, int b){
    if (a == 0)
       return b;
    if (b == 0)
       return a;
    // base case
    if (a == b)
        return a;
    // a is greater
    if (a > b)
        return gcd(a-b, b);
    return gcd(a, b-a);
}

int getNeighbors(const vector<vector<bool>>& map, int x, int y){
	set<pair<int, int>> los;
	for(int i = 0;i<map.size();i++){
		for(int j = 0;j<map[i].size();j++){
			// (j,i) -> (x,y)
			if(i == y && j == x)
				continue;
			if(map[i][j]){
				auto f = make_pair(i-y, j-x);
				// cout<<f<<" -> ";
				int divs = gcd(abs(f.first), abs(f.second));
				f.first/=divs;
				f.second/=divs;
				// cout<<f<<endl;
				los.insert(f);
			}
		}
	}
	return los.size();
}

double dist(pair<int, int>& a, int b){
	return pow(a.first-b/100, 2)+pow(a.second-b%100, 2);
}

void p2(const vector<vector<bool>>& aster, pair<int, int>& best){
	map<double, vector<int> > m;
	int x = best.first;
	int y = best.second;
	for(int i = 0;i<aster.size();i++){
		for(int j = 0;j<aster[i].size();j++){
			// (j,i) -> (x,y)
			if(i == y && j == x)
				continue;
			if(aster[i][j]){
				auto f = make_pair(j-x, y-i);
				// cout<<f<<" -> ";
				int divs = gcd(abs(f.first), abs(f.second));
				f.first/=divs;
				f.second/=divs;
				// cout<<f<<endl;
				double deg = atan2(f.first,f.second)*180/3.14159;
				if(deg<0)
					deg+=360;
				m[deg].push_back(j*100+i);
			}
		}
	}
	int iter = 0;
	for(auto& p:m){
		bool done = false;
		while(!done){
			done = true;
			for(int i =0;i<p.second.size()-1;i++){
				if(dist(best, p.second[i]) > dist(best, p.second[i+1])){
					done = false;
					swap(p.second[i], p.second[i+1]);
				}
			}
		}
	}
	while(true){
		for(auto& p:m){
			if(!p.second.empty()){
				if(++iter == 200){
					cout<<"[P2] "<<p.second.front()<<endl;
					return;
				}
				// cout<<"The "<<iter<<"th asteroid to be vaporized is "<<p.second.front()<<endl;
				p.second.erase(p.second.begin());
			}
		}
	}
}

int main(){
	fstream file("Day 10/input");
	string line;
	vector<vector<bool>> asteroids;
	while(getline(file, line)){
		asteroids.emplace_back();
		if(line.back() == '\r')
			line.pop_back();
		for(auto c: line){
			asteroids.back().push_back(c=='#'?1:0);
		}
	}
	//read input to asteroids
	vector<vector<int>> view;
	int p1 = 0;
	pair<int, int> best;
	int nb;
	for(int y = 0;y<asteroids.size();y++){
		for(int x = 0;x<asteroids[y].size();x++){
			if(asteroids[y][x]){
				nb = getNeighbors(asteroids, x, y);
				if(nb>p1){
					best = make_pair(x, y);
					p1 = nb;
				}
			}
		}
	}
	cout<<"[P1] "<<p1<<endl;
	// print(asteroids);
	p2(asteroids, best);

}