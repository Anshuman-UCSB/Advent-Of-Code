#include "AOC.h"

struct virus{
	int dir;
	pii pos;
	int p1;
	long long p2;

	virus(int x, int y):dir(0), pos(x,y), p1(0), p2(0){}

	void iter(set<pii>& m){
		if(m.count(pos)){
			dir = (dir+1)%4;
			m.erase(pos);
		}else{
			p1++;
			dir = (dir+3)%4;
			m.insert(pos);
		}
		switch(dir){
			case 0: pos.y--; break;
			case 1: pos.x++; break;
			case 2: pos.y++; break;
			case 3: pos.x--; break;
		}
	}
	void iter2(map<pii, int>& m){
		switch(m[pos]){
			case 0: dir = (dir+3)%4;	break;
			case 1: p2++; break;
			case 2: dir = (dir+1)%4;	break;
			case 3: dir = (dir+2)%4;	break;
		}
		m[pos] = (m[pos]+1)%4;
		switch(dir){
			case 0: pos.y--; break;
			case 1: pos.x++; break;
			case 2: pos.y++; break;
			case 3: pos.x--; break;
		}
	}
};

chrono::time_point<std::chrono::steady_clock> day22(input_t& inp){
	set<pii> m;
	map<pii, int> m2;
	for(int y = 0;y<inp.size();y++){
		for(int x = 0;x<inp.size();x++){
			if(inp[y][x] == '#'){
				m.insert(pii(x,y));
				m2[pii(x,y)] = 2;
			}

		}
	}
	virus v(inp.size()/2, inp.size()/2);
	for(int i = 0;i<10000;i++){
		v.iter(m);
	}
	v.pos = pii(inp.size()/2, inp.size()/2);
	v.dir = 0;
	for(int i = 0;i<10000000;i++){
		v.iter2(m2);
	}
	auto done = chrono::steady_clock::now();
	cout<<"[P1] "<<v.p1<<endl;
	cout<<"[P2] "<<v.p2<<endl;
	return done;
}