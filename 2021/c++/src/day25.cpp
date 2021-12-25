#include "AOC.h"

bool iter(vector<vector<char>>& g, const int& w, const int& h){
	bool changed = false;
	for(int y = 0;y<h;y++)
		for(int x = 0;x<w;x++)
			if(g[y][x] == '>' && g[y][(x+1)%w]=='.')
				g[y][x] = 'M';
	for(int y = 0;y<h;y++)
		for(int x = 0;x<w;x++)
			if(g[y][x] == 'M'){
				changed = true;
				g[y][x] = '.';	
				g[y][(x+1)%w] = '>';
			}
	for(int y = 0;y<h;y++)
		for(int x = 0;x<w;x++)
			if(g[y][x] == 'v' && g[(y+1)%h][x]=='.')
				g[y][x] = 'M';
	for(int y = 0;y<h;y++)
		for(int x = 0;x<w;x++)
			if(g[y][x] == 'M'){
				changed = true;
				g[y][x] = '.';
				g[(y+1)%h][x] = 'v';
			}
	return changed;
}

chrono::time_point<std::chrono::steady_clock> day25(input_t& inp){
	int p1(0), p2(0);

	vector<vector<char>> g;
	for(auto& l: inp){
		g.emplace_back();
		for(auto& c: l)
			g.back().emplace_back(c);
	}
	int w = g[0].size();
	int h = g.size();
	for(p1=1;iter(g,w,h);p1++);
	auto done = chrono::steady_clock::now();
	cout<<"[P1] "<<p1<<endl;
	return done;
}