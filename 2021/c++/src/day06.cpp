#include "AOC.h"
#include <algorithm>
chrono::time_point<std::chrono::steady_clock> day06(input_t& inp){
	long p1(0), p2(0);
	vector<long> fishes(9);
	int t;
	char c;
	for(stringstream ss(inp[0]); ss>>t;fishes[t]++){ss>>c;}
	for(t=0;t<256;t++){
		if(t == 80)
			for(auto& v: fishes)
				p1+=v;
		long babies = fishes[0];
		fishes[7]+=babies;
		fishes[9]+=babies;
		rotate(begin(fishes), begin(fishes)+1, end(fishes));
	}
	for(auto& v: fishes) p2+=v;
	auto done = chrono::steady_clock::now();
	cout<<"[P1] "<<p1<<"\n[P2] "<<p2<<endl;
	return done;
}