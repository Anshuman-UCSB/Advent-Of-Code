#include "AOC.h"


chrono::time_point<std::chrono::steady_clock> day17(input_t& inp){
	stringstream ss(inp[0].substr(15));
	int lx, ly, hx, hy;
	char tr;
	ss>>lx>>tr>>tr>>hx;
	ss.ignore(256, '=');
	ss>>ly>>tr>>tr>>hy;
	int p1((ly*(ly+1))>>1), p2(0);
	auto simulate = [&](int dx, int dy){
		int x(0), y(0);
		while(x<=hx && y>=ly){
			x+=dx;
			y+=dy--;
			if(dx)
				dx--;
			if(lx<=x && x<=hx && ly<=y && y<=hy)
				return true;
		}
		return false;
	};
	for(int y = ly;y<=-ly;y++){
		for(int x = 0; x<=hx;x++){
			p2+=simulate(x, y);
		}
	}
	
	auto done = chrono::steady_clock::now();
	cout<<"[P1] "<<p1<<"\n[P2] "<<p2<<endl;
	return done;
}