#include "AOC.h"

chrono::time_point<std::chrono::steady_clock> day05(input_t& inp){
	int p1(0), p2(0);
	map<pii, int> m1, m2;
	int x, y;
	char t;
	vector<pair<pii, pii>> pointset;
	for(auto& l: inp){
		stringstream ss(l);
		ss>>x>>t>>y>>l;
		pii c1(x, y);
		ss>>x>>t>>y;
		pii c2(x, y);
		pointset.emplace_back(c1, c2);
	}
	for(auto& [s, e]: pointset){
		int dx = e.x-s.x;
		int dy = e.y-s.y;
		dx = (dx>0)-(dx<0);
		dy = (dy>0)-(dy<0);
		e.x+=dx;
		e.y+=dy;
		while(s != e){
			if(!(dx && dy))
				if(m1[s]++ == 1) p1++;
			if(m2[s]++ == 1) p2++;
			s.x+=dx;
			s.y+=dy;
		}
	}
	
	auto done = chrono::steady_clock::now();
	cout<<"[P1] "<<p1<<"\n[P2] "<<p2<<endl;
	return done;
}





/*
#include "AOC.h"

pii step(const pii& x, const pii& y){
	pii o;
	if(x.x>y.x) o.x = -1;
	else if(x.x<y.x) o.x =  1;
	if(x.y>y.y) o.y = -1;
	else if(x.y<y.y) o.y =  1;
	return o;
}

chrono::time_point<std::chrono::steady_clock> day05(input_t& inp){
	int p1(0), p2(0);

	vector<pair<pii, pii>> lines;
	char t;
	int x1, x2, y1, y2;
	for(auto& l: inp){
		stringstream ss(l);
		ss>>x1>>t>>y1>>l>>x2>>t>>y2;
		lines.emplace_back(pii(x1, y1), pii(x2, y2));
	}
	map<pii, int> m1, m2;
	for(auto& pointset: lines){
		pii x = pointset.first;
		pii y = pointset.second;
		pii d = step(x, y);
		y.x+=d.x;
		y.y+=d.y;
		while(x != y){
			if(x.x==y.x || x.y == y.y)
				m1[x]++;
			m2[x]++;
			x.x+=d.x;
			x.y+=d.y;
		};
	}
	for(auto [k, v]: m2)
		if(v>1) p2+=1;
	for(auto [k, v]: m1)
		if(v>1) p1+=1;
	
	auto done = chrono::steady_clock::now();
	cout<<"[P1] "<<p1<<"\n[P2] "<<p2<<endl;
	return done;
}
*/