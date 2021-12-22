#include "AOC.h"

struct Cube{
	int lx, hx, ly, hy, lz, hz;
	Cube(string l){
		stringstream ss(l.substr(l.find('=')));
		char tr;
		ss>>tr>>lx>>tr>>tr>>hx>>tr;
		ss>>tr>>tr>>ly>>tr>>tr>>hy>>tr;
		ss>>tr>>tr>>lz>>tr>>tr>>hz;
	}
	Cube(int lx, int hx, int ly, int hy, int lz, int hz):
		lx(lx), hx(hx), ly(ly), hy(hy), lz(lz), hz(hz){}
	inline bool isValid(){
		return lx<=hx && ly<=hy && lz<=hz;
	}
	ull volumep1(){
		if(lx<=-50 || hx>=50 || ly<=-50 || hy>=50 || lz<=-50 || hz>=50)
			return 0;
		ull out = hx-lx+1;
		out*= hy-ly+1;
		out*= hz-lz+1;
		return out;
	}
	ull volumep2(){
		ull out = hx-lx+1;
		out*= hy-ly+1;
		out*= hz-lz+1;
		return out;
	}
};

bool intersects(Cube& a, Cube& b){ // Optimized by GDB the homie
	if(a.hx<b.lx || b.hx<a.lx) return false;
	if(a.hy<b.ly || b.hy<a.ly) return false;
	if(a.hz<b.lz || b.hz<a.lz) return false;
	return true;
}

void subtract(Cube& a, Cube& b, vector<Cube>& build){
	Cube c(	max(a.lx, b.lx), min(a.hx, b.hx),max(a.ly, b.ly),
			min(a.hy, b.hy),max(a.lz, b.lz), min(a.hz, b.hz));
	if(a.lz<c.lz)	build.emplace_back(a.lx, a.hx, a.ly, a.hy, a.lz, c.lz-1); // bottom part
	if(c.hz<a.hz)	build.emplace_back(a.lx, a.hx, a.ly, a.hy, c.hz+1, a.hz); // top part
	if(a.lx<c.lx)	build.emplace_back(a.lx, c.lx-1, a.ly, a.hy, c.lz, c.hz); // middle portions
	if(c.hx<a.hx)	build.emplace_back(c.hx+1, a.hx, a.ly, a.hy, c.lz, c.hz);
	if(a.ly<c.ly)	build.emplace_back(c.lx, c.hx, a.ly, c.ly-1, c.lz, c.hz);
	if(c.hy<a.hy)	build.emplace_back(c.lx, c.hx, c.hy+1, a.hy, c.lz, c.hz);
}

chrono::time_point<std::chrono::steady_clock> day22(input_t& inp){
	ull p1(0), p2(0);
	vector<Cube> cubes;
	for(auto& l: inp){
		Cube cur(l);
		vector<Cube> build;
		for(auto& c: cubes)
			if(intersects(c, cur))
				subtract(c, cur, build);
			else
				build.push_back(c);
		if(l[1] == 'n') // on
			build.push_back(cur);
		cubes = move(build);
	}
	for(auto& c: cubes){
		p1+=c.volumep1();
		p2+=c.volumep2();
	}
	auto done = chrono::steady_clock::now();
	cout<<"[P1] "<<p1<<"\n[P2] "<<p2<<endl;
	return done;
}