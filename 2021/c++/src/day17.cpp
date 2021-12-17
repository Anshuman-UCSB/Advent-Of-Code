#include "AOC.h"


chrono::time_point<std::chrono::steady_clock> day17(input_t& inp){
	int p1(0), p2(0);
	stringstream ss(inp[0].substr(15));
	int lx, ly, hx, hy;
	char tr;
	ss>>lx>>tr>>tr>>hx;
	ss.ignore(256, '=');
	ss>>ly>>tr>>tr>>hy;
	auto simulate = [&](int dx, int dy){
		int x(0), y(0), ans(0);
		while(x<=hx && y>=ly){
			x+=dx;
			y+=dy--;
			ans = max(ans, y);
			if(dx)
				dx--;
			if(lx<=x && x<=hx && ly<=y && y<=hy)
				return ans;
		}
		return -1;
	};
	for(int y = ly;y<=-ly;y++){
		for(int x = 0; x<=hx;x++){
			int res = simulate(x, y);
			if(res != -1){
				p2++;
				p1=max(p1, res);
			}
		}
	}
	
	auto done = chrono::steady_clock::now();
	cout<<"[P1] "<<p1<<"\n[P2] "<<p2<<endl;
	return done;
}