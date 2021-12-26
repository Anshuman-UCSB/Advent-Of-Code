#include "AOC.h"

bool iter(vector<vector<char>>& g, const int& w, const int& h){
	bool changed = false;
	int y,x;
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

	vector<vector<char>> g;
	for(auto& l: inp){
		g.emplace_back();
		for(auto& c: l)
			if(c == '.')
				g.back().emplace_back(0);
			else
				g.back().emplace_back(c);
	}
	int w = g[0].size();
	int h = g.size();
	for(p1=1;iter(g,w,h);p1++);
	auto done = chrono::steady_clock::now();
	cout<<"[P1] "<<p1<<endl;
	return done;
}