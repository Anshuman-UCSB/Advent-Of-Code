#include "AOC.h"
#define GRIDSIZE 501

int p1solve(vector<vector<bool>>& m){
	int x(m.size()/2), y(m.size()/2);
	int dir = 0;
	int p1 = 0;
	for(int i =0;i<10000;i++){
		if(m[y][x])
			dir+=1;
		else
			dir+=3;
		dir&=0b11;
		m[y][x] = !m[y][x];
		p1+=m[y][x];
		switch(dir){
			case 0:y--;break;
			case 1:x++;break;
			case 2:y++;break;
			case 3:x--;break;
		}
	}
	return p1;
}
int p2solve(vector<vector<int>>& m){
	int x(m.size()/2), y(m.size()/2);
	int dir = 0;
	int p2 = 0;
	for(int i =0;i<10000000;i++){
		switch(m[y][x]){
			case 0: dir+=3;	break;
			case 1: p2++;	break;
			case 2: dir++;	break;
			case 3: dir+=2;	break;
		}
		dir&=0b11;
		m[y][x]++;
		m[y][x]&=0b11;

		switch(dir){
			case 0:y--;break;
			case 1:x++;break;
			case 2:y++;break;
			case 3:x--;break;
		}
	}
	return p2;
}

chrono::time_point<std::chrono::steady_clock> day22(input_t& inp){

	vector<vector<bool>> m1(GRIDSIZE);
	vector<vector<int>> m2(GRIDSIZE);
	for(int i = 0;i<GRIDSIZE;i++){
		m1[i].resize(GRIDSIZE, false);
		m2[i].resize(GRIDSIZE, 0);
	}
	for(int y = 0; y<inp.size();y++){
		for(int x = 0; x<inp.size();x++){
			if(inp[y][x] == '#') {
				m2[GRIDSIZE/2-inp.size()/2+y][GRIDSIZE/2-inp.size()/2+x] = 2;
				m1[GRIDSIZE/2-inp.size()/2+y][GRIDSIZE/2-inp.size()/2+x] = true;
			}
		}
	}
	
	int p1 = p1solve(m1);
	int p2 = p2solve(m2);
	auto done = chrono::steady_clock::now();
	cout<<"[P1] "<<p1<<endl;
	cout<<"[P2] "<<p2<<endl;
	return done;
}