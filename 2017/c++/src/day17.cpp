#include "AOC.h"

#define SIZE 2018

chrono::time_point<std::chrono::steady_clock> day17(input_t& inp){
	int step = stoi(inp[0]);
	// int step = 3;
	int regs[SIZE] = {};
	int p = 0;
	int p1;
	int n;
	for(n = 1;n<2018;n++){
		for(int _ = 0;_<step;_++){
			p = regs[p];
		}
		regs[n] = regs[p];
		regs[p] = n;
		p = n;
	}
	p1 = regs[p];
	int p2 = 0;
	for(int p = 0, i=0; i<50000000;p++){
		if(p == 1) p2=i;
		int s = (i-p) / step +1;
		p += s*(step+1)-1;
		p %= (i+=s);
	}
	
	auto done = chrono::steady_clock::now();
	cout<<"[P1] "<<p1<<endl;
	cout<<"[P2] "<<p2<<endl;
	return done;
}