#include "AOC.h"
#define grid array<array<char, 150>, 150> 

bool iter(grid& g, const int& w, const int& h){
	bool changed = false;
	int x,y;
	char c;
	for(y = 0;y<h;y++){
		c = !g[y][0] && g[y][w-1]=='>';
		for(x = w-1;x>0;x--)
			if(!g[y][x] && g[y][x-1]=='>'){
				changed = g[y][x--] = '>';
				g[y][x] = 0;
			}
		if(c){
			g[y][0] = '>';
			g[y][w-1]=0;
		}
	}
	for(x = 0;x<w;x++){
		c = !g[0][x] && g[h-1][x]=='v';
		for(y = h-1;y>0;y--)
			if(!g[y][x] && g[y-1][x]=='v'){
				changed = g[y--][x] = 'v';
				g[y][x] = 0;
			}
		if(c){
			g[0][x] = 'v';
			g[h-1][x]=0;
		}
	}
	return changed;
}

chrono::time_point<std::chrono::steady_clock> day25(input_t& inp){
	int p1(0), p2(0);

	grid g;
	for(int y = 0;y<inp.size();y++)
		for(int x = 0;x<inp[0].size();x++)
			g[y][x]=inp[y][x]=='.'?0:inp[y][x];
	int w = inp[0].size();
	int h = inp.size();
	for(p1=1;iter(g,w,h);p1++);
	auto done = chrono::steady_clock::now();
	cout<<"[P1] "<<p1<<endl;
	return done;
}