#include "../prints.h"
#include <fstream>
#define x first
#define y second
#define coord pair<int, int>
#define printgrid() cout<<"---------\n";for(auto& p: grids){cout<<"Depth "<<p.first<<":"<<endl;print(p.second);}
vector<vector<bool>> grid;

map<int, vector<vector<bool>>> grids;

void print(vector<vector<bool>>& g = grid){
	for(auto& r: g){
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

/*
  01234
0 ..###
1 ##...
2 #.?.#
3 #.#.#
4 .#.#.
*/

int getNeighbor2(map<int, vector<vector<bool>>>& grids, coord c, int level){
	if(c.x&1 && c.y&1){
		return getNeighbor1(grids[level], c);
	}
	if(c.x == 1 && c.y == 2){
		if(grids.count(level-1)==0){
			grids[level-1] = vector<vector<bool>>(5, vector<bool>(5,0));
		}
		int out = 0;
		for(int y = 0;y<5;y++){
			out+=grids[level-1][y][0]; //if on inside right border, add all inside grids
		}
		return out + getNeighbor1(grids[level], c);
	}
	if(c.x == 3 && c.y == 2){
		if(grids.count(level-1)==0){
			grids[level-1] = vector<vector<bool>>(5, vector<bool>(5,0));
		}
		int out = 0;
		for(int y = 0;y<5;y++){
			out+=grids[level-1][y][4]; //if on inside left border, add all inside grids
		}
		return out + getNeighbor1(grids[level], c);
	}
	if(c.x == 2 && c.y == 1){
		if(grids.count(level-1)==0){
			grids[level-1] = vector<vector<bool>>(5, vector<bool>(5,0));
		}
		int out = 0;
		for(int x = 0;x<5;x++){
			out+=grids[level-1][0][x]; //if on inside right border, add all inside grids
		}
		return out + getNeighbor1(grids[level], c);
	}
	if(c.x == 2 && c.y == 3){
		if(grids.count(level-1)==0){
			grids[level-1] = vector<vector<bool>>(5, vector<bool>(5,0));
		}
		int out = 0;
		for(int x = 0;x<5;x++){
			out+=grids[level-1][4][x]; //if on inside left border, add all inside grids
		}
		return out + getNeighbor1(grids[level], c);
	}
	int out=getNeighbor1(grids[level],c);
	if(c.x == 0){
		if(grids.count(level+1)==0){
			grids[level+1] = vector<vector<bool>>(5, vector<bool>(5,0));
		}
		out+=grids[level+1][2][1];
	}
	if(c.x == 4){
		if(grids.count(level+1)==0){
			grids[level+1] = vector<vector<bool>>(5, vector<bool>(5,0));
		}
		out+=grids[level+1][2][3];
	}
	if(c.y == 0){
		if(grids.count(level+1)==0){
			grids[level+1] = vector<vector<bool>>(5, vector<bool>(5,0));
		}
		out+=grids[level+1][1][2];
	}
	if(c.y == 4){
		if(grids.count(level+1)==0){
			grids[level+1] = vector<vector<bool>>(5, vector<bool>(5,0));
		}
		out+=grids[level+1][3][2];
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

void generation2(map<int, vector<vector<bool>>>& grids){
	auto copy = grids;
	int neighbors;
	vector<int> levels;
	for(auto& p : grids){
		levels.push_back(p.first);
	}
	for(auto level: levels){
		printgrid();
		auto grid = grids[level];
		for(int i = 0;i<5;i++){
			for(int j = 0;j<5;j++){
				neighbors = getNeighbor2(grids, coord(j,i), level);
				if(grids[level][i][j]){
					copy[level][i][j] = neighbors==1;
				}else{
					if(neighbors == 1 || neighbors == 2){
						copy[level][i][j] = 1;
					}
				}
			}
		}
	}
	cout<<copy.size()<<endl;
	grids = copy;
}

void p1(){
	set<vector<vector<bool>>> cache;
	while(cache.insert(grid).second){
		generation(grid);
		// print();
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

void p2(){
	printgrid();
	generation2(grids);
	printgrid();
}

int main(){
	fstream file("Day 24/input");
	string line;
	while(getline(file, line)){
		grid.emplace_back();
		for(auto c: line)
			grid.back().push_back(c=='#');
	}
	grids[0] = grid;
	p1();
	p2();

}