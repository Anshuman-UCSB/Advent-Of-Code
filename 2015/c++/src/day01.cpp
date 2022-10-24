#include "AOC.h"

chrono::time_point<std::chrono::steady_clock> day01(input_t& inp){
	int floor(0), p2(0);
	const string &b = inp[0];
	for(int i = 0;i<b.size();i++){
		if(!p2 && floor == -1)
			p2 = i;
		// floor++;
		if(b[i]&0b1)
			floor--;
		else
			floor++;
	}
	auto done = chrono::steady_clock::now();
	cout<<"[P1] "<<floor<<"\n[P2] "<<p2<<endl;
	return done;
}