#include "../aoc.h"
#include <sstream>

int main(){
	fstream file("Day 3/input");
	string line;
	vector<vector<set<int>>> g(1000,vector<set<int>>(1000, set<int>()));
	int id, x, y, w, h;
	char trash;
	set<int> claims;
	int p1 = 0;
	while(getline(file, line)){
		stringstream ss(line);
		ss>>trash>>id>>line>>x>>trash>>y>>trash>>w>>trash>>h;
		claims.insert(id);
		for(int i = y;i<y+h;i++)
			for(int j = x;j<x+w;j++)
				g[i][j].insert(id);
	}

	for(int i = 0;i<1000;i++){
		for(int j = 0;j<1000;j++){
			p1+=(g[i][j].size()>1);
			if(g[i][j].size()>1){
				for(auto& v: g[i][j])
					claims.erase(v);
			}
		}
	}
	cout<<"[P1] "<<p1<<endl;
	cout<<"[P2] "<<*claims.begin()<<endl;
	
}