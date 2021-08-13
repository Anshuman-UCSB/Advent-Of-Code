#include "AOC.h"
#include <cmath>

chrono::time_point<std::chrono::steady_clock> day03(input_t inp){

	int target = stoi(inp[0]);
	int lastPow = sqrt(target);
	// cout<<lastPow<<endl;
	if(!(lastPow&1)) lastPow--;
	int x,y;
	x = 1+lastPow>>1;
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

	map<pii, int> m;
	pii p(0,0);
	m[p] = 1;
	int len = 1;
	for(;;){
		p.x++;
		m[p] = m[pii(x,y-1)] + m[pii(x,y+1)] + m[pii(x-1,y)] + m[pii(x+1,y)];
		cout<<m[p]<<endl;
		if(m[p]>target)goto finish;
		for(int i = 0;i<len;i++){
			p.y++;
			m[p] = m[pii(x,y-1)] + m[pii(x,y+1)] + m[pii(x-1,y)] + m[pii(x+1,y)];
			cout<<m[p]<<endl;
			if(m[p]>target)goto finish;
		}
		len++;
		for(int i = 0;i<len;i++){
			p.x--;
			m[p] = m[pii(x,y-1)] + m[pii(x,y+1)] + m[pii(x-1,y)] + m[pii(x+1,y)];
			cout<<m[p]<<endl;
			if(m[p]>target)goto finish;
		}
		for(int i = 0;i<len;i++){
			p.y--;
			m[p] = m[pii(x,y-1)] + m[pii(x,y+1)] + m[pii(x-1,y)] + m[pii(x+1,y)];
			cout<<m[p]<<endl;
			if(m[p]>target)goto finish;
		}
	}
	finish:;
	auto done = chrono::steady_clock::now();
	cout<<"[P1] "<<p1<<endl;
	return done;
}