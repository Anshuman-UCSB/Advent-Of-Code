#include "AOC.h"

chrono::time_point<std::chrono::steady_clock> day02(input_t& inp){
	int p1(0), p2(0);
	int l, w, h;
	char tr;
	for(auto& line: inp){
		stringstream ss(line);
		ss>>l>>tr>>w>>tr>>h;
		p1+=2*(l*w + w*h + h*l);
		p1+=min(l*w, min(w*h, h*l));
		p2+=l*w*h;
		p2+=2*(l+w+h-max(l,max(w,h)));
	}
	auto done = chrono::steady_clock::now();
	cout<<"[P1] "<<p1<<"\n[P2] "<<p2<<endl;
	return done;
}