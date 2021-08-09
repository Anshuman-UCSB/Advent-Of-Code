#include "../aoc.h"
#define GRIDSIZE 50
#define grid vector<vector<char>>

grid m(GRIDSIZE, vector<char>(GRIDSIZE,' '));

map<int, int> cache;

static void print(){
	cout<<endl;
	for(auto& r: m){for(auto& c: r)cout<<c;cout<<endl;}
}

static int count(const int& x, const int& y, const char& l){
	int count = 0;
	for(int i = y-1;i<=y+1;i++){
		for(int j = x-1;j<=x+1;j++){
			if(j == x && y == i) continue;
			try{
				if(m.at(i).at(j) == l) count++;
			}catch(...){}
		}
	}
	return count;
}

// string hashGrid(const grid& g){
// 	string out;
// 	for(int i = 0;i<g.size();i+=9){
// 		for(auto& c: g[i]){
// 			out.append(1, c);
// 		}
// 	}
// 	return out;
// }

int getScore(const grid& m){
	int wood(0), lumber(0);
	for(int y = 0;y<GRIDSIZE;y++){
		for(int x = 0;x<GRIDSIZE;x++){
			if(m[y][x] == '|') wood++;
			else if(m[y][x] == '#') lumber++;
		}
	}
	return lumber*wood;
}

void iter(grid& m){
	grid t(GRIDSIZE, vector<char>(GRIDSIZE));
	for(int y = 0;y<GRIDSIZE;y++){
		for(int x = 0;x<GRIDSIZE;x++){
			switch(m[y][x]){
				case '.':
					if(count(x,y, '|')>=3){
						t[y][x] = '|';
					} 
					else t[y][x] = '.';
					break;
				case '|':
					if(count(x, y, '#')>=3) t[y][x] = '#';
					else t[y][x] = '|';
					break;
				case '#':
					if(!(count(x,y, '#') >=1 && count(x,y,'|')))
						t[y][x] = '.';
					else t[y][x] = '#';
					break;
			}
		}
	}
	m = t;
}

int main(){
	fstream file("Day 18/input");
	string line;
	int y = 0;
	while(getline(file, line)){
		for(int x =0 ;x<GRIDSIZE;x++){
			m[y][x] = line[x];
		}
		y++;
	}
	// print();
	int i;
	for(i = 0;i<10;i++){
		iter(m);
	}
	cout<<"[P1] "<<getScore(m)<<endl;
	for(;i<1000000000;i++){
		iter(m);
		if(i<50000) continue;
		if(cache[getScore(m)]){
			int period = i-cache[getScore(m)];
			i+=((1000000000-i)/period)*period;
		}
		cache[getScore(m)] = i;
	}
	cout<<"[P2] "<<getScore(m)<<endl;
}