#include "../aoc.h"
#include <sstream>
#include <tuple>
#define claim tuple<int, int, int, int>

int main(){
	vector<claim> claims;
	fstream file("Day 3/input");
	string line;
	char trash;
	int x, y, w, h;
	vector<vector<int>> m(1000,vector<int>(1000));
	while(getline(file, line)){
		stringstream ss(line);
		ss>>line>>line>>x>>trash>>y>>trash>>w>>trash>>h;
		claims.emplace_back(x,y,w,h);
		for(int i = x;i<x+w;i++){
			for(int j = y;j<y+h;j++){
				m[j][i]++;
			}
		}
	}
	int p1 = 0;
	x = y = -1;
	for(int i = 0;i<m.size();i++){
		for(int j = 0;j<m.size();j++){
			if(m[i][j] == 1 && x == -1){
				x = j;
				y = i;
			}
			p1+=(m[i][j]>=2);
		}
	}
	cout<<x<<" "<<y<<endl;
	cout<<"[P1] "<<p1<<endl;
}