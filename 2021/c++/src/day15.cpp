#include "AOC.h"
#include <list>
#define state tuple<int, int, int>

chrono::time_point<std::chrono::steady_clock> day15(input_t& inp){
	int p1(0), p2(0), side(inp.size());
	vector<vector<int>> g(side*5, vector<int>(side*5, 0));
	vector<vector<bool>> seen(side*5, vector<bool>(side*5, false));
	for(int y = 0;y<side;y++)
		for(int x = 0;x<side;x++)
			g[y][x] = inp[y][x]-'0';
	for(int y = side;y<side*5;y++)
		for(int x = 0;x<side;x++)
			g[y][x] = (g[y-side][x] == 9)?1:g[y-side][x]+1;
	for(int y = 0;y<side*5;y++)
		for(int x = side;x<side*5;x++)
			g[y][x] = (g[y][x-side] == 9)?1:g[y][x-side]+1;
	
	vector<list<state>> q(10, list<state>());
	q[0].push_back(state(0, 0, 0));
	int risk, x, y, x1(side-1), y1(side-1), x2(side*5-1), y2(side*5-1);
	for(int i = 0;;i++){
		for(auto& p: q[i%10]){
			tie(risk, x, y) = p;
			if(x==x1 && y==y1)
				p1 = risk;
			else if(x==x2 && y==y2){
				p2 = risk;
				goto done;
			}
			if(seen[y][x])
				continue;
			seen[y][x]=1;
			if(x>0 && seen[y][x-1]==0)
				q[(risk+g[y][x-1])%10].emplace_back(risk+g[y][x-1], x-1, y);
			if(x<g.size()-1 && seen[y][x+1]==0)
				q[(risk+g[y][x+1])%10].emplace_back(risk+g[y][x+1], x+1, y);
			if(y>0 && seen[y-1][x]==0)
				q[(risk+g[y-1][x])%10].emplace_back(risk+g[y-1][x], x, y-1);
			if(y<g.size()-1 && seen[y+1][x]==0)
				q[(risk+g[y+1][x])%10].emplace_back(risk+g[y+1][x], x, y+1);
		}
		q[i%10].clear();
	}
	done:;
	
	auto done = chrono::steady_clock::now();
	cout<<"[P1] "<<p1<<"\n[P2] "<<p2<<endl;
	return done;
}