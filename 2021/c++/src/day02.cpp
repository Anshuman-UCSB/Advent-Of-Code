#include "AOC.h"

chrono::time_point<std::chrono::steady_clock> day02(input_t& inp){
	int p1(0), p2(0), x(0), y(0),y2(0), dist;
	string dir;
	for(auto& l: inp){
		stringstream ss(l);
		ss>>dir>>dist;
		switch(dir[0]){
			case 'f':
				x+=dist;
				y2+=y*dist;
				break;
			case 'd':
				y+=dist;
				break;
			case 'u':
				y-=dist;
				break;
		}
	}
	p1 = x*y;
	p2 = x*y2;
	auto done = chrono::steady_clock::now();
	cout<<"[P1] "<<p1<<"\n[P2] "<<p2<<endl;
	return done;
}