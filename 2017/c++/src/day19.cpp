#include "AOC.h"

int dx[4] = {0,1,0,-1};
int dy[4] = {-1,0,1,0};
int p2=0;

string p1solve(const input_t& m, pii p){
	string path;

	int dir = 2;
	for(;;){
		p2++;
		if(char ch = m[p.y][p.x]; ch>='A' && ch<='Z'){
			path+=ch;
		}
		// cout<<p<<endl;
		pii next(p.x+dx[dir], p.y+dy[dir]);
		if(m[p.y][p.x]=='+'){
			dir = (dir+1)%4;
			next = pii(p.x+dx[dir], p.y+dy[dir]);
			if(m[next.y][next.x]!=' '){
				// cout<<"turning onto '"<<m[next.y][next.x]<<"'"<<endl;
				p = next;
			}else{
				dir = (dir+2)%4;
				next = pii(p.x+dx[dir], p.y+dy[dir]);
				if(m[next.y][next.x]!=' '){
					// cout<<"turning on2 "<<m[next.y][next.x]<<endl;
					p = next;
				}
			}
		}else{
			p = next;
		}
		if(m[p.y][p.x] == ' ') return path;
	}
}

chrono::time_point<std::chrono::steady_clock> day19(input_t& inp){
	pii p(0, 0);
	for(;p.x<inp[0].size();p.x++){
		if(inp[0][p.x] == '|') break;
	}
	inp.emplace_back(inp[0].size(), ' ');
	string p1 = p1solve(inp, p);
	
	auto done = chrono::steady_clock::now();
	cout<<"[P1] "<<p1<<endl;
	cout<<"[P2] "<<p2<<endl;
	return done;
}