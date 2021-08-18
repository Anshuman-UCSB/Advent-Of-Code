#include "AOC.h"

int dx[4] = {0,1,0,-1};
int dy[4] = {-1,0,1,0};

string p1solve(const input_t& m, pii p){
	string path;

	int dir = 2;
	for(;;){
		if(char ch = m[p.y][p.x]; ch>='A' && ch<='Z'){
			path+=ch;
		}
		cout<<p<<endl;
		pii next(p.x+dx[dir], p.y+dy[dir]);
		if(m[next.y][next.x]==' '){
			dir = (dir+1)%4;
			next = pii(p.x+dx[dir], p.y+dy[dir]);
			if(m[next.y][next.x]!=' '){
				p = next;
			}else{
				dir = (dir+2)%4;
				next = pii(p.x+dx[dir], p.y+dy[dir]);
				if(m[next.y][next.x]!=' '){
					p = next;
				}else{
					break;
				}
			}
		}else{
			p = next;
		}
	}

	return path;
}

chrono::time_point<std::chrono::steady_clock> day19(input_t& inp){
	pii p(0, 0);
	for(;p.x<inp[0].size();p.x++){
		if(inp[0][p.x] == '|') break;
	}
	string p1 = p1solve(inp, p);
	cout<<p<<endl;
	auto done = chrono::steady_clock::now();
	return done;
}