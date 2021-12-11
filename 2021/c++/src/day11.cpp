#include "AOC.h"

int iter(vector<vector<int>>& m){
	queue<pii> q;
	int out = 0;
	for(int y = 0;y<10;y++)
		for(int x = 0;x<10;x++)
			if(++m[y][x] > 9)
				q.push(pii(x, y));

	while(!q.empty()){
		pii p = q.front();
		q.pop();
		if(m[p.y][p.x] > 9){
			m[p.y][p.x] = 0;
			out++;
			for(int dy = -1;dy<=1;dy++)
				for(int dx = -1;dx<=1;dx++)
					if((dx || dy) && (p.x+dx>=0 && p.x+dx<10 && p.y+dy>=0 && p.y+dy<10) && m[p.y+dy][p.x+dx] && ++m[p.y+dy][p.x+dx]>9)
						q.push(pii(p.x+dx, p.y+dy));
		}
	}
	return out;
}

chrono::time_point<std::chrono::steady_clock> day11(input_t& inp){
	int p1(0), p2(0);
	vector<vector<int>> m;
	for(auto& l: inp){
		m.emplace_back();
		for(auto c: l)
			m.back().push_back(c-'0');			
	}
	for(int i = 0;i<100;i++)
		p1+=iter(m);
	for(p2=101;iter(m)!=100;p2++);	
	auto done = chrono::steady_clock::now();
	cout<<"[P1] "<<p1<<"\n[P2] "<<p2<<endl;
	return done;
}