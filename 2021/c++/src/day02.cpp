#include "AOC.h"

chrono::time_point<std::chrono::steady_clock> day02(input_t& inp){
	int p1(0), p2(0);

	int aim = 0;
	int x = 0;
	int y = 0;
	int y2 = 0;
	string dir;
	int dist;
	for(auto& l: inp){
		stringstream ss(l);
		ss>>dir>>dist;
		if(dir == "forward"){
			x+=dist;
			y2+=aim*dist;
		}else if(dir == "down"){
			y+=dist;
			aim+=dist;
		}else{
			y-=dist;
			aim-=dist;
		}
	}
	p1 = x*y;
	p2 = x*y2;
	auto done = chrono::steady_clock::now();
	cout<<"[P1] "<<p1<<"\n[P2] "<<p2<<endl;
	return done;
}