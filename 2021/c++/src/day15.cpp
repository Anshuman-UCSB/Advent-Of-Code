#include "AOC.h"
#define state pair<int, pii>

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
	
	priority_queue<state, vector<state>, greater<state>> q;
	q.push(make_pair(0, pii(0,0)));
	int risk, x, y;
	pii pos, p1pos(side-1, side-1), p2pos(side*5-1, side*5-1);
	while(!q.empty()){
		state s = q.top();
		q.pop();
		tie(risk, pos) = s;
		tie(x, y) = pos;
		if(pos == p1pos)
			p1 = risk;
		if(pos == p2pos){
			p2 = risk;
			break;
		}
		if(seen[y][x])
			continue;
		seen[y][x] = true;
		
		if(x>0){
			pii t(x-1, y);
			if(seen[y][x-1] == false)
				q.push(make_pair(risk+g[y][x-1], t));
		}
		if(x<g.size()-1){
			pii t(x+1, y);
			if(seen[y][x+1] == false)
				q.push(make_pair(risk+g[y][x+1], t));
		}
		if(y>0){
			pii t(x, y-1);
			if(seen[y-1][x] == false)
				q.push(make_pair(risk+g[y-1][x], t));
		}
		if(y<g.size()-1){
			pii t(x, y+1);
			if(seen[y+1][x] == false)
				q.push(make_pair(risk+g[y+1][x], t));
		}
	}
	
	auto done = chrono::steady_clock::now();
	cout<<"[P1] "<<p1<<"\n[P2] "<<p2<<endl;
	return done;
}