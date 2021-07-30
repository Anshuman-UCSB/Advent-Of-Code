#include "../prints.h"
#include <fstream>
#define x first
#define y second
#define coord pair<int, int>

vector<vector<bool>> grid;

void print(){
	for(auto& r: grid){
		for(auto b: r){
			cout<<(b?"#":".");
		}cout<<endl;
	}
}

int dx[4] = {0,1,0,-1};
int dy[4] = {1,0,-1,0};
int getNeighbor1(vector<vector<bool>>& grid, coord c){
	int out = 0;
	for(int i =0;i<4;i++){
		try{
			if(grid.at(c.y+dy[i]).at(c.x+dx[i])){
				out++;
			}
		}catch (const out_of_range& oor){}
	}
	return out;
}

void generation(vector<vector<bool>>& grid){
	vector<vector<bool>> copy = grid;
	int neighbors;
	for(int i= 0;i<grid.size();i++){
		for(int j =0;j<grid[0].size();j++){
			neighbors = getNeighbor1(grid, coord(j, i));
			if(grid[i][j]){
				copy[i][j] = neighbors==1;
			}else{
				if(neighbors == 1 || neighbors == 2){
					copy[i][j] = 1;
				}
			}
		}
	}
	grid = copy;
}

void p1(){
	set<vector<vector<bool>>> cache;
	while(cache.insert(grid).second){
		generation(grid);
		print();
	}
	unsigned int p1 = 0;
	unsigned int mult = 1;
	for(auto& r: grid){
		for(auto v: r){
			p1+=(v?mult:0);
			mult<<=1;
		}	
	}
	cout<<"[P1] "<<p1<<endl;
}

int main(){
	fstream file("Day 24/input");
	string line;
	while(getline(file, line)){
		grid.emplace_back();
		for(auto c: line)
			grid.back().push_back(c=='#');
	}
	p1();
}