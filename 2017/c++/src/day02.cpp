#include "AOC.h"

chrono::time_point<std::chrono::steady_clock> day02(input_t& inp){
	int p1(0), p2(0);
	for(auto& r: inp){
		int mn(999), mx(0);
		int t;
		set<int> sorted;
		stringstream ss(r);
		while(ss>>t){
			sorted.insert(t);
			mx = max(mx, t);
			mn = min(mn, t);
		}
		p1+=mx-mn;
		for(auto it = sorted.rbegin(); it!=sorted.rend(); it++){
			for(auto it2 = next(it); it2!=sorted.rend(); it2++){
				if(*it%*it2 == 0) {p2+=*it / *it2; goto next;}
			}
		}
		next:;
	}
	
	auto done = chrono::steady_clock::now();
	cout<<"[P1] "<<p1<<endl;
	cout<<"[P2] "<<p2<<endl;
	return done;
}