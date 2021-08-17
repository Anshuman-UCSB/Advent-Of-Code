#include "AOC.h"
#include <cmath>

int p2Solve(const int& target){
	map<pii, int> m;
	pii p;
	m[p] = 1;
	int len = 0;
	for(;;){
		len++;
		for(int i = 0;i<len;i++){
			p.x++;
			for(int dy = -1;dy<=1;dy++)
				for(int dx = -1;dx<=1;dx++)
					if(dy || dx)
						m[p]+=m[pii(p.x+dx, p.y+dy)];
			if(m[p]>target)
				return m[p];
		}
		for(int i = 0;i<len;i++){
			p.y++;
			for(int dy = -1;dy<=1;dy++)
				for(int dx = -1;dx<=1;dx++)
					if(dy || dx)
						m[p]+=m[pii(p.x+dx, p.y+dy)];
			if(m[p]>target)
				return m[p];
		}
		len++;
		for(int i = 0;i<len;i++){
			p.x--;
			for(int dy = -1;dy<=1;dy++)
				for(int dx = -1;dx<=1;dx++)
					if(dy || dx)
						m[p]+=m[pii(p.x+dx, p.y+dy)];
			if(m[p]>target)
				return m[p];
		}
		for(int i = 0;i<len;i++){
			p.y--;
			for(int dy = -1;dy<=1;dy++)
				for(int dx = -1;dx<=1;dx++)
					if(dy || dx)
						m[p]+=m[pii(p.x+dx, p.y+dy)];
			if(m[p]>target)
				return m[p];
		}
	}

	return m[p];
}

chrono::time_point<std::chrono::steady_clock> day03(input_t& inp){

	int target = stoi(inp[0]);
	int lastPow = sqrt(target);
	// cout<<lastPow<<endl;
	if(!(lastPow&1)) lastPow--;
	int x,y;
	x = (1+lastPow)>>1;
	y = -(lastPow>>1);
	int p1;
	for(int n = 1+lastPow*lastPow;;){
		// cout<<n<<endl;
		for(int i = 0;i<lastPow;i++){
			y++;
			if(++n == target){
				p1 = abs(x)+abs(y);
				goto out;
			}
		}
		lastPow++;
		for(int i = 0;i<lastPow;i++){
			x--;
			if(++n == target){
				p1 = abs(x)+abs(y);
				goto out;
			}
		}
		for(int i = 0;i<lastPow;i++){
			y--;
			if(++n == target){
				p1 = abs(x)+abs(y);
				goto out;
			}
		}
		lastPow++;
		for(int i = 0;i<lastPow;i++){
			x++;
			if(++n == target){
				p1 = abs(x)+abs(y);
				goto out;
			}
		}
	}
	out:;

	int p2 = p2Solve(target);
	auto done = chrono::steady_clock::now();
	cout<<"[P1] "<<p1<<endl;
	cout<<"[P2] "<<p2<<endl;
	return done;
}